#include<unistd.h>
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stdlib.h>

typedef struct {
    int integer;
    char string[24];
} RECORD;
#define RECORD_SIZE (sizeof(RECORD))
#define NUM_RECORD (100)
int main() {
    RECORD record;
    int i=0, f=0;
    FILE *fp = NULL;

    fp = fopen("records.dat", "w+");
    for(i = 0; i< NUM_RECORD; ++i) {
        record.integer = i;
        sprintf(record.string, "RECORD-%02d", i);
        fwrite(&record, RECORD_SIZE, 1, fp);
    }
    fclose(fp);

    // 修改第43条记录整值 43 --> 143 并回写
    record.integer = 143;
    sprintf(record.string, "RECORD-%02d", record.integer);
    fp = fopen("records.dat", "r+");
    fseek(fp, 43* RECORD_SIZE, SEEK_SET);
    fwrite(&record, RECORD_SIZE, 1, fp);
    fclose(fp);

    // linux 2.0以上
    int fd = open("records.dat", O_RDWR);
    RECORD *mapped = NULL;
    // 创建指向内存区域的指针
    mapped = (RECORD *)mmap(0, NUM_RECORD * RECORD_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    mapped[43].integer = 234;
    sprintf(record.string, "RECORD-%02d", record.integer);
    // 内存修改回写到映射文件中
    msync((void *)mapped, NUM_RECORD*RECORD_SIZE, MS_ASYNC);
    // 释放内存
    munmap((void *)mapped, NUM_RECORD*RECORD_SIZE);
    close(fd);

    return 0;
}
