// SPDX-License-Identifier: MIT

/* Provides functions for working with the HTTP standard. */

#ifndef SERVE_HTTP_H
#define SERVE_HTTP_H

/* Define the HTTP method type. */
typedef int HTTPMETHOD;

/* Define the HTTP request struct. */
typedef struct __request_t
{
    HTTPMETHOD method;
    char url[128];
    char body[1024];
} HTTPREQ;

/* Define the HTTP methods. */
#define GET 1
#define HEAD 2
#define POST 3
#define PUT 4
#define DELETE 5
#define TRACE 6
#define CONNECT 7

/* Parse the HTTP request from the raw request data. */
extern HTTPREQ http_parse_request(char *__request);

#endif /* SERVE_HTTP_H */
