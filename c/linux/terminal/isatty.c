#include<unistd.h>
#include<stdio.h>

int main() {
    printf("stdout fd:%d\n", fileno(stdout));
    printf("stderr fd:%d\n", fileno(stderr));
    printf("stdin  fd:%d\n", fileno(stdin));

    if(! isatty(fileno(stdout) ) ) {
        fprintf(stderr, "stdout redirect, now it donot point to termial\n");
    } else {
        fprintf(stdout, "stdout output to terminal\n");
    }
}
