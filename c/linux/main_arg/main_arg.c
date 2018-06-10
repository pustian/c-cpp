#include<stdio.h>
int main(int argc, char *argv[]) {
    int arg_index = 0;
    for (arg_index = 0; arg_index <argc; ++arg_index ) {
        printf("arg[%d] value:[%s]\n", arg_index, argv[arg_index]);
    }
    return 0;
}
