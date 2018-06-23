#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

// 目录下与当前时间间隔多久修改过的文件
void dir_file_modifed(char *dirpath/*, char *filename[256]*/, time_t current, unsigned int interval ) {
    struct stat stat_buf;
    // is dir
    int ret = lstat(dirpath, &stat_buf);
    if(ret < 0) {
        printf("dir=%s lstat error!\n", dirpath);
    } else {
        DIR *dirptr =NULL;
        if(( dirptr = opendir(dirpath)) ==NULL) {
            printf("%s error opendir failed\n", dirpath);

        } else {
            int i=0;
            struct dirent* entry;
            char buf[1024]={0};
            while(entry=readdir(dirptr)) {                                                                                   
                printf("index=%d name=%s\n",i,entry->d_name);                                                                   
                if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) {
                    printf("\nd_name[%s]\n", entry->d_name);
                    continue;
                }
                strcat(buf, dirpath);
                strcat(buf, "/");
                strcat(buf, entry->d_name);
                puts(buf);
                ret = lstat(buf, &stat_buf);
                if(ret < 0) {
                    printf("file=%s lstat error!\n", buf);
                }
                if(! S_ISDIR(stat_buf.st_mode) ) {
                    printf("    file=%s current=%ld interval=%u is_modified=%d\n",
                            buf, current, interval, is_modified_file(buf, current, interval) ) ;
                }
                memset(buf, 0x0, 1024);
                i++;                                                                                                         
            };
            closedir(dirptr);  
        }
    }
}
// interval时间段内做过更新
int is_modified_file(char *filepath, time_t current, unsigned int interval) {
    struct stat stat_buf;
    int ret = lstat(filepath, &stat_buf);
    if(ret < 0) {
        printf("lstat file=%s error!\n", filepath);
        ret = 0;
    } else {
        time_t modified_time = stat_buf.st_mtime;
        // current - modified_time < interval
        time_t interval_time = current - modified_time;
        ret = interval_time <= interval;    
        printf("file modified time=%ld curr=%ld\n", modified_time, current);
        printf("interval=%d %d sec modified\n",interval_time,  interval);
    }
    return ret;
}
int main() {
    time_t current = time(NULL);
//    char *filename = "/home/parafs/workspace/c-cpp/c/linux/file/simple_read.c";
//    int is_modified_file_ret = is_modified_file(filename, current, 30*60);
//    printf("is_modified_file_ret %d\n", is_modified_file_ret);
    char *dirpath="/home/parafs/workspace/c-cpp/c/app";
    dir_file_modifed(dirpath, current, 3000);
        
    return 0;
}
