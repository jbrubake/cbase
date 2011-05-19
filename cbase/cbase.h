/*--------------------------------------------------------------------*\
| cbase.h
|
| This file is part of cbase
|
| Copyright (c) 2010, Jeremy Brubaker <jbru362@gmail.com> 
|---------------------------------------------------------------------*\
| Permission is hereby granted, free of charge, to any person          |
| obtaining a copy of this software and associated documentation files |
| (the "Software"), to deal in the Software without restriction,       |
| including without limitation the rights to use, copy, modify, merge, |
| publish, distribute, distribute with modifications, sublicense,      |
| and/or sell copies of the Software, and to permit persons to whom    |
| the Software is furnished to do so, subject to the following         |
| conditions:                                                          |
|                                                                      |
| The above copyright notice and this permission notice shall be       |
| included in all copies or substantial portions of the Software.      |
|                                                                      |
| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      |
| EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   |
| MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                |
| NONINFRINGEMENT.  IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE   |
| LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN      |
| ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    |
| CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     |
| SOFTWARE.                                                            |
|                                                                      |
| Except as contained in this notice, the name(s) of the above         |
| copyright holders shall not be used in advertising or otherwise to   |
| promote the sale, use or other dealings in this Software without     |
| prior written authorization.                                         |
|----------------------------------------------------------------------|
| 
| DOCUMENTATION
|
\---------------------------------------------------------------------*/

#ifndef CBASE_H
#   define CBASE_H

#include <time.h>
#include <stdio.h>

/* TODO: Merge this into cbase.h" */
#include "kazlib_wrapper.h"

/*-----------------------------------------
 *
 * Macros and typedefs to make life easier
 *
 *----------------------------------------*/

/* 
 * Macros to allow C code to be used with C++
 */
#ifdef __cplusplus
#   define BEGIN_C_DECLS extern "C" {
#   define END_C_DECLS   }
#else
#   define BEGIN_C_DECLS
#   define END_C_DECLS
#endif

/* 
 * I need a bool type
 */
/* TODO: Check for stdbool.h? */
typedef enum {false = 0, true = 1} bool;

/*
 * Defintion of NULL
 */
#ifndef NULL
#   define NULL 0
#endif

BEGIN_C_DECLS

/*-----------------------------------------
 *
 * Logfile functions and macros
 *
 *----------------------------------------*/

/*
 * Logfile Type
 *
 * DO NOT use this struct directly. It is subject to
 * change without warning
 */
typedef struct {
    FILE *fd;
    char *format;
} logfile_t;

logfile_t  *open_logfile  (const char *filename, const char *format);
bool        log_entry     (logfile_t *logfile, const char *entry);
bool        close_logfile (logfile_t *logfile);

/*-----------------------------------------
 *
 * Error handling stuff
 *
 *----------------------------------------*/

/* Pointer to error handling function */
/* XXX: How can I avoid the pointless typedef? */
typedef void (*error_handler_t) (const char *message, int error_level);
error_handler_t error_handler;

/* Generic error handlers provided for use */
void print_to_stderr  (const char *, int);
void print_to_logfile (logfile_t *, const char *, int);

/* error_handler() will be called with these as its
 * second parameter. Exception: If die() is called,
 * the second paramter will not be ERROR_FATAL but
 * will be the error_code passed to die() */
#define ERROR_DEBUG      -5
#define ERROR_DIAGNOSTIC -4
#define ERROR_WARNING    -3
#define ERROR_NONFATAL   -2
#define ERROR_FATAL      -1 

/* Generate error messages of different types */
/* XXX: errno for die MUST be > 0 to work right */
#define debug(msg)      generate_error (msg, ERROR_DEBUG)
#define diagnostic(msg) generate_error (msg, ERROR_DIAGNOSTIC)
#define warn(msg)       generate_error (msg, ERROR_WARNING)
#define error(msg)      generate_error (msg, ERROR_NONFATAL)
#define die(msg, errno) generate_error (msg, errno)

void generate_error (const char *message, int error_level);

/*-----------------------------------------
 *
 * Memory management functions and macros
 *
 *----------------------------------------*/

/*
 * Macros to allow calling x*alloc with more sensible parameters
 */
#define xcalloc(type, num)                           \
    ((type *) xcalloc_ ((num), sizeof(type)))
#define xmalloc(type, num)                           \
    ((type *) xmalloc_ ((num) * sizeof(type)))
#define xrealloc(type, p, num)                       \
    ((type *) xrealloc_ ((p), (num) * sizeof(type)))
#define xfree(stale)                                 \
    do { free (stale); stale = NULL; } while(0);

void *xmalloc_  (size_t num);
void *xcalloc_  (size_t num, size_t size);
void *xrealloc_ (void *p, size_t num);

/*-----------------------------------------
 *
 * String manipulation functions and macros
 *
 *----------------------------------------*/

char *xstrcpy   (char *dst, const char *src);
char *xstrcat   (char *dst, const char *src);
char *xstrncpy  (char *dst, const char *src, size_t size);
char *xstrncat  (char *dst, const char *src, size_t size);
int   xsprintf  (char *str, const char *format, ...);
int   xnsprintf (char *str, size_t size, const char *format, ...);

/*-----------------------------------------
 *
 * Time manipulation functions and macros
 *
 *----------------------------------------*/

const char *xstrftime    (const char *format);
struct tm  *getlocaltime ();
struct tm  *getgmttime   ();

/*-----------------------------------------
 *
 * Utility functions and macros
 *
 *----------------------------------------*/

char *chomp (char *string);

END_C_DECLS

#endif /* !CBASE_H */
