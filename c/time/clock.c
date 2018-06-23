#include<time.h>
#include<stdio.h>
int main() {
    clock_t start = clock();
    int i=0;
    for(i=0; i< 0x7fffffff; ++i) 
        ;
    clock_t end= clock();
    clock_t elapse = end-start;
    float elapse_sec = elapse /CLOCKS_PER_SEC;
    printf("start=%d end=%d elapse=%d elapse_sec=%.6f\n", start, end, elapse, elapse_sec);
}
