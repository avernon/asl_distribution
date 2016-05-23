/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/
/******************************************************************************
 * This code statically links to code available from
 * http://www.st.com/web/en/catalog/tools/ and that code is subject to a license
 * agreement with terms and conditions that you will be responsible for from
 * STMicroelectronics if you employ that code. Use of such code is your responsibility.
 * Neither AllSeen Alliance nor any contributor to this AllSeen code base has any
 * obligations with respect to the STMicroelectronics code that to which you will be
 * statically linking this code. One requirement in the license is that the
 * STMicroelectronics code may only be used with STMicroelectronics processors as set
 * forth in their agreement."
 *******************************************************************************/

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/*
 * System calls for the STM32F407
 */

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

int _exit(int s)
{
    while (1);
}

caddr_t _sbrk(int inc)
{
    static char* end_of_heap;
    register char* stack asm ("sp");
    char* prev_end_of_heap;
    extern char ld_end asm ("end");
    if (end_of_heap == 0) {
        end_of_heap = &ld_end;
    }
    /* Check that we haven't hit the stack */
    if (end_of_heap + inc > stack) {
        return (caddr_t) -1;
    }
    prev_end_of_heap = end_of_heap;
    end_of_heap += inc;
    return (caddr_t)prev_end_of_heap;
}

int _kill(int id, int s)
{
    return -1;
}
int _getpid(void)
{
    return 0;
}
int _write(int f, char*pointer, int length)
{
    int i = 0;
    while (i < length) {
        __io_putchar(*(pointer + i));
        i++;
    }
    return length;
}

int _close(int f)
{
    return 0;
}

int _fstat(int f, struct stat* s)
{
    return 0;
}

int _isatty(int f)
{
    return 1;
}

int _lseek(int f, int p, int d)
{
    return 0;
}

int _read(int f, char* pointer, int length)
{
    int i = 0;
    while (i < length) {
        *(pointer + i) = __io_getchar();
        i++;
    }
    return length;
}
