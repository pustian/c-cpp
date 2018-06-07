#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    pid_t pid;
    char *message;
    char buf[128];
    int n = 0;
    const int SIZE = 8;
    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = SIZE;
            break;
        default:
            message = "This is the parent";
            n = SIZE * 2;
            break;
    }
    
    for(; n>0; n--) {
        memset(buf, 0x0, 128);
        sprintf(buf, "n:%d %s", n, message);
        puts(buf);
        sleep(1);
    }

    return 0;
}
