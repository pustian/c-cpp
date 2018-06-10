#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define PORT 8000

int main() 
{
    int client_sockfd;
    int len;
    struct sockaddr_in server_addr;
    char buf[BUFSIZ];
    
    memset(&server_addr, 0x0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET; // 设置IP通信
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // 创建客户端套接字 IP
    if((client_sockfd = socket(PF_INET, SOCK_STREAM, 0 ) ) < 0 ) 
    {
        perror("socket error");
        return 1;
    }

    // 将套接字绑定到服务器的网络地址上
    if((connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) ) < 0)
    {
        perror("connect error");
        return 1;
    }

    printf("connected to server. BUFSIZ: %d \n", BUFSIZ);
    len = recv(client_sockfd, buf, BUFSIZ, 0); //接收服务端信息
    buf[len] = '\0';
    printf("Server info:%s type 'quit' end socket\n", buf);

    while(1) 
    {
        printf("Enter string to send:");  
        scanf("%s",buf);  
        if(!strcmp(buf,"quit") )  break;  
        len=send(client_sockfd,buf,strlen(buf),0);  
        len=recv(client_sockfd,buf,BUFSIZ,0);  
        buf[len]='\0';  
        printf("received:%s\n",buf); 
    }
    close(client_sockfd);

    return 0;
}

