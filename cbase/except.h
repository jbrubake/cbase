/* Copyright 2009
 * Kaz Kylheku <kkylheku@gmail.com>
 * Vancouver, Canada
 * All rights reserved.
 *
 * BSD License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3. The name of the author may not be used to endorse or promote
 *      products derived from this software without specific prior
 *      written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef XCEPT_H
#define XCEPT_H

#include <setjmp.h>
#include <stdlib.h>
#include <assert.h>

#define XCEPT_GROUP_ANY 0
#define XCEPT_CODE_ANY  0
#define XCEPT_BAD_ALLOC 1

#ifdef __cplusplus
extern "C" {
#endif

enum { except_no_call, except_call };

typedef struct {
    unsigned long except_group;
    unsigned long except_code;
} except_id_t;

typedef struct {
    except_id_t volatile except_id;
    const char *volatile except_message;
    void *volatile except_dyndata;
} except_t;

struct except_cleanup {
    void (*except_func)(void *);
    void *except_context;
};

struct except_catch {
    const except_id_t *except_id;
    size_t except_size;
    except_t except_obj;
    jmp_buf except_jmp;
};

enum except_stacktype {
    XCEPT_CLEANUP, XCEPT_CATCHER
};

struct except_stacknode {
    struct except_stacknode *except_down;
    enum except_stacktype except_type;
    union {
        struct except_catch *except_catcher;
        struct except_cleanup *except_cleanup;
    } except_info;
};

/* private functions made external so they can be used in macros */
void except_setup_clean(struct except_stacknode *,
        struct except_cleanup *, void (*)(void *), void *);
void except_setup_try(struct except_stacknode *,
        struct except_catch *, const except_id_t [], size_t);
struct except_stacknode *except_pop(void);

/* public interface functions */
int except_init(void);
void except_deinit(void);
void except_rethrow(except_t *);
void except_throw(long, long, const char *);
void except_throwd(long, long, const char *, void *);
void except_throwf(long, long, const char *, ...);
void (*except_unhandled_catcher(void (*)(except_t *)))(except_t *);
unsigned long except_code(except_t *);
unsigned long except_group(except_t *);
const char *except_message(except_t *);
void *except_data(except_t *);
void *except_take_data(except_t *);
void except_set_allocator(void *(*)(size_t), void (*)(void *));
void *except_alloc(size_t);
void except_free(void *);

#define except_code(E) ((E)->except_id.except_code)
#define except_group(E) ((E)->except_id.except_group)
#define except_message(E) ((E)->except_message)
#define except_data(E) ((E)->except_dyndata)

#ifdef __cplusplus
}
#endif

/*
 * void except_cleanup_push(void (*)(void *), void *);
 * void except_cleanup_pop(int);
 * void except_checked_cleanup_pop(void (*)(void *), int);
 * void except_try_push(const except_id_t [], size_t, except_t **);
 * void except_try_pop(void);
 */

#define except_cleanup_push(F, C)                               \
    {                                                           \
        struct except_stacknode except_sn;                      \
        struct except_cleanup except_cl;                        \
        except_setup_clean(&except_sn, &except_cl, F, C)

#define except_cleanup_pop(E)                                   \
        except_pop();                                           \
        if (E)                                                  \
            except_cl.except_func(except_cl.except_context);    \
    }

#define except_checked_cleanup_pop(F, E)                        \
        except_pop();                                           \
        assert (except_cl.except_func == (F));                  \
        if (E)                                                  \
            except_cl.except_func(except_cl.except_context);    \
    }

#define except_try_push(ID, NUM, PPE)                           \
     {                                                          \
        struct except_stacknode except_sn;                      \
        struct except_catch except_ch;                          \
        except_setup_try(&except_sn, &except_ch, ID, NUM);      \
        if (setjmp(except_ch.except_jmp))                       \
            *(PPE) = &except_ch.except_obj;                     \
        else                                                    \
            *(PPE) = 0

#define except_try_pop()                                        \
        except_free(except_ch.except_obj.except_dyndata);       \
        except_pop();                                           \
    }


/*
 * The following code was added to except.h by Jeremy Brubaker
 * (jbru362@gmail.com). It adds TRY, CATCH and END_CATCH macros to allow
 * user code to use kazlib's exception handling in a more intuitive way.
 * It results in a loss of some flexibility, but for my purposes that
 * was OK. See the full documentation for cbase for an overview on how
 * to use the basic exception handling with my changes.
 */

/* TODO: Write simple documentation on how to use this system */

/*************************************
 * Standard error groups and exeptions
 *************************************/

#define X_ALLOC     1
#define X_FOPEN     2
#define X_FCLOSE    3
#define X_FWRITE    4
#define X_BAD_INPUT 5

#define X_USERDEF   6 /* All user defined exceptions start here */

#define DUMMY_CODE  1 /* THROW() doesn't specify an actual exception code */

/**************************************
 * Macros to setup the exception system
 **************************************/

/*
 * This is what I'm going for:
 *
 * TRY
 * {
 *     <code that might fail>
 * }
 * CATCH
 * {
 *     case X_*:
 *         break;
 *     case X_*:
 *         break;
 *     default:
 *         break;
 * }
 * END_CATCH;
 */

#define TRY                                                      \
    {                                                            \
        static const except_id_t catch_spec[] = {                \
            { XCEPT_GROUP_ANY, XCEPT_CODE_ANY } };               \
        except_t *exc;                                           \
        struct except_stacknode except_sn;                       \
        struct except_catch except_ch;                           \
        except_setup_try(&except_sn, &except_ch, catch_spec, 1); \
        if (setjmp(except_ch.except_jmp))                        \
            *(&exc) = &except_ch.except_obj;                     \
        else                                                     \
            *(&exc) = 0;                                         \
        if (exc == 0)

#define CATCH                          \
        else                           \
        {                              \
            switch (except_group(exc))

#define END_CATCH                                                       \
        }                                                               \
        except_free(except_ch.except_obj.except_dyndata); except_pop(); \
    };

#define THROW(type)   except_throw   ((type), DUMMY_CODE, "")
#define RETHROW()     except_rethrow ((exc))

#endif
