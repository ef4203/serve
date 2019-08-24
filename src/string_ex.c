#include <stdlib.h>
#include <string.h>

/* Defines the string keyword. */
typedef char *string;

/* Append SRC onto DEST, using reallocation. */
int strapp(char **__dest, char *__src)
{
    string __new = (char *)malloc(
        (strlen(*__dest) + strlen(__src)) * sizeof(char) + 1);

    strcpy(__new, *__dest);
    strcat(__new, __src);
    free(*__dest);
    *__dest = __new;

    return 1;
}

/* Create a new dynamic string. */
string strnew()
{
    string __new = (char *)malloc(sizeof(char));

    memset(__new, 0, 1);

    return __new;
}
