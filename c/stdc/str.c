#include<stdio.h>
#include<string.h>
int main() {
    char str1[11] = "Hello";
    char str2[11] = "World";
    char str3[11] = {0};
    int  len ;
    printf("str1\t"); puts(str1);
    printf("str2\t"); puts(str2);
    printf("str3\t"); puts(str3);
    // 复制 str1 到 str3
    strcpy( str3, str1);
    printf("str(str3, str1) str3\t");puts(str3);
    printf("strcmp(str3, str1) %d\n", strcmp(str3, str1));
    
    // 连接 str1 和 str2
    strcat( str1, str2);
    printf("strcat(str1, str2) str1=%s str2=%s\n", str1, str2);

    printf("strcmp(str3, str1) %d\n", strcmp(str3, str1));
    
    // 连接后，str1 的总长度
    printf("str1 len %d\n", strlen(str1));
    printf("str2 len %d\n", strlen(str2));
    printf("str3 len %d\n", strlen(str3));
}
