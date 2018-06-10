#include <stdio.h>  
#include <signal.h>  
#include <sys/time.h>  
  
void signalHandler(int signo)  
{  
    switch (signo){  
        case SIGALRM:  
            printf("Caught the SIGALRM signal!\n");  
            break;  
   }  
}  
  
int main(int argc, char *argv[])  {  
    signal(SIGALRM, signalHandler);  
  
    // 在setitimer方法调用成功后，延时1微秒便触发一次SIGALRM信号，以后每隔200毫秒触发一次SIGALRM信号
    // settimer工作机制是，先对it_value倒计时，当it_value为零时触发信号，然后重置为it_interval，继续对it_value倒计时，一直这样循环下去。
    struct itimerval new_value, old_value;  
    new_value.it_value.tv_sec = 0;  
    new_value.it_value.tv_usec = 1;  
    new_value.it_interval.tv_sec = 5;  
    new_value.it_interval.tv_usec = 200000;  
    // old_value参数，通常用不上，设置为NULL，它是用来存储上一次setitimer调用时设置的new_value值。
    setitimer(ITIMER_REAL, &new_value, &old_value);  
      
    for(;;);  
       
    return 0;  
}  
