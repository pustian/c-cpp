#include<arpa/inet.h>
#include<errno.h>
#include<stdio.h>
int is_ip4v(const char *ipstr) {
    struct in_addr addr;  
    int ret = inet_pton(AF_INET, ipstr, &addr);
    if(ret < 0) {
        fprintf(stderr, "check %s error:%s\n", ipstr, strerror(errno));
    }
    return ret;
}

int main(int argc, char *argv[]) {
    char *str = "127.0.0.1";
    if(argc >1 ) 
        str = argv[1];
    if(is_ip4v(str)) {
        printf("%s is a ip4v\n", str);
    }else {
        printf("%s is a not ip4v\n", str);
    }

}
