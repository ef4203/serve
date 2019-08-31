// SPDX-License-Identifier: MIT

/* Extending functionality of the string.h standard library. */

#include <stdlib.h>
#include <string.h>

/* Append SRC onto DEST, using reallocation. */
char *strapp(char **__dest, const char *__src)
{
    char *__new = (char *)malloc(
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
char *strnew()
{
    char *__new = (char *)malloc(sizeof(char));

    if (!__new)
        return NULL; /* Memory allocation failed. */

    memset(__new, 0, 1);

    return __new;
}

/* Check whether the PREF is a prefix of STR. */
int strprefix(const char *__pref, const char *__str)
{
    return strncmp(__pref, __str, strlen(__pref)) == 0;
}
