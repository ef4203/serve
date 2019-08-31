#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1

#include <winsock2.h>
#include <windows.h>
typedef int* socklen_t;

#else

#include <netinet/in.h>
#include <unistd.h>
typedef int SOCKET;

#endif

#include <stdio.h>
#include <stdlib.h>

#include <stdex/string.h>
#include <stdex/int.h>
#include <serve/http.h>

int main()
{
    SOCKET create_socket, new_socket;
    socklen_t addrlen;
#ifdef _WIN32
	char opt[128] = { 0 };
#else
    int opt = 1;

#endif

    int bufsize = 1024;
    char *request = malloc(bufsize);
    struct sockaddr_in address;

    if (!(create_socket = socket(AF_INET, SOCK_STREAM, 0)))
    {
        fprintf(stderr, "Error creating socket\n");
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)))
    {
        fprintf(stderr, "Error binding socket\n");
#ifdef _WIN32
		closesocket(create_socket);
#else
        close(create_socket);
#endif
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

        switch (req.method)
        {
        case GET:;
            char *path = strnew();
            strapp(&path, "www");
            strapp(&path, req.url);
            serve_files(new_socket, path);
            free(path);
            break;
        default:
            break;
        }
#ifdef _WIN32
		closesocket(new_socket);
#else
        close(new_socket);
#endif
    }

    free(request);
#ifdef _WIN32
	closesocket(create_socket);
#else
	close(create_socket);
#endif

    return EXIT_SUCCESS;
}
