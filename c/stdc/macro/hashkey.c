#include<stdio.h>
#define STR(a)  #a
#define CONNECT(a, b) a##b 
#define TEST(a) STR(a)
int main() {
    puts(STR(CONNECT(tian, pusen)));
    puts(TEST(CONNECT(tian, pusen)));
    return 0;
}
