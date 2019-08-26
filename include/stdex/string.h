// SPDX-License-Identifier: MIT

/* Extending functionality of the string.h standard library. */

#ifndef STDEX_STRING_H
#define STDEX_STRING_H

#include <string.h>

/* Append SRC onto DEST, using reallocation. */
extern char *strapp(char **__dest, const char *__src);

/* Create a new dynamic string. */
extern char *strnew();

extern int prefix(const char *__pre, const char *__str);

#endif /* STDEX_STRING_H */
