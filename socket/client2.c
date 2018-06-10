#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// gcc -g -o client client2.c
int main() 
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch='A';

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // name socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9001;
    len = sizeof(address);
    // connect socket to server
    result = connect(sockfd, (struct sockaddr*)& address, len);
    if(result == -1) {
        perror("oops: client2");
        return 1;
    }
    // read/write by socket fd
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);

    printf("char from server = %c\n", ch);

    close(sockfd);
    return 0;
}
