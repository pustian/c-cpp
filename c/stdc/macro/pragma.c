#include<stdio.h>

int main() {
#pragma message("struct s1, struct s2 内部存储结构相同")
    struct s1{
        int i;
        char ch;
    };
    printf("sizeof struct s1 %d\n", sizeof(struct s1));
//按照1字节方式进行对齐
#pragma pack(1)
    struct s2{
        int i;
        char ch;
    };
    printf("sizeof struct s2 %d\n", sizeof(struct s2));
#pragma pop()
// 取消1字节对齐方式
    return 0;
}
