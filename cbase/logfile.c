/*------------------------------------------------------------------------*\
| xlogfile.c
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

#include <stdio.h>
#include <time.h>

#include "cbase.h"

logfile_t *
open_logfile (const char *filename, const char *format)
{
    return NULL;
}

bool
log_entry (logfile_t *logfile, const char *entry)
{
    return true;
}

bool
close_logfile (logfile_t *logfile)
{
    return true;
}
