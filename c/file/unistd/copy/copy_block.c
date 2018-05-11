#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BLOCK_SIZE 125
int main() {
    char block[BLOCK_SIZE];
    int in;
    int out;
    int nread;

    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    while(nread = read(in, block, sizeof(block)) > 0) {
        write(out, block, nread);
    }

    int cls_out = close(out);
    int cls_in = close(in);

    return 0;
}
