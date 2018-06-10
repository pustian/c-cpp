#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>

// gcc -g -o client client.c
int main() 
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch='A';

    // create socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    // name socket
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket_pus");
    len = sizeof(address);
    // connect socket to server
    result = connect(sockfd, (struct sockaddr*)& address, len);
    if(result == -1) {
        perror("oops: client1");
        return 1;
    }
    // read/write by socket fd
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);

    printf("char from server = %c\n", ch);

    close(sockfd);
    return 0;
}
