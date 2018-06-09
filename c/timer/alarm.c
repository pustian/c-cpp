#include <unistd.h>
#include <stdio.h>
int main(void) { 
    int counter; 
    alarm(1); 
    for(counter=0; 1; counter++) 
        if(!(counter%100)) 
            printf("counter=%d\n", counter); 
    
    return 0;
}
