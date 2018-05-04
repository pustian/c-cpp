#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>

int main(int argc, char* argv[]) 
{
    char *host;
    char **names;
    char **addrs;
    struct hostent *hostinfo;

    if(argc == 1) {
        char myname[256];
        gethostname(myname, 255);
        host = myname;
    } else {
        host = argv[1];
    }


    hostinfo = gethostbyname(host);
    if(!hostinfo) {
        fprintf(stderr, "cannot get info from host:%s\n", host);
        return 1;
    }

    printf("results for host %s:\n", host);
    printf("Name:%s\n", hostinfo->h_name);
    printf("Aliase:");
    names = hostinfo->h_aliases;
    while(*names) {
        printf("  %s", *names);
        names++;
    }
    putchar('\n');

    if(hostinfo->h_addrtype != AF_INET ) {
        fprintf(stderr, "not an IP host!\n");
        return 1;
    }

    addrs = hostinfo->h_addr_list;
    while(*addrs) {
        printf("[%s]  ", inet_ntoa(*(struct in_addr*)*addrs));
        addrs++;
    }
    
    printf("\n");
    return 0;
}
