#include <signal.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 

static char msg[] = "I received a msg.\n"; 
int len; 
void show_msg() { 
    write(STDERR_FILENO, msg, len); 
} 
int main() { 

    len = strlen(msg); 
    while( 1 ) 
    { 
        sleep(2); /*睡眠2秒*/ 
        show_msg();
    } 
    return 0; 
}
