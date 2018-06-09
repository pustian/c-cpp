#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

/**
 *  该程序的ITMER_REAL定时器，每隔2秒钟都会发送一个SIGALRM信号，
 *  当主函数接收到了这个信号之后，调用信号处理函数prompt_info在标准错误上输出time is running out这个字符串。
 *  对于ITIMER_VIRTUAL和ITIMER_PROF的使用方法类似，当你在setitimer里面设置的定时器为ITIMER_VIRTUAL的时候，
 *  你把sigaction里面的SIGALRM改为SIGVTALARM, 同理，ITIMER_PROF对应SIGPROF。
 *  不过，你可能会注意到，当你用ITIMER_VIRTUAL和ITIMER_PROF的时候，你拿一个秒表，
 *  你会发现程序输出字符串的时间间隔会不止2秒，甚至5-6秒才会输出一个，那是因为cpu在用户与内核切换之间也会浪费时间，
 *  这段时间是不计入在指定时间范围之内的。
 */
static char msg[] = "time is running out.\n";
static int len;

/* time's up */
void prompt_info (int signo) {
    write (STDERR_FILENO, msg, len);
}

void init_sigaction (void) {
    struct sigaction tact;
    tact.sa_handler = prompt_info;
    tact.sa_flags = 0;
    sigemptyset (&tact.sa_mask);
    sigaction (SIGALRM, &tact, NULL);
}

void init_time () {
    struct itimerval value;
    value.it_value.tv_sec = 2;
    value.it_value.tv_usec = 0;
    
    value.it_interval = value.it_value;

    /* set ITIMER_REAL */
    setitimer (ITIMER_REAL, &value, NULL);
}

int main (int argc, char** argv) {
    len = strlen (msg);
    init_sigaction ();
    init_time ();
    while (1)
        ;
    
    exit (0);
}
