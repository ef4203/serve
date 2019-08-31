// SPDX-License-Identifier: MIT

/* Provides functions for working with the HTTP standard. */

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1

#include <winsock2.h>
#include <windows.h>

#else

#include <unistd.h>
#include <netinet/in.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdex/string.h>
#include <stdex/int.h>
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

char *__status_code_str(const int __http_status_code)
{
    switch (__http_status_code)
    {
    case 200:
        return "OK";
        break;
    case 404:
        return "Not Found";
        break;
    default:
        return "Not Found";
        break;
    }
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

/* Handle the given URL with a specified FUNC. */
void http_handle(const char *__url, const char *(*__func)())
{
    char *func_buff = (char *)malloc(2048 * sizeof(char));
    func_buff = __func();

    free(func_buff);
}

/* Send a HTTP formated response on the given SOCKET. */
void send_http_response(const int __socket, const int __http_status_code, char **__body)
{
    char *status_code = itostr(__http_status_code);
    char *base_header = strnew();
    strapp(&base_header, "HTTP/1.1 ");
    strapp(&base_header, status_code);
    strapp(&base_header, " ");
    strapp(&base_header, __status_code_str(__http_status_code));
    strapp(&base_header, "\n");

    char *body_len = itostr(strlen(*__body));
    char *content_len_header = strnew();
    strapp(&content_len_header, "Content-length: ");
    strapp(&content_len_header, body_len);
    strapp(&content_len_header, "\n");

    write(__socket, base_header, strlen(base_header));
    write(__socket, content_len_header, strlen(content_len_header));
    write(__socket, "Content-Type: text/html\n\n", 25);
    write(__socket, *__body, strlen(*__body));

    free(base_header);
    free(content_len_header);
}

void serve_files(const int __socket, const char *__path)
{
    char buf[128];
    char *result = strnew();
    FILE *fp;
    if ((fp = fopen(__path, "r")) == NULL)
    {
        strapp(&result, "404: Not Found");

        send_http_response(__socket, 404, &result);
    }
    else
    {
        while (fgets(buf, 128, fp) != NULL)
        {
            strapp(&result, buf);
        }

        send_http_response(__socket, 200, &result);
        fclose(fp);
    }
    free(result);
}
