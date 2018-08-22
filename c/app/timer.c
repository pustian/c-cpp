#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void __str_func(char *str) {
    static int i = 0;
    printf("pid=%u i=%d string %s\n", getpid(), i++, str);
}
/* time's up */
void __my_func_handler(int signo) {
    char *str = "hello";
    __str_func(str);
}

void __init_sigaction (void) {
    struct sigaction tact;
    tact.sa_handler = __my_func_handler;
    tact.sa_flags = 0;
    sigemptyset (&tact.sa_mask);
    sigaction (SIGALRM, &tact, NULL);
}

void __init_timer(int interval_sec) {
    struct itimerval value;
    /* 计时器安装后首先启动的初始值 */
    value.it_value.tv_sec = 1;
    value.it_value.tv_usec = 0;
    /* 计时器重启动的间歇值 */
    value.it_interval.tv_sec = interval_sec;
    value.it_interval.tv_usec = 0;

    /* set ITIMER_REAL */
    setitimer(ITIMER_REAL, &value, NULL);
}

void __timer(int sec) {
    __init_timer(sec);
    __init_sigaction();
    while(1) ;
}

int main (int argc, char** argv) {
//    __timer(3);
    pid_t pid = fork();
    switch(pid) {
        case -1:
        case 0:
            printf("Child pid:%u\n", getpid());
            __timer(5);
            printf("child Done\n");
            break;
        default:
            printf("parent pid:%u\n", getpid());
            printf("parent Done\n");
    }

    return 0;
}
