#include <unistd.h>
#include <signal.h>
#include <stdio.h>
// 1. main 函数调用 mysleep 函数,后者调用 sigaction 注册了 SIGALRM 信号的处理函数 sig_alrm。
// 2. 调用 alarm(nsecs)设定闹钟。
// 3. 调用 pause 等待,内核切换到别的进程运行。
// 4. nsecs 秒之后,闹钟超时,内核发 SIGALRM 给这个进程。
// 5. 从内核态返回这个进程的用户态之前处理未决信号,发现有 SIGALRM 信号,其处理函数是 sig_alrm。
// 6. 切换到用户态执行 sig_alrm 函数,进入 sig_alrm 函数时 SIGALRM 信号被自动屏蔽,从 sig_alrm 函数返回时 SIGALRM 信号自动解除屏蔽。然后
// 自动执行系统调用 sigreturn 再次进入内核,再返回用户态继续执行进程的主控制流程(main 函数调用的 mysleep 函数)。
// 7. pause 函数返回-1,然后调用 alarm(0)取消闹钟,调用 sigaction 恢复SIGALRM 信号以前的处理动作。

void sig_alrm(int signo) {
     /* nothing to do */
    printf("call sig_alrm %d\n", signo);
}

// unsigned int 
void mysleep(unsigned int nsecs) {
    struct sigaction newact; 
    struct sigaction oldact;
    // 调用 sigaction 注册了 SIGALRM 信号 的处理函数 sig_alrm
    newact.sa_handler = sig_alrm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    //  alarm(nsecs)设定闹钟
    alarm(nsecs);
    //  pause 等待,内核切换到别的进程运行
    pause();

//    unsigned int unslept;
//    unslept = alarm(0);
//    sigaction(SIGALRM, &oldact, NULL);
//    return unslept;
}
int main(void) {
    while(1){
        mysleep(2);
        printf("Two seconds passed\n");
    }
    return 0;
}
