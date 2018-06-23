#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

#define BUFF_SIZE  0xFF

int main(int argc, char *argv[]) {
    char *filename = "./write.out";
    if(argc > 1) {
        filename = argv[1];
    }

    int fd = open(filename, O_WRONLY);
    if(fd < 0) {
        fprintf(stderr, "Failed to open file:%s\n", filename);
        return -1;
    }
   
    char *source = "123456789\n123456789\nabcdeABCDE\n!@#$%^&*(\n";
    size_t source_len = strlen(source);
    int nwrite = -1;
    if( (nwrite = write(fd, source, source_len)) == -1 ) {
        write(2, "A write error has occured\n", 27);
    }

    fprintf(stdout, "write to file file:%s size:%d\n", filename, nwrite);

    off_t lseek_ret = lseek(fd, source_len/2, SEEK_SET);
    printf("lseek_t:%d\n", lseek_ret);

    // 再写一次
    if((nwrite = write(fd, source, source_len) ) == -1) {
        write(2, "A write error has occured\n", 27);
    }
    fprintf(stdout, "re-write to file file:%s size:%d\n", filename, nwrite);

    close(fd);

    return 0;
}
