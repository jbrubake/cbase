/*------------------------------------------------------------------------*\
| xmalloc.c
|
| This file is part of cbase
|
| Copyright (c) 2010, Jeremy Brubaker <jbru362@gmail.com> 
|-------------------------------------------------------------------------*\
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
#include <stdlib.h>
#include <errno.h>

#include "cbase.h"

/*-------------------------------------------------*\
| xmalloc_
|
| Provides a wrapper for malloc()
|
| Parameters:
|     size_t num : Number of bytes to allocate
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *
xmalloc_ (size_t num)
{
    void *new = malloc (num);

    if (!new)
        THROW (EXC_ALLOC);

    return new;
}

/*-------------------------------------------------*\
| xrealloc_
|
| Provides a wrapper for realloc()
|
| Parameters:
|     void *p    : Pointer to memory to reallocate
|     size_t num : Size to allocate
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *
xrealloc_ (void *p, size_t num)
{
  void *new;

  if(!p)
    return xmalloc_ (num);

  new = realloc (p, num);

  if (!new)
      THROW (EXC_ALLOC);

  return new;
}

/*-------------------------------------------------*\
| xcalloc_
|
| Provides a wrapper for calloc()
|
| Parameters:
|     size_t num  : Number of elements to allocate
|     size_t size : Size of each element
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *
xcalloc_ (size_t num, size_t size)
{
  void *new = calloc (num, size);

  if (!new)
      THROW (EXC_ALLOC);

  return new;
}
