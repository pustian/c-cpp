#include<syslog.h>
#include<stdio.h>

int main() {
    FILE *fp;
    fp = fopen("none", "r");
    if(NULL == fp) {
        syslog(LOG_ERR|LOG_USER, "oops - %m\n");
    }
    return 0;
}
