#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

timer_t firstTimerID;
timer_t secondTimerID;
timer_t thirdTimerID;


static void timerHandler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;

    tidp = si->si_value.sival_ptr;

    if ( *tidp == firstTimerID ) {
        malloc(10);
        printf("2ms malloc\n");
    } else if ( *tidp == secondTimerID ) {
        malloc(20);
        printf("10ms\n");
    } else if ( *tidp == thirdTimerID ) {
        malloc(30);
        printf("100ms\n\n");
    }
}

static int makeTimer( timer_t *timerID, int expireMS, int intervalMS )
{
    struct sigevent te;
    struct itimerspec its;
    struct sigaction sa;
    int sigNo = SIGRTMIN;

    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sigNo, &sa, NULL) == -1) {
        perror("sigaction");
    }

    /* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
    timer_create(CLOCK_REALTIME, &te, timerID);

    /* 计时器重启动的间歇值 */
    its.it_interval.tv_sec = intervalMS;
    its.it_interval.tv_nsec = 0;// intervalMS * 1000000;
    /* 计时器安装后首先启动的初始值 */
    its.it_value.tv_sec = expireMS;
    its.it_value.tv_nsec = 0;// expireMS * 1000000;
    timer_settime(*timerID, 0, &its, NULL);

    return 1;
}

int main()
{
    makeTimer(&firstTimerID, 2, 2); //2ms
    makeTimer(&secondTimerID, 10, 10); //10ms
    makeTimer(&thirdTimerID, 100, 100); //100ms

    while(1)
        ;;
}
