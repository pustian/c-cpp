#include<stdio.h>

typedef struct {
    int integer;
    char string[24];
} RECORD;
#define RECORD_SIZE (sizeof(RECORD))
#define NUM_RECORD (15)

int main() {
    RECORD record; 

    FILE *fp = NULL;
    fp = fopen("records.dat", "w");
    int i=0;
    // write
    printf("========== write begin ==========\n");
    for(i = 0; i< NUM_RECORD; ++i) {
        record.integer = i;
        sprintf(record.string, "RECORD-%02d", i);
        fprintf(stdout, "record[%2d] integer:%2d string:%s\n", i, record.integer, record.string);
        fwrite(&record, RECORD_SIZE, 1, fp);
    }
    fclose(fp);
    printf("========== write end  ==========\n");

    //read and check
    printf("========== read begin ==========\n");
    fp = fopen("records.dat", "r");
    for(i=0; i<NUM_RECORD; ++i) {
        fread(&record, RECORD_SIZE, 1, fp);
        fprintf(stdout, "record[%2d] integer:%2d string:%s\n", i, record.integer, record.string);
    }
    fclose(fp);
    printf("========== read end  ==========\n");

    // 修改第43条记录整值 43 --> 143 并回写
    fp = fopen("records.dat", "r+");
    printf("========== modified begin index=9==========\n");
    long offset = 0;
    int record_index = 9;
    record.integer = 9*9;
    sprintf(record.string, "RECORD-%02d", record.integer);
    fprintf(stdout, "record integer:%2d string:%s\n", record.integer, record.string);
    fseek(fp, record_index*RECORD_SIZE, SEEK_SET);
    offset = ftell(fp);
    printf("current at %ld\n", offset);
    fwrite(&record, RECORD_SIZE, 1, fp);
    // 修改
    fseek(fp, record_index*RECORD_SIZE, SEEK_SET);
    offset = ftell(fp);
    printf("current at %ld\n", offset);
    fread(&record, RECORD_SIZE, 1, fp);
    fprintf(stdout, "record[%2d] integer:%2d string:%s\n", i, record.integer, record.string);
    fclose(fp);
    printf("========== modified end==========\n");

    //read and check
    printf("========== read begin ==========\n");
    fp = fopen("records.dat", "r");
    for(i=0; i<NUM_RECORD; ++i) {
        fread(&record, RECORD_SIZE, 1, fp);
        fprintf(stdout, "record[%2d] integer:%2d string:%s\n", i, record.integer, record.string);
    }
    fclose(fp);
    printf("========== read end  ==========\n");
    return 0;
}
