#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gdb 其实只是对父进程的debug
// set follow-fork-mode child 命令设置gdb在fork之后跟踪子进程。
// set follow-fork-mode parent设置跟踪父进程。
int main() {
    pid_t pid;
    char *message;
    char buf[128];
    int n = 0;
    const int SIZE =10;

    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            printf("child pid pid=%u ppid=%u\n", getpid(), getppid());
            message = "This is the child";
            n = SIZE;
            break;
        default:
            printf("parent pid pid=%u ppid=%u\n", getpid(), getppid());
            message = "This is the parent";
            n = SIZE/2;
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
