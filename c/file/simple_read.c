#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main() {
    char buffer[BUFSIZ];
    int nread;

    // 读取标准输入到buffer
    if((nread = read(0, buffer, BUFSIZ))== -1) {
        write(2, "A read error has occurred\n", 26);
    }

    // 将读取的内容输出
    if((write(1, buffer, nread) ) != nread) {
        write(2, "A write error has occurred\n", 27);
    }

    return 0;
}
