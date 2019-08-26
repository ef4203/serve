#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdex/string.h>
#include <stdex/int.h>
#include <clyth/http.h>

int main()
{
    int create_socket, new_socket;
    socklen_t addrlen;
    int opt = 1;
    int bufsize = 1024;
    char *request = malloc(bufsize);
    struct sockaddr_in address;

    if (!(create_socket = socket(AF_INET, SOCK_STREAM, 0)))
    {
        fprintf(stderr, "Error creating socket\n");
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8084);

    if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)))
    {
        fprintf(stderr, "Error binding socket\n");
        close(create_socket);
        return EXIT_FAILURE;
    }

    while (1)
    {
        if (listen(create_socket, 10) < 0)
        {
            perror("server: listen");
            exit(EXIT_FAILURE);
        }

        if ((new_socket = accept(create_socket, (struct sockaddr *)&address, &addrlen)) < 0)
        {
            perror("server: accept");
            exit(EXIT_FAILURE);
        }

        recv(new_socket, request, bufsize, 0);

        HTTPREQ req = http_parse_request(request);
        // Debug things
        printf("Http method %d\n", req.method);
        printf("On url: %s\n", req.url);

        switch (req.method)
        {
        case GET:;
            char *path = strnew();
            strapp(&path, "www");
            strapp(&path, req.url);
            char buf[128];
            char *result = strnew();
            FILE *fp;
            if ((fp = fopen(path, "r")) == NULL)
            {
                strapp(&result, "404: Not Found");

                char *contentLen = itostr(strlen(result));

                char *contentHeader = strnew();
                strapp(&contentHeader, "Content-length: ");
                strapp(&contentHeader, contentLen);
                strapp(&contentHeader, "\n");

                write(new_socket, "HTTP/1.1 404 Not Found\n", 23);
                write(new_socket, "Content-Type: text/html\n\n", 25);
                write(new_socket, "Content-Type: text/html\n\n", 25);
                write(new_socket, result, strlen(result));

                free(result);
                free(contentHeader);
            }
            else
            {
                while (fgets(buf, 128, fp) != NULL)
                {
                    strapp(&result, buf);
                }

                char *contentLen = itostr(strlen(result));

                char *contentHeader = strnew();
                strapp(&contentHeader, "Content-length: ");
                strapp(&contentHeader, contentLen);
                strapp(&contentHeader, "\n");

                write(new_socket, "HTTP/1.1 200 OK\n", 16);
                write(new_socket, contentHeader, strlen(contentHeader));
                write(new_socket, "Content-Type: text/html\n\n", 25);
                write(new_socket, result, strlen(result));

                free(result);
                free(contentHeader);

                if (fclose(fp))
                {
                    printf("Command not found or exited with error status\n");
                }
            }
            free(path);
            break;
        default:
            break;
        }

        close(new_socket);
    }

    free(request);
    close(create_socket);

    return EXIT_SUCCESS;
}
