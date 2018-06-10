#include<stdlib.h>
#include<stdio.h>

extern char **environ;

int main() {
    char **env = environ;
    while(*env) {
        // printf("env: %s\n", *env++);
        printf("env: %s\n", *env);
        env++;
    }

    return 0;
}
