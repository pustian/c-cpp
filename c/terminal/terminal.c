#include<unistd.h>
#include<stdio.h>
#include<string.h>
#define LINE_SIZE 256
// gcc terminal.c
// ./a.out
// ./a.out >/dev/null
int main(){
    FILE *input =  fopen("/dev/tty", "r");
    FILE *output = fopen("/dev/tty", "w");

    fputs("Input something max:i256\n", output);
    char buf[LINE_SIZE] = {0};
    char *str;
    str = fgets(buf, LINE_SIZE, input);
    puts("output the input begin ===:");
    fputs(buf, output);
    puts("output the input end ===:");
    printf("str:%p buf:%p\n", str, buf);
    return 0;
}
