// SPDX-License-Identifier: MIT

/* Functions to make working with strings more sane. */

#ifndef STRING_EX_H
#define STRING_EX_H

/* Define the string keyword. */
typedef char *string;

/* Append SRC onto DEST, using reallocation. */
extern string strapp(char **__dest, const char *__src);

/* Create a new dynamic string. */
extern string strnew();

#endif /* STRING_EX_H */
