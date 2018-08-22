#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define _1M_LEN 1024*1024
// test
// #define _1M_LEN 100

int main() {
    char buf[_1M_LEN] = {0}; // 1
    int i=0;
    char *begin = "================block=======begin";
    char *end= "================block=======end\n";
    for(i=0; i<_1M_LEN; ++i) {
        buf[i] = rand()%95+32; 
    }
    memcpy(buf, begin, strlen(begin));
    memcpy(buf+_1M_LEN - strlen(end), end, strlen(end));
    buf[_1M_LEN-1] = '\0'; // 替换end中\n
    
    char *block_filename = "64M+1.data";

    int fd = open(block_filename, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    int m_size = 63; // M
    int nwrite = -1;
    do {
        if( ( nwrite = write(fd, buf, _1M_LEN) ) < 0) {
            printf("write failed. errno=%d errmsg=%s\n", errno, strerror(errno));
            break;
        }
        --m_size;
    }while(m_size > 0 &&  nwrite >= 0);
    // 1M 1M-1 1M+1
    if( ( nwrite = write(fd, buf, _1M_LEN) ) < 0) {
        printf("write failed. errno=%d errmsg=%s\n", errno, strerror(errno));
    }
    write(fd, buf, 1);

    close(fd);
    return 0;
}
