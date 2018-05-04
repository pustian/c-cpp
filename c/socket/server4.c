#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
// gcc -g -o server server2.c
int main() 
{
    int server_sockfd;
    int client_sockfd;
    int server_len;
    int client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    // create a socket for server
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // name socket
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9001);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
    // create a queue wait client connect
    listen(server_sockfd, 5);
    // ignore child process exit detail
    signal(SIGCHLD, SIG_IGN);
    while(1) {
        char ch;
        printf("server waiting\n");
        // accept a client apply
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
        if(fork() == 0) {
            // read/write the socket fd from client
            read(client_sockfd, &ch, 1);
            printf("read ch: %c from client_socked\n", ch);
            ch++;
            write(client_sockfd, &ch, 1);
            close(client_sockfd);
            return 0;
        } else {
            close(server_sockfd);
        }
    }

    return 0;
}
