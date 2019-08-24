#ifndef STRING_EX_H
#define STRING_EX_H

/* Defines the string keyword. */
typedef char *string;

/* Append SRC onto DEST, using reallocation. */
extern int strapp(char **__dest, const char *__src);

/* Create a new dynamic string. */
extern char *strnew();

#endif
