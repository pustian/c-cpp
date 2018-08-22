#include<signal.h>
#include<time.h>

/**
 * 为测试
 */
timer_t firstTimerID;
timer_t secondTimerID;
timer_t thirdTimerID;
timer_t fourthTimerID;
int z=0;
int a=0;
int t_block3=4;
float delay_blocks;

struct itimerspec it;
struct itimerspec its;

static void timerHandler(int sig,siginfo_t*si,void*uc ) {
    timer_t*tidp;

    tidp = si->si_value.sival_ptr;

    if(*tidp == firstTimerID ){
        printf("First timer\n");
    }
    elseif(*tidp == secondTimerID ){
        printf("Second timer\n");
    }
    elseif(*tidp == thirdTimerID ){
        printf("Third timer\n");
    }
    elseif(*tidp == fourthTimerID ){
        printf("Fourth timer\n");
    }

    z--;
    printf("%d", z);

}

staticint makeTimer(timer_t*timerID,int time)
{
    struct sigevent te;
    struct itimerspec its;
    struct sigaction sa;
    int sigNo = SIGRTMIN;

    // Set up signal handler.
    sa.sa_flags = SA_SIGINFO; 
    sa.sa_sigaction = timerHandler;//Action when singal is triggered
    sigemptyset(&sa.sa_mask);
    if(sigaction(sigNo,&sa, NULL)==-1){
        perror("sigaction");
    }

    // Set and enable alarm 
    te.sigev_notify = SIGEV_SIGNAL;//Gnerate alarm upon expiration
    te.sigev_signo = sigNo;//SIGALRM
    te.sigev_value.sival_ptr = timerID;//Timer ID
    //Create a per_process timer using the timer ID
    timer_create(CLOCK_REALTIME,&te, timerID);

    //Interval for starting again 
    its.it_interval.tv_sec =0;
    its.it_interval.tv_nsec =0;
    //Timer time
    its.it_value.tv_sec = time;
    its.it_value.tv_nsec =0;
    //Arm/disarmer a per process time
    timer_settime(*timerID,0,&its, NULL);

    return1;
}

int main(){
    while(1){
        printf("Enter the number of the block\n");
        if(scanf(" %d",&a)==1){
    
        switch(a){
        case3: printf("Block number three, belt will proceed to stop in 12 seconds\n");
                if(z==0){                  
                makeTimer(&firstTimerID, t_block3);
                }elseif(z==1){
                    makeTimer(&secondTimerID,4);
                    timer_gettime(&firstTimerID,&it);
                    delay_blocks=t_block3-(it.it_value.tv_sec+(it.it_value.tv_nsec*0.000000001));
                    printf("Difference between the first and the second timer = %f\n", delay_blocks);
    
                }elseif(z==2){
                makeTimer(&thirdTimerID,4);
                }elseif(z==3){
                makeTimer(&fourthTimerID,4);
                }
                z++;
                break;
    
        case2: printf("Block number two, belt will proceed to stop in 10 seconds\n");
                        //sleep(1);
                        break;
    
        case4: printf("Block number four, belt won't stop\n");
                        //sleep(1);
                        break;
        default:printf("Wrong lecture\n");
    
        }
        }
    
    }
}
