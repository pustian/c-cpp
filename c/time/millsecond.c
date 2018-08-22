#include<time.h>
#include<sys/time.h>
#include<stdio.h>
#include<string.h>

int main() {
    time_t the_time = 0;
    struct tm *tm_ptr;

    (void)time(&the_time);
    tm_ptr = localtime(&the_time);
    printf("Raw time is %ld\n", the_time);
    printf("gmtime[yyyymmdd hh24miss]:%04d%02d%02d %02d%02d%02d\n",
            tm_ptr->tm_year, tm_ptr->tm_mon+1, tm_ptr->tm_mday+1,
            tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
    
    char str_time[27] = {0};
    strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", tm_ptr);
    printf("str_time len=%d, value=%s\n", strlen(str_time), str_time);

    struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("second:%ld\n",tv.tv_sec);  //秒
    printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);  //毫秒
    printf("microsecond:%ld\n",tv.tv_sec*1000000 + tv.tv_usec);  //微秒

    char buf[16] = {0};
    // 毫秒
    sprintf(buf, " %3d", tv.tv_usec/1000) ;
    printf("buf len=%d, value=%s\n", strlen(buf), buf);
    sprintf(&str_time[19], " %03d", tv.tv_usec/1000) ;
    printf("str_time len=%d, value=%s\n", strlen(str_time), str_time);

    sprintf(buf, " %06d", tv.tv_usec) ;
    printf("buf len=%d, value=%s\n", strlen(buf), buf);
    sprintf(&str_time[19], " %06d", tv.tv_usec) ;
    printf("str_time len=%d, value=%s\n", strlen(str_time), str_time);

    return 0;
}
