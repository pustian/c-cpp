#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/wait.h>

// #include "dbg.h"
//  gcc -g parad_timer.c -lrt 
#if 0
#define __START_UP_TIME 10*60
#define DISK_CHECK_SECOND 10*60
#define RECOVER_SECOND 10*60
#define META_BALANCE_SECOND 60*60
#define BRICK_BALANCE_SECOND 8*60*60
#else
#define __START_UP_TIME 2
#define DISK_CHECK_SECOND 4
#define RECOVER_SECOND 5
#define META_BALANCE_SECOND 6
#define BRICK_BALANCE_SECOND 8

#define MAX_NAME_LEN 256
#endif
static int __parad_run_disk_check() {
    puts("__parad_run_disk_check \n");
    //system("/opt/xxxXXX/node.sh");
    return 0;
}
static int __parad_run_recover_replica() {
    puts("__parad_run_recover_replica \n");
    //system("/opt/xxxXXX/node.sh --recove_replica");
    return 0;
}
static int __parad_run_metabalance() {
    puts("__parad_run_meta \n");
    //system("/opt/xxxXXX/node.sh --metabalance");
    return 0;
}
static int __parad_run_brickbalance() {
    puts("__parad_run_brick \n");
    //system("/opt/xxxXXX/node.sh --brickbalance");
    return 0;
}

/** 任务时间 */
static timer_t disk_check_time_id;
static timer_t recover_time_id;
static timer_t meta_time_id;
static timer_t brick_time_id;

/** 回调句柄 */
static void timer_handler( int sig, siginfo_t *si, void *uc ) {
    timer_t *tidp;

    tidp = si->si_value.sival_ptr;
    /** 定时处理设置 */
    if ( *tidp == disk_check_time_id) {
        __parad_run_disk_check();
    } else if ( *tidp == recover_time_id) {
        __parad_run_recover_replica();
    } else if ( *tidp == meta_time_id) {
        __parad_run_metabalance();
    } else if ( *tidp == brick_time_id) {
        __parad_run_brickbalance();
    }
}

static int make_timer(timer_t *timer_id, int expire_sec, int interval_sec) {
    struct sigevent sigevt;
    struct itimerspec its;
    struct sigaction sact;
    int sigNo = SIGRTMIN;

    /* Set up signal handler. */
    sact.sa_flags = SA_SIGINFO;
    sact.sa_sigaction = timer_handler;
    sigemptyset(&sact.sa_mask);
    if (sigaction(sigNo, &sact, NULL) == -1) {
    //  DERROR("sigaction, errno=%d", errno);
        fprintf(stderr, "sigaction, errno=%d", errno);
    }

    /* Set and enable alarm 时间初始化 */
    sigevt.sigev_notify = SIGEV_SIGNAL;
    sigevt.sigev_signo = sigNo;
    sigevt.sigev_value.sival_ptr = timer_id;
    timer_create(CLOCK_REALTIME, &sigevt, timer_id);

    /* 计时器安装后首先启动的初始值 */
    its.it_interval.tv_sec = interval_sec;
    its.it_interval.tv_nsec = 0;
    /* 计时器重启动的间歇值 */
    its.it_value.tv_sec = expire_sec;
    its.it_value.tv_nsec = 0;
    timer_settime(*timer_id, 0, &its, NULL);
   
    return 1;
}
    
static int __para_schedule() {
    make_timer(&disk_check_time_id, __START_UP_TIME, DISK_CHECK_SECOND);
    make_timer(&recover_time_id, __START_UP_TIME, RECOVER_SECOND);
    make_timer(&meta_time_id, __START_UP_TIME, META_BALANCE_SECOND);
    make_timer(&brick_time_id, __START_UP_TIME, BRICK_BALANCE_SECOND);
    while(1){
         sleep(60);;
    }
}

// 创建deamon 启动定时器
static int __para_deamon(char *home) {
    char pid_path[MAX_NAME_LEN] = {0};
    snprintf(pid_path, MAX_NAME_LEN, "%s/status/timer_parent.pid", home);
//    int ret = daemon_pid(pid_path);
//    if(ret) {
//        fprintf(stderr, "daemon_pid errno=%d", errno);
//        DBG_EXIT(ret);
//    }
//    int lockfd = daemon_lock(pid_path);
//    if(ret) {
//        fprintf(stderr, "daemon_lock errno=%d", errno);
//        DBG_EXIT(ret);
//    }

    // fork后让父进程退出，子进程获得新的pid
    pid_t pid=0;
    if( (pid = fork()) < 0 ) {
        return -1; 
    } else if(pid != 0) {
        return 0;
    }
    fprintf(stderr, "1st getpid=%lu getppid=%d\n", getpid(), getppid() );
    setsid(); // 调用setsid来创建新的进程会话。这使得daemon进程成为会话首进程，脱离和terminal的关联。
    chdir(home);

    puts("daemon begin");
    while(1) {
        pid = fork(); // 第二次的fork
        int child_status;
        int ret;
        switch(pid) {
            case -1:
                return -1;
            case 0:
                // setsid(); // 调用setsid来创建新的进程会话。这使得daemon进程成为会话首进程，脱离和terminal的关联。
                fprintf(stderr, "2nd getpid=%lu getppid=%d\n", getpid(), getppid() );
                __para_schedule();
                break;
            default:
                fprintf(stderr, "3nd getpid=%lu getppid=%d\n", getpid(), getppid() );
                // 关闭打开的文件句柄
                ret = wait(&child_status);
                fprintf(stderr, "ret=%d\n", ret);
                if(WIFEXITED(child_status) ) {
                    ret = WEXITSTATUS(child_status);
                    fprintf(stderr, "child return code=%d", ret);
                    continue;
                } else if(WIFSIGNALED(child_status) ) {
                    printf("Child terminated abnormally\n");
                    continue;
                } else {
                    return -1;
                }
                break;
        }
    }
    puts("__para_daemon end");
    return 0;

    // char pid_path[MAX_NAME_LEN] = {0};
    // snprintf(pid_path, MAX_NAME_LEN, "%s/status/timer_status.pid", home);
    // puts(pid_path);
    //   int ret = daemon_pid(pid_path);
    //   if(ret) {
    //       fprintf(stderr, "daemon_pid errno=%d", errno);
    //       return (ret);
    //   }
    //   int lockfd = daemon_lock(pid_path);
    //   if(ret) {
    //       fprintf(stderr, "daemon_lock errno=%d", errno);
    //       return (ret);
    //   }
}

int main() {
    char *home="/opt/wotung/node/0";
    __para_deamon(home);
}

