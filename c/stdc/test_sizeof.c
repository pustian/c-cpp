#include<stdio.h>

struct struct_sizeof{
    char ch[0]; // sizeof =0
    int a;
    int b;
    char *charr;
};
int main() {
    printf("char: %d\n", sizeof(char));
    printf("short: %d\n", sizeof(short));
    printf("int: %d\n", sizeof(int));
    printf("long: %d\n", sizeof(long));
    printf("long long: %d\n", sizeof(long long));
    printf("float: %d\n", sizeof(float));
    printf("double: %d\n", sizeof(double));
    printf("long double: %d\n", sizeof(long double));

    printf("pointer char: %d\n", sizeof(char*));
    printf("pointer int: %d\n", sizeof(int*));
    printf("pointer long long: %d\n", sizeof(long long*));
    printf("pointer double: %d\n", sizeof(double*));
    printf("pointer long double: %d\n", sizeof(long double*));
    
    char arrch0[0];
    char arrch1[9];
    printf("array 0 char: %d\n", sizeof(arrch0));
    printf("array 9 char: %d\n", sizeof(arrch1));
    char *arrch0_ptr = arrch0;
    char *arrch1_ptr = arrch1;
    printf("array 0 point: %d\n", sizeof(arrch0_ptr));
    printf("array 9 point: %d\n", sizeof(arrch1_ptr));
    printf("array 0 point refer: %d\n", sizeof(*arrch0_ptr));
    printf("array 9 point refer: %d\n", sizeof(*arrch1_ptr));

    int arrint0[0];
    int arrint1[9];
    printf("array 0 int: %d\n", sizeof(arrint0));
    printf("array 9 int: %d\n", sizeof(arrint1));
    
    printf("%d\n",sizeof(struct struct_sizeof));
    printf("%d\n",sizeof(int));
    struct struct_sizeof var_struct;
    printf("%d\n",sizeof(var_struct.ch));
    printf("%d\n",sizeof(var_struct.charr));
    
    printf("'hello world':%d\n",sizeof("hello world"));
    char *helloworld = "hello world";
    printf("'hello world' pointer:%d\n",sizeof(helloworld));
    printf("'hello world' ref:%d\n",sizeof(*helloworld));

    printf("off_t:%d\n", sizeof(off_t) );
    printf("size_t:%d\n", sizeof(size_t) );
    printf("ssize_t:%d\n", sizeof(ssize_t) );

    return 0;
}
