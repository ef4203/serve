// SPDX-License-Identifier: MIT

/* Functionality for common tasks with integers. */

#include <stdio.h>

/* Convert an integer to string. */
char *itostr(const int __i)
{
    static char __buff[12] = {0};

    sprintf(__buff, "%d", __i);

    return __buff;
}
