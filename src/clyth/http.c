// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdex/string.h>
#include <clyth/http.h>

HTTPMETHOD __parse_http_method(const char *__request)
{
    if (prefix("GET", __request))
        return GET;
    if (prefix("HEAD", __request))
        return HEAD;
    if (prefix("POST", __request))
        return POST;
    if (prefix("PUT", __request))
        return PUT;
    if (prefix("DELETE", __request))
        return DELETE;
    if (prefix("TRACE", __request))
        return TRACE;
    if (prefix("CONNECT", __request))
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
