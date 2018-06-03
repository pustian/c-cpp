#include<sys/types.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<unistd.h>
#include<stdio.h>
#include<math.h>

static void __work() {
    FILE *fp;

    double x = 4.5;

    fp = tmpfile();
    if(NULL == fp)
        printf("open tmpfile failed\n");
    int i;
    for(i=0; i <10240; ++i) {
        fprintf(fp, "Do some output\n");
        if(ferror(fp) ) {
            fprintf(stderr, "Error writing to temporary file\n");
            return ;
        }
        if((i+1)%1000 == 0)
            printf("%d\n", i);

    }
    printf("Write 10240 to fp\n");
    for(i=0; i< 10240; ++i) {
        x = log(x*x + 3.21);
    }
    printf("do log 10240\n");
}

int main() {
    struct rusage r_usage;
    struct rlimit r_limit;

    __work();
    getrusage(RUSAGE_SELF, &r_usage);

    printf("CPU usage: User = %ld.%06ld, Systemd = %ld.%06ld\n",
            r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec, 
            r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);

    int priority = getpriority(PRIO_PROCESS, getpid());
    printf("Current priority = %d\n", priority);
    getrlimit(RLIMIT_FSIZE, &r_limit);
    printf("Current FSIZE limit: soft=%ld, hard=%ld\n",
            r_limit.rlim_cur, r_limit.rlim_max);

    r_limit.rlim_cur = 2048;
    r_limit.rlim_max = 4096;
    printf("Setting a 2K file size limit\n");
    setrlimit(RLIMIT_FSIZE, &r_limit);

    __work();
    return 0;
}
