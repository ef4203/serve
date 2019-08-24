// SPDX-License-Identifier: MIT

/* Functions to make working with strings more sane. */

#include <stdlib.h>
#include <string.h>

/* Define the string keyword. */
typedef char *string;

/* Append SRC onto DEST, using reallocation. */
string strapp(char **__dest, const char *__src)
{
    string __new = (char *)malloc(
        (strlen(*__dest) + strlen(__src)) * sizeof(char) + 1);

    if (!__new)
        return NULL; /* Memory allocation failed. */

    strcpy(__new, *__dest);
    strcat(__new, __src);
    free(*__dest);
    *__dest = __new;

    return *__dest;
}

/* Create a new dynamic string. */
string strnew()
{
    string __new = (char *)malloc(sizeof(char));

    if (!__new)
        return NULL; /* Memory allocation failed. */

    memset(__new, 0, 1);

    return __new;
}
