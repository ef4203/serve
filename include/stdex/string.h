// SPDX-License-Identifier: MIT

/* Extending functionality of the string.h standard library. */

#ifndef STDEX_STRING_H
#define STDEX_STRING_H

#include <string.h>

/* Define the string keyword. */
typedef char *string;

/* Append SRC onto DEST, using reallocation. */
extern string strapp(char **__dest, const char *__src);

/* Create a new dynamic string. */
extern string strnew();

#endif /* STDEX_STRING_H */
