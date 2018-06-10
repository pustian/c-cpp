#include <signal.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 
#include <time.h> //包含time()函数
// 如果你想更精确的计算时间差，你可以把 time 函数换成gettimeofday，这个可以精确到微妙。
// 实际中不可以采用 cpu占用100%
#include <sys/time.h>//包含gettimeofday()函数

static char msg[] = "I received a msg.\n"; 

int len; 
static time_t lasttime; 

void show_msg(int signo) { 
    write(STDERR_FILENO, msg, len); 
} 
int main() { 
    struct sigaction act; 
    union  sigval tsval; 

    act.sa_handler = show_msg; 
    act.sa_flags = 0; 
    sigemptyset(&act.sa_mask); 
    sigaction(50, &act, NULL); 

    len = strlen(msg); 
    time(&lasttime); 
    while( 1 ) 
    { 
        time_t nowtime; 
        /*获取当前时间*/ 
        time(&nowtime); 
        /*和上一次的时间做比较，如果大于等于2秒，则立刻发送信号*/ 
        if(nowtime - lasttime >= 2) 
        { 
            /*向主进程发送信号，实际上是自己给自己发信号*/ 
            sigqueue(getpid(), 50, tsval); 
            lasttime = nowtime; 
        }        
    } 
    return 0; 
}



