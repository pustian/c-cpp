#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

//* 实际上代替了现在的进程。且不会回到原来的进程空间
void call_execl() {
    char *path= "/home/parafs";
    printf("execl begin assues ls is in /bin\n");
    int i=0;
    for(i=0; i<3; i++) {
        int ret = execl("/home/parafs/workspace/c-cpp/c/linux/process/hello", "hello", NULL);
        printf("execl done ret=%d, error message=%s\n", ret, strerror(errno)); // --- 将不会被打印
    }
}

void call_execlp() {
    printf("execlp begin assues ls is in path\n");
    int ret = execlp("ls", "ls", "-at", NULL);
    printf("execlp done ret=%d, error message=%s\n", ret, strerror(errno)); // --- 将不会被打印
}

void call_execle() {
    char *const ps_envp[] = {
        "PATH=/bin:/usr/bin", "TERM=console", 0
    };
    printf("execle begin passes own environment \n");
    int ret = execle("/bin/ls", "ls", "-d", NULL, ps_envp);
    printf("execle done ret=%d, error message=%s\n", ret, strerror(errno)); // --- 将不会被打印
}

void call_execv() {
    char *const ps_argv[] = {
        "ls", "-lrt", NULL
    };
    printf("execv begin assues ls is in /bin\n");
    int ret = execv("/bin/ls", ps_argv);
    printf("execv done ret=%d, error message=%s\n", ret, strerror(errno)); // --- 将不会被打印
}

void call_execvp() {
    char *const ps_argv[] = {
        "ls", "-at", NULL
    };
    printf("execvp begin assues ls is in path\n");
    int ret = execvp("ls", ps_argv);
    printf("execvp done ret=%d, error message=%s\n", ret, strerror(errno)); // --- 将不会被打印
}

void call_execve() {
    char *const ps_argv[] = {
        "ls", "-d", NULL
    };
    char *const ps_envp[] = {
        "PATH=/bin:/usr/bin", "TERM=console", 0
    };
    printf("execve begin passes own environment \n");
    int ret = execve("/bin/ls", ps_argv, ps_envp);
    printf("execve done ret=%d, error message=%s\n", ret, strerror(errno)); // --- 将不会被打印
}
int main() {
    printf("main begin call_execl\n");
    call_execl();
    printf("main  call_execl done\n"); // --- 将不会被打印

    // printf("main begin call_execlp\n");
    // call_execlp();
    // printf("main  call_execlp done\n"); // --- 将不会被打印
    
    // printf("main begin call_execle\n");
    // call_execle();
    // printf("main  call_execle done\n"); // --- 将不会被打印

    // printf("main begin call_execv\n");
    // call_execv();
    // printf("main  call_execv done\n"); // --- 将不会被打印

    // printf("main begin call_execvp\n");
    // call_execvp();
    // printf("main  call_execvp done\n"); // --- 将不会被打印
    
    // printf("main begin call_execve\n");
    // call_execve();
    // printf("main  call_execve done\n"); // --- 将不会被打印

    exit(0);
}

