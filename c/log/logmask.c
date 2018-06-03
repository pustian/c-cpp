#include<syslog.h>
#include<stdio.h>
#include<unistd.h>

int main() {
    int logmask;

    openlog("test_logmask_test", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "infomative message, pid=%d", getpid() );
    syslog(LOG_DEBUG, "debug message, should appear");

    logmask = setlogmask(LOG_UPTO(LOG_NOTICE) );
    syslog(LOG_INFO, "write log infomative message, pid=%d", getpid() );
    syslog(LOG_DEBUG, "write log debug message, should appear");

    closelog();

    return 0;
}
