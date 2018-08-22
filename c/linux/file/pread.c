#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#define BUFF_SIZE  0xFF

int main(int argc, char *argv[]) {
    char *filename = "./pread.c";
    if(argc > 1) {
        filename = argv[1];
    }

    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
        fprintf(stderr, "Failed to open file:%s\n", filename);
        return -1;
    }

    // 长度
    struct stat s_stat;
    struct stat *ptr_stat = &s_stat;
    int fstat_ret = fstat(fd, ptr_stat);
    printf("file fstat size:%d\n", ptr_stat->st_size);;

    char buffer[BUFF_SIZE+1] = {0};
    off_t offset=0;
    int nread = -1;
    // 读取标准输入到buffer
    if((nread = pread(fd, buffer, BUFF_SIZE, 32))== -1) {
        write(2, "A read error has occurred\n", 26);
    }
    fprintf(stdout, "pread from file:%s size: %d offset=%lu content:\n", filename, nread, offset);
    fprintf(stdout, "%s\n\n", buffer);

//    off_t curr_pos = tell(fd);
    off_t lseek_ret = lseek(fd, 0, SEEK_CUR);
    printf("lseek_t:%d\n", lseek_ret);
//
    // 再读取一次
    if((nread = read(fd, buffer, BUFF_SIZE))== -1) {
        write(2, "A read error has occurred\n", 26);
    }
    fprintf(stdout, "re-read from file:%s size: %d content:\n", filename, nread);
    fprintf(stdout, "%s\n\n", buffer);

//    off_t curr_pos = tell(fd);
    lseek_ret = lseek(fd, 0, SEEK_CUR);
    printf("lseek_t:%d\n", lseek_ret);
    close(fd);
    return 0;
}
