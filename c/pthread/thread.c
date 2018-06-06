#include<stdio.h>
#include<pthread.h>
#include<errno.h>

#define THREAD_NUM 10
void *thread_func(void *num) {
    printf("num=%d abs=%d\n", *(int*)num, abs(*(int*)num));
    return (void *)0;
}
int main(int argc, char *argv[]) {
    pthread_t thread[THREAD_NUM];
    int thread_args[THREAD_NUM];
    void *thread_result;
    int i= 0;
    for(i = 0; i< THREAD_NUM; ++i) {
        thread_args[i] = i* -1;
        pthread_create(&thread[i], NULL, thread_func, (void *)&thread_args[i]);
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
    printf("All done\n");

    return 0;
}
