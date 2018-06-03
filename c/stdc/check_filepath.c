/********************************************************************
 * tianpusen
 *******************************************************************/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>

#if 1
#define DEBUG(...) \
    do{\
        fprintf(stdout, " DEBUG ");\
        fprintf(stdout, "%s %s ",__TIME__,__DATE__);\
        fprintf(stdout, "%s:%d:%s():",__FILE__,__LINE__,__func__);\
        fprintf(stdout, __VA_ARGS__);\
        fprintf(stdout, "\n");\
    }while(0)
#else
#define DEBUG(...) {}
#endif

#define MAX_FILEPATH_LENGTH 4*1024
#define __FILE_DIR_FLAG '/'
#define MAX_DIR_DEPTH 99
// 只能包含数字，字母 _和/ . 这几个字符
// 目录层级不超过99
int __check_filepath(const char *filepath, int is_dir) {
    int ret = 0;
    if( NULL == filepath || strlen(filepath) >= MAX_FILEPATH_LENGTH) {
        DEBUG("Please check the filepath, it is null or too long more than %d.", MAX_FILEPATH_LENGTH);
        return -1;
    }
    if( (is_dir == 0 && filepath[strlen(filepath) -1 ] == __FILE_DIR_FLAG) 
            || (is_dir == 1 && filepath[strlen(filepath) -1 ] != __FILE_DIR_FLAG) ) {
        DEBUG("Please check the last char of filepath, file end without '/', dir end with '/'");
        return -1;
    }

    // 汉语 utf-8
    int dir_depth = 0;
    do{
        if(*filepath == __FILE_DIR_FLAG ) {
            if(*(filepath + 1) != __FILE_DIR_FLAG ) {
                ++dir_depth;
                if(dir_depth > MAX_DIR_DEPTH) {
                    DEBUG("Please check the filepath, the dir depth more than %d", MAX_DIR_DEPTH);
                    return -1;
                }
            } else {
                DEBUG("Duplicate / not support.");
                return -1;
            }
        }
        // _ 数字, 字母 . /
        if( (! isalpha(*filepath) ) && (! isalnum(*filepath) )
                && (*filepath != __FILE_DIR_FLAG) && (*filepath != '.') ) {
            DEBUG("Please check the filepath, special char is not support.");
            return -1;
        }
    }while(*(++filepath) );

    return ret;
}

int main(int argc, char *argv[]) {
    char *filepath = "/test";
    int is_dir = 0;
    if(argc > 1) {
        filepath = argv[1];
    }
    if(argc > 2) {
        is_dir = atoi(argv[2]);
    }
    int ret = __check_filepath(filepath, is_dir);
    return 0;
}
