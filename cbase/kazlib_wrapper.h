#include "except.h"

/* TODO: Need to make sure it is all thread-safe */

/*************************************
 * Standard error groups and exeptions
 *************************************/

#define EXC_ALLOC 1
#define EXC_FOPEN 2
#define EXC_FCLOSE 3
#define EXC_FWRITE 4
#define EXC_BAD_INPUT 5

#define EXC_USERDEF 6 /* All user defined exceptions start here */

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
 *     case EXC_*:
 *         break;
 *     case EXC_*:
 *         break;
 *     default:
 *         break;
 * }
 * END_CATCH;
 
 * TODO: Will need to patch kazlib to get this to work right
 * XXX: I will use group only. Code will always be XCEPT_CODE_ANY
 */

#define TRY do {
#define CATCH switch
#define END_CATCH } while (0)

#define THROW(type)
#define RETHROW(type)

/* make popping and pushing data easier */
