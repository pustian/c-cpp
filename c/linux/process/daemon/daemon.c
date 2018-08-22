#include <unistd.h>
#include <stdlib.h>

int run(void)
{
// If nochdir is zero, daemon() changes the process's current working directory to the root directory ("/"); otherwise, the current working directory is left unchanged.
// If noclose is zero, daemon() redirects standard input, standard output and standard error to /dev/null; otherwise, no changes are made to these  file descriptors.
    if(daemon(0,0) == -1)
        exit(EXIT_FAILURE);
    while(1){
        puts("hello ");
        sleep(60);
    }
    return 0;
}

int main() {
    puts("runing begin");
    run();
    puts("runing end");
    return 0;
}


