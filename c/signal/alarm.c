#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig) {
    alarm_fired = 1;
}

int main() {
    pid_t pid;
    printf("Alarm application starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork error");
            exit(1);
        case 0:  // child
            printf("child continue\n");
            sleep(5);
            kill(getppid(), SIGALRM);
            printf("child done\n");
            exit(0);
        default:
            printf("parent continue\n");
    }

    printf("Waiting for alarm to go off\n");
    (void) signal(SIGALRM, ding);
    pause();
    if(alarm_fired) 
        printf("Ding!\n");

    printf("Done\n");
    exit(0);
}
