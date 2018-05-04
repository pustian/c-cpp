#include<stdio.h>
#include<dirent.h>

int main(void) {
    DIR *dirptr=NULL;
    int i=1;
    struct dirent *entry;
    if((dirptr = opendir("/home/hypertable"))==NULL) {
        printf("opendir failed!");
        return 1;
    } else {
        // Only the first
        // entry=readdir(dirptr);
        // printf("%s\n",entry->d_name);
        // closedir(dirptr);
        while(entry=readdir(dirptr)) {
            printf("filename%d=%s\n",i,entry->d_name);
            i++;
        }
        closedir(dirptr);
    }
    return 0;
}
