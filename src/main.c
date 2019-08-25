#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdex/string.h>

int main()
{
    int create_socket, new_socket;
    socklen_t addrlen;
    int opt = 1;
    int bufsize = 1024;
    string buffer = malloc(bufsize);
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
    address.sin_port = htons(8080);

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

        recv(new_socket, buffer, bufsize, 0);

        // printf("%s\n", buffer);

        char buf[128];
        string result = strnew();
        FILE *fp;
        if ((fp = popen("sh -c www/index.sh", "r")) == NULL)
        {
            printf("Error opening pipe!\n");
        }

        while (fgets(buf, 128, fp) != NULL)
        {
            strapp(&result, buf);
        }

        char contentLen[12];
        sprintf(contentLen, "%d", (int)strlen(result));

        string contentHeader = strnew();
        strapp(&contentHeader, "Content-length: ");
        strapp(&contentHeader, contentLen);
        strapp(&contentHeader, "\n");

        write(new_socket, "HTTP/1.1 200 OK\n", 16);
        write(new_socket, contentHeader, strlen(contentHeader));
        write(new_socket, "Content-Type: text/html\n\n", 25);
        write(new_socket, result, strlen(result));

        free(result);
        free(contentHeader);

        if (pclose(fp))
        {
            printf("Command not found or exited with error status\n");
        }

        close(new_socket);
    }

    free(buffer);
    close(create_socket);

    return EXIT_SUCCESS;
}
