#include<time.h>
#include<stdio.h>

int main() {
    struct tm *tm_ptr;
    time_t the_time = 0;

    (void)time(&the_time);
    // the_time = time((time_t *)0);
    tm_ptr = gmtime(&the_time);

    printf("Raw time is %ld\n", the_time);
    printf("gmtime[yyyymmdd hh24miss]:%04d%02d%02d %02d%02d%02d\n",
            tm_ptr->tm_year, tm_ptr->tm_mon+1, tm_ptr->tm_mday+1,
            tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);

    return 0;
}
