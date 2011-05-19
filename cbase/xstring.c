/*------------------------------------------------------------------------*\
| xstring.c
|
| This file is part of libcbase
|
| Copyright (c) 2010, Jeremy Brubaker <jbru362@gmail.com> 
|--------------------------------------------------------------------------\
| Permission is hereby granted, free of charge, to any person obtaining a  |
| copy of this software and associated documentation files (the            |
| "Software"), to deal in the Software without restriction, including      |
| without limitation the rights to use, copy, modify, merge, publish,      |
| distribute, distribute with modifications, sublicense, and/or sell       |
| copies of the Software, and to permit persons to whom the Software is    |
| furnished to do so, subject to the following conditions:                 |
|                                                                          |
| The above copyright notice and this permission notice shall be included  |
| in all copies or substantial portions of the Software.                   |
|                                                                          |
| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  |
| OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               |
| MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   |
| IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   |
| DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    |
| OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    |
| THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               |
|                                                                          |
| Except as contained in this notice, the name(s) of the above copyright   |
| holders shall not be used in advertising or otherwise to promote the     |
| sale, use or other dealings in this Software without prior written       |
| authorization.                                                           |
\*------------------------------------------------------------------------*/

#include <string.h>
#include <time.h>

/*-------------------------------------------------*\
| xstrcpy
| 
| Copies src into dst. Tries to allocate enough memory
| for src to fit
| 
| Parameters:
|     const char *dst : string to copy to
|     char * src      : string to copy
| Returns:
|     char * : pointer to dst
\*-------------------------------------------------*/
char *
xstrcpy (char *dst, const char *src)
{
    return "\0";
}

/*-------------------------------------------------*\
| Cats src onto dst. Tries to allocate enough memory
| for src to fit
| 
| Parameters:
|     const char *dst : string to cat to
|     char * src      : string to cat
| Returns:
|     char * : pointer to dst
\*-------------------------------------------------*/
char *
xstrcat (char *dst, const char *src)
{
    return "\0";
}

char *
xstrncpy (char *dst, const char *src, size_t size)
{
    return "\0";
}

char *
xstrncat (char *dst, const char *src, size_t size)
{
    return "\0";
}

int
xsprintf (char *str, const char *format, ...)
{
    return 0;
}

int
xnsprintf (char *str, size_t size, const char *format, ...)
{
    return 0;
}
