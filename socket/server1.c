#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
// gcc -g -o server server1.c
int main() 
{
    int server_sockfd;
    int client_sockfd;
    int server_len;
    int client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    // create a socket for server
    unlink("server_socket_pus");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    // name socket
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket_pus");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
    // create a queue wait client connect
    listen(server_sockfd, 5);
    while(1) {
        char ch;
        printf("server waiting\n");
        // accept a client apply
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
        // read/write the socket fd from client
        read(client_sockfd, &ch, 1);
        printf("read ch: %c from client_socked\n", ch);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }

    close(server_sockfd);
    return 0;
}
