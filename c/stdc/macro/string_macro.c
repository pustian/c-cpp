#include<stdio.h>

#define attanch(result) (##result)
#define STR(string) (#(string))

int main() {
    puts((" OK"));
    return 0;
}

