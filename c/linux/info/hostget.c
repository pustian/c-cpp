#include<sys/utsname.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

#define BUFFER_SIZE 1024

int main() {
    char computer[BUFFER_SIZE] = {0};
    if(gethostname(computer, BUFFER_SIZE-1) != 0 ) {
        fprintf(stderr, "Could not get host name:%s\n", strerror(errno) );
        return -1;
    }
    printf("computer hostname is %s\n", computer);

    struct utsname uts;
    if( uname(&uts) < 0 ) {
        fprintf(stderr, "Could not get host info:%s\n", strerror(errno) );
        return -1;
    }
    printf("System is %s on %s hardware.\n ", uts.sysname, uts.machine);
    printf("Nodename is %s.\n", uts.nodename);
    printf("Version is %s %s\n", uts.release, uts.version);

    return 0;
}
