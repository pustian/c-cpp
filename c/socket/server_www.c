#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT  8000

int main() {
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int server_sockfd;
    int client_sockfd;
    char buf[BUFSIZ];
    int len;

    memset(&server_address, 0, sizeof(struct sockaddr_in) );
    memset(&client_address, 0, sizeof(client_address) );

    server_address.sin_family = AF_INET; //设置为IP通信  
    server_address.sin_addr.s_addr = INADDR_ANY; //服务器IP地址--允许连接到所有本地地址上  
    server_address.sin_port = htons(PORT);

    // 创建服务端套接字 IPv4协议。 面向连接通信TCP
    if((server_sockfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0 ) 
    {
        perror("socket error");
        return 1;
    }

    // 套接字绑到服务器的网络地址上
    if(bind(server_sockfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr) ) < 0 )
    {
        perror("socket bind error");
        return 1;
    }

    // 监听请求 监听队列长为5
    if(listen(server_sockfd, 5) < 0 ) {
        perror("listen error");
        return 1;
    }

    int sin_size = sizeof(struct sockaddr_in);

    // 等待客户端连接
    if((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &sin_size)) < 0 )
    {  
        perror("accept error");  
        return 1; 
    }  

//    printf("accept client %s\n",inet_ntoa(client_address.sin_addr));  
    const char *welecome = "Welcome to my server\n";
    len=send(client_sockfd, welecome, sizeof(welecome), 0);//发送欢迎信息  


    while((len = recv(client_sockfd, buf, BUFSIZ, 0) ) > 0 ) {
        buf[len] = '\0';
        printf("server received:%s\n", buf);
        if(send(client_sockfd, buf, len, 0) < 0) 
        {
            perror("write error");
            return 1;
        }
    }

    close(client_sockfd);
    close(server_sockfd);

    return 0;
}
