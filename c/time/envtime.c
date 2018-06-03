#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    time_t the_time;
    int i;
    for(i=0; i<=10; ++i) {
        the_time = time((time_t *)0 );
        printf("The time is %ld\n", the_time);
        sleep(2); //每个2秒执行一次
    }

    exit(0);
}
