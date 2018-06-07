#ifndef __MALLOC_1_H_
#define __MALLOC_1_H_
#include <stdio.h>
#include <stdlib.h>

#define DEBUG(...) \
    do{\
        fprintf(stdout, "DEBUG ");\
        fprintf(stdout, "%s %s ",__TIME__,__DATE__);\
        fprintf(stdout, "%s:%d:%s():",__FILE__,__LINE__,__func__);\
        fprintf(stdout, __VA_ARGS__);\
        fprintf(stdout, "\n");\
    }while(0)
    
/**
 * 4k 以内的都算是小块管理  * 4k=2^12 mapping
 * 此处只做小块的内存管理
 */
#ifdef TEST
const size_t _DEFAULT_BLOCK_SIZE=64;
const size_t _MAX_PATCH_SIZE = 5;
const size_t _MIN_BLOCK_SIZE = 8;
#else
const size_t _DEFAULT_BLOCK_SIZE = 4*1024; // 默认内存块4k
const size_t _MAX_PATCH_SIZE = 1024; // 最多碎片化1k内存. 
const size_t _MIN_BLOCK_SIZE = 512;  // 一块内再次划分使用提高使用率
#endif
typedef struct _map_t {
    // uint8_t index;
    void *ptr;
    uint8_t used;
}map_t;
typedef struct _malloc_t {
    void *data;          // 4k内存起始地址
    size_t used_bytes;   // 使用字节数, <= _DEFAULT_BLOCK_SIZE
    uint16_t block_size; // 均分块 8*512, 4*1024, 2*2048, 4096
    map_t mapping[8];
    uint8_t no_avail;    // 0 available, 1 no available
}malloc_t;
typedef struct _malloc_head {
    malloc_t *ptr_malloc; // 内存结构起始地址
    size_t p_size;        // 内存块大小 <= _MAX_PATCH_SIZE
}malloc_head_t;

extern malloc_head_t *ptr_head; 

// 开始时调用
int init_malloc();
// 程序结束时调用
void destroy_malloc();
// 分配内存使用
void *p_malloc(size_t num);
// 取消
int p_free(const void *ptr);

#endif /* __MALLOC_1_H_ */

