// SPDX-License-Identifier: MIT

/* Provides functions for working with the HTTP standard. */

#include <stdio.h>
#include <stdex/string.h>
#include <serve/http.h>

HTTPMETHOD __parse_http_method(const char *__request)
{
    if (strprefix("GET", __request))
        return GET;
    if (strprefix("HEAD", __request))
        return HEAD;
    if (strprefix("POST", __request))
        return POST;
    if (strprefix("PUT", __request))
        return PUT;
    if (strprefix("DELETE", __request))
        return DELETE;
    if (strprefix("TRACE", __request))
        return TRACE;
    if (strprefix("CONNECT", __request))
        return CONNECT;

    fprintf(stderr, "Could not understand HTTP method");

    // TODO: Figure something out here
    return GET;
}

/* Parse the HTTP request from the raw request data. */
HTTPREQ http_parse_request(char *__request)
{
    HTTPREQ request;
    request.method = __parse_http_method(__request);

    memset(request.url, 0, sizeof(request.url));
    memset(request.body, 0, sizeof(request.body));

    char *requestPtr = __request;
    while (*++requestPtr != ' ')
        ;

    int i = 0;
    while (*++requestPtr != ' ' && i < sizeof(request.url))
    {
        request.url[i] = *requestPtr;
        i++;
    }

    return request;
}
