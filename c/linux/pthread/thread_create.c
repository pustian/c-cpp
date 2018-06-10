#include<stdio.h>
#include<pthread.h>
#include<errno.h>

// gcc -g -o thread thread_create.c ../parafs.c  ../net/restart.c ../net/uiciname.c ../net/uici.c -I../net -pthread
#define THREAD_NUM 20
struct create_args{ 
     char *nodename;
     char *filepath;
};

void *parafs_create_thread(void *args) {
    struct create_args *ptr_create_args =(struct create_args*)args;
    printf("parafs_create args nodename=%s filepath=%s \n", 
            ptr_create_args->nodename, ptr_create_args->filepath);
    return (void *)0;
}
int main(int argc, char *argv[]) {
    pthread_t thread[THREAD_NUM];
    struct create_args thread_args[THREAD_NUM];
    char filepath[THREAD_NUM][256];
    void *thread_result;
    int i= 0;
    for(i = 0; i< THREAD_NUM; ++i) {
        thread_args[i].nodename = "192.168.1.11";
        sprintf(filepath[i], "/test/test_%d.txt", i);
        thread_args[i].filepath = filepath[i];
        pthread_create(&thread[i], NULL, parafs_create_thread, (void *)&thread_args[i]);
    }
    printf("Waiting thread finished\n");
    
    int res = 0;
    for(i=0; i< THREAD_NUM; ++i) {
        res = pthread_join(thread[i], &thread_result);
        if( res ) {
            printf("pthread_joib failed %s\n", strerror(errno));
        } else {
            printf("picked up a thread \n");
        }
    }
    printf("thread all done\n");

    sleep(2);
    for(i=0; i< THREAD_NUM; ++i) {
        printf("%d end ...\n", i);
    }

    printf("All closed done\n");
    return 0;
}
