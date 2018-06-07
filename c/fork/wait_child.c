#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    pid_t pid;
    char * message;
    char buf[128] = {0};
    int n;
    const int SIZE =10;
    int exit_code;

    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = SIZE;
            exit_code = 37;
            break;
        default:
            message = "This is the parent";
            n = SIZE/2;
            exit_code = 0;
            break;
    }
    
    for(; n>0; n--) {
        memset(buf, 0x0, 128);
        sprintf(buf, "n:%d %s", n, message);
        puts(buf);
        sleep(1);
    }

    if( pid != 0)  {
        int stat_val;
        pid_t child_pid = wait(&stat_val);

        printf("Child had finished: PID=%d\n", child_pid);
       
        if(WIFEXITED(stat_val) ) {
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        } else {
            printf("Child terminated abnormally\n");
        }
    }
    printf("exit code=%d\n", exit_code);
    return exit_code;
}
