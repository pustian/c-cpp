#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/******************************************************
 * 全局区  global变量和 常量所在地址
 * 代码区  load函数代码的地方
 * 栈区    函数调用
 * 堆区    malloc 指出的地址
 *
 *
 *****************************************************/
char *string1 = "global string store in global area";
char *string2 = "global string 2 store in global area";
void show_global_area() {
    printf("global string addr1=%p val=%s\n", string1, string1);
    printf("global string addr2=%p val=%s\n", string2, string2);
    printf("global string addr3=%p val=%s\n", 
            "global string store in global area", 
            "global string store in global area");
}

void show_heap_area() {
    char *p1 = malloc(15);
    char *p2 = malloc(15);
    strcpy(p1, "hello world 1");
    strcpy(p2, "hello world 2");
    printf("head addr1=%p len=%d val=%s\n",p1, 15,  p1);
    printf("head addr2=%p len=%d val=%s\n",p2, 15,  p2);
    free(p2);
    free(p1);
}

void show_stack_area() {
    int x;
    int y;
    char str[10];
    int z;
    printf("stack x   addr=%p sizeof=%d \n", &x, sizeof(int));
    printf("stack y   addr=%p sizeof=%d \n", &y, sizeof(int));
    printf("stack str addr=%p sizeof=%d \n", str, sizeof(str)/sizeof(char));
    printf("stack z   addr=%p sizeof=%d \n", &z, sizeof(int));
}

// funct
void show_code_area() {
    printf("func show_global_area addr %p\n", show_global_area);
    printf("func show_heap_area   addr %p\n", show_heap_area);
    printf("func show_stack_area  addr %p\n", show_stack_area);
    printf("func show_code_area   addr %p\n", show_code_area);
    printf("func printf           addr %p\n", printf);
}

int main() {
    puts("===show_global_area");
    show_global_area();
    puts("===show_heap_area");
    show_heap_area();
    puts("===show_stack_area");
    show_stack_area();
    puts("===show_code_area");
    show_code_area();
    return 0;
} 
