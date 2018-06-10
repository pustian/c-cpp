#include <stdio.h>    // for printf()    
#include <signal.h>   
#include <sys/time.h>  
  
#include <errno.h>  
  
void sigFunc()  
{  
   static int iCnt = 0;  
   printf("The %d Times: Hello world\n", iCnt++);  
}  
  
int main(void)  
{  
   struct itimerval tv, otv;  
   signal(SIGALRM, sigFunc);  
   //how long to run the first time  
   tv.it_value.tv_sec = 1;  
   tv.it_value.tv_usec = 0;  
   //after the first time, how long to run next time  
   tv.it_interval.tv_sec = 5;  
   tv.it_interval.tv_usec = 0;  
  
   printf("otv: %d, %d, %d, %d\n", otv.it_value.tv_sec, otv.it_value.tv_usec, otv.it_interval.tv_sec, otv.it_interval.tv_usec);  
   printf("tv: %d, %d, %d, %d\n", tv.it_value.tv_sec, tv.it_value.tv_usec, tv.it_interval.tv_sec, tv.it_interval.tv_usec);  
   // if(setitimer(ITIMER_REAL, &tv, &otv) != 0)  
   if(setitimer(ITIMER_REAL, &tv, NULL) != 0)  
       printf("setitimer err %d\n", errno);  
   printf("set otv: %d, %d, %d, %d\n", otv.it_value.tv_sec, otv.it_value.tv_usec, otv.it_interval.tv_sec, otv.it_interval.tv_usec);  
   printf("set tv: %d, %d, %d, %d\n", tv.it_value.tv_sec, tv.it_value.tv_usec, tv.it_interval.tv_sec, tv.it_interval.tv_usec);  
  
   while(1)  
   {  
       sleep(1);  
   printf("set otv: %d, %d, %d, %d\n", otv.it_value.tv_sec, otv.it_value.tv_usec, otv.it_interval.tv_sec, otv.it_interval.tv_usec);  
   printf("set tv: %d, %d, %d, %d\n", tv.it_value.tv_sec, tv.it_value.tv_usec, tv.it_interval.tv_sec, tv.it_interval.tv_usec);  
   }  
} 
