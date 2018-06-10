#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "malloc_1.h"
// gcc -DTEST -DMONITOR malloc_1.c

/**
 * 操作数据外记录到结构中
 * malloc_head_t --> malloc_t
 *               --> malloc_t
 *               --> malloc_t
 * 申请时先检查分配的是否可用。
 * +多线程调用需要加锁
 */

malloc_head_t _malloc_head_t;
malloc_head_t *ptr_head=&_malloc_head_t;
// 通过日志文件可以监控使用情况，甚至使用%
#ifdef MONITOR 
static void monitor() {
    DEBUG("ptr_head=%p p_size=%d ptr_malloc=%p", 
            ptr_head, ptr_head->p_size, ptr_head->ptr_malloc);
    int i=0;
    for(i=0; i< _MAX_PATCH_SIZE; ++i) {
        malloc_t *ptr_malloc = &(ptr_head->ptr_malloc[i]);
        DEBUG("index=%d ptr_malloc data=%p used_bytes=%d block_size=%d no_avail=%d", i, 
                ptr_malloc->data, (int)ptr_malloc->used_bytes, (int)ptr_malloc->block_size, (int)ptr_malloc->no_avail);
        int j=0;
        if(ptr_malloc->block_size > 0 ) {
            int block_count = _DEFAULT_BLOCK_SIZE/ptr_malloc->block_size;
            for(j=0; j<block_count; ++j) {
                DEBUG("\t\t mapping[%d] used=%d ptr=%p",j, (int)ptr_malloc->mapping[j].used, ptr_malloc->mapping[j].ptr);
            }
        }
    }
}
#else
static void monitor(){}
#endif
/**
 *
 */
static void *_alloc_init(malloc_t *ptr, size_t num) {
    int i = 0;
    if(0 < num && num <= _MIN_BLOCK_SIZE) {
        ptr->block_size = _MIN_BLOCK_SIZE;
        for(i=0; i<_DEFAULT_BLOCK_SIZE/ptr->block_size; ++i) {
            ptr->mapping[i].ptr = (char *)ptr->data + i * _MIN_BLOCK_SIZE;
            ptr->mapping[i].used = 0;
        }
    } else if(_MIN_BLOCK_SIZE  < num && num <= _MIN_BLOCK_SIZE*2 ) {
        ptr->block_size = _MIN_BLOCK_SIZE*2;
        for(i=0; i<_DEFAULT_BLOCK_SIZE/ptr->block_size; ++i) {
            ptr->mapping[i].ptr = (char *)ptr->data + i * _MIN_BLOCK_SIZE*2;
            ptr->mapping[i].used = 0;
        }
    } else if(_MIN_BLOCK_SIZE*2 < num && num <= _MIN_BLOCK_SIZE*4 ) {
        ptr->block_size = _MIN_BLOCK_SIZE*4;
        for(i=0; i<_DEFAULT_BLOCK_SIZE/ptr->block_size; ++i) {
            ptr->mapping[i].ptr = (char *)ptr->data + i * _MIN_BLOCK_SIZE*4;
            ptr->mapping[i].used = 0;
        }
    } else if(_MIN_BLOCK_SIZE*4 < num && num <= _MIN_BLOCK_SIZE*8) {
        ptr->block_size = _MIN_BLOCK_SIZE*8;
        for(i=0; i<_DEFAULT_BLOCK_SIZE/ptr->block_size; ++i) {
            ptr->mapping[i].ptr = (char *)ptr->data + i * _MIN_BLOCK_SIZE*8;
            ptr->mapping[i].used = 0;
        }
        ptr->no_avail = 1;
    }
    ptr->mapping[0].used = 1;
    ptr->used_bytes += num;
    
    return (void *)(ptr->data);
}
static void *_re_alloc(malloc_t *ptr, size_t num) {
//    if(ptr->block_size == 0) {
//        ptr->block_size = _DEFAULT_BLOCK_SIZE;
//    }
    int block_count = _DEFAULT_BLOCK_SIZE/ptr->block_size;
    void *ret_ptr = NULL;
    int used_block_count = 0;
    int i =0;
    for(i =0; i< block_count; ++i) {
        if(0 == ptr->mapping[i].used) {
            ptr->mapping[i].used = 1;
            ret_ptr = ptr->mapping[i].ptr;
        } else {
            ++used_block_count;
        }
    }
    if(1 == (block_count - used_block_count) ) {
        ptr->no_avail =1;
    }
    ptr->used_bytes += num;
}
/**/
static void _free(malloc_t *ptr_malloc, const void *ptr) {
//    if(ptr->block_size == 0) {
//        ptr->block_size = _DEFAULT_BLOCK_SIZE;
//    }

    int block_count = _DEFAULT_BLOCK_SIZE/ptr_malloc->block_size;
    int used_block_count = 0;
    int i=0;
    for(i=0; i<block_count; ++i) {
        if(1 == ptr_malloc->mapping[i].used && ptr == ptr_malloc->mapping[i].ptr) {
            ptr_malloc->mapping[i].used = 0;
            ++used_block_count ;
        }
    }
    if(1 == ptr_malloc->no_avail) {
        ptr_malloc->no_avail = 0;
        ptr_malloc->used_bytes -= ptr_malloc->block_size;
    }
    // if(1 == (block_count - used_block_count) ) {
    //     ptr->no_avail = 0;
    // }
    // 该页可重新分配使用
    if(0 == ptr_malloc->used_bytes) {
        ptr_malloc->block_size = 0;
        for(i=0; i<block_count; ++i) {
            ptr_malloc->mapping[i].ptr = NULL;
            ptr_malloc->mapping[i].used = 0;
        }
    }
}
// 开始内存块初始化.
// 内存示例如下
// [ptr_match_head.ptr_malloc[0--_MAX_PATCH_SIZE]  +++]
// [ptr_match_malloc[0].data: _DEFAULT_BLOCK_SIZE        +++]
// [ptr_match_malloc[1].data: _DEFAULT_BLOCK_SIZE        +++]
// [ptr_match_malloc[2].data: _DEFAULT_BLOCK_SIZE        +++]
// [......]
// 一次性分配，内部动态化管理 预期分配管理相对简单。 
// 0 成功 -1: 失败
int init_malloc() {
    DEBUG("++++++ init_malloc begin");
    const size_t head_size = sizeof(malloc_t) * _MAX_PATCH_SIZE ;
    const size_t data_size = _MAX_PATCH_SIZE * _DEFAULT_BLOCK_SIZE;
    const size_t total_size = head_size + data_size;
    void *ptr =  malloc(total_size);
    if(NULL == ptr ) {
        ptr_head->p_size = 0;
        ptr_head->ptr_malloc = NULL;
        return -1;
    }
    memset((void *)ptr, 0x0,  total_size);

    ptr_head->p_size = _MAX_PATCH_SIZE;
    ptr_head->ptr_malloc = ptr;
    int i = 0;
    char *ptr_data = ptr + head_size;
    for(i = 0; i< _MAX_PATCH_SIZE; ++i) {
         ptr_head->ptr_malloc[i].data = (char *)ptr_data + i * _DEFAULT_BLOCK_SIZE;
         // ptr_head->ptr_malloc[i].used_bytes= 0; // ptr_head->ptr_malloc[i]中默认值0, memset 已经为0
    }
    monitor();
    DEBUG("++++++ init_malloc end");
    return 0;
}

// 销毁内存块结构，释放所有管理的内存
void destroy_malloc() {
    // 整块内存
    DEBUG("++++++ destroy_malloc begin");
    free(ptr_head->ptr_malloc);
    monitor();
    DEBUG("++++++ destroy_malloc end");
}

// 0 成功 0 返回NULL，否则会造成free时异常
void *p_malloc(size_t num) {
    DEBUG("++++++ p_malloc begin num = %d", num);
    monitor();

    void *ptr = NULL;
    int i=0;
    if(num > 0 && num <= _DEFAULT_BLOCK_SIZE) {
        do {
            malloc_t *ptr_malloc = &(ptr_head->ptr_malloc[i]);
            if((uint8_t)0 == ptr_malloc->no_avail) {
                if((uint16_t)0 == ptr_malloc->block_size) { // 首次申请
                    ptr = _alloc_init(ptr_malloc, num);
                // } else if(ptr_malloc->block_size >= num ) { // 已有block内 是否可行,可添加优化为 
                } else if(num <= ptr_malloc->block_size && ptr_malloc->block_size < 2*num ) { 
                    ptr = _re_alloc(ptr_malloc, num);
                } else {                             // 该页不可用或是不合适
                    continue;
                }
            }
        } while(NULL == ptr && i++ < _MAX_PATCH_SIZE );
    }
    if(ptr == NULL && i > _MAX_PATCH_SIZE) {
        fprintf(stderr, "ERROR: %d block are using, modified the _MAX_PATCH_SIZE at header\n", _MAX_PATCH_SIZE);
    }
    
    monitor();
    DEBUG("++++++ p_malloc end result=%p", ptr);

    return ptr;
}

// 0 成功
int p_free(const void *ptr) {
    DEBUG("++++++ p_free begin ptr = %p", ptr);
    monitor();
    int i = 0;
    for(i=0; i< _MAX_PATCH_SIZE; ++i){
        if(ptr_head->ptr_malloc[i].data <= ptr && ptr < ptr_head->ptr_malloc[i].data + _DEFAULT_BLOCK_SIZE) {
            _free(&(ptr_head->ptr_malloc[i]), ptr);       
            break;
        }
    }
    monitor();
    DEBUG("++++++ p_free end");
    return 0;
}
#ifdef TEST
int main() {
    puts("\ntest00"); test00();
//    puts("\ntest01"); test01();
//    puts("\ntest02"); test02();
//    puts("\ntest03"); test03();
//    puts("\ntest04"); test04();
    return 0;
}
// normal usage 
int test00() {
    init_malloc();
    char *ptr19 = p_malloc(32);
    char *ptr20 = p_malloc(64);
    char *ptr1 = p_malloc(32);
    char *ptr2 = p_malloc(16);
    char *ptr3 = p_malloc(8);
    char *ptr4 = p_malloc(8);

    p_free(ptr19);
    char *ptr5 = p_malloc(14);
    
//    p_free(ptr2);
    ptr2 = p_malloc(17);
    destroy_malloc();
    return 0;
}
// // more than _MAX_PATCH_SIZE
// int test01() {
//     init_malloc();
//     char *ptr19 = p_malloc(19);
//     char *ptr20 = p_malloc(20);
//     char *ptr1 = p_malloc(1);
//     char *ptr2 = p_malloc(2);
//     char *ptr3 = p_malloc(3);
//     char *ptr4 = p_malloc(4); // ptr4 = null;
// 
//     p_free(ptr1);
//     ptr4 = p_malloc(4);
//     destroy_malloc();
//     return 0;
// }
// // 申请0内存
// int test02() {
//     init_malloc();
//     char *ptr0 = p_malloc(0);
//     char *ptr1 = p_malloc(1);
//     p_free(ptr0);
//     p_free(ptr1);
//     destroy_malloc();
//     return 0;
// }
// // more than _DEFAULT_BLOCK_SIZE 
// int test03() {
//     init_malloc();
//     char *ptr21 = p_malloc(21);
//     destroy_malloc();
//     return 0;
// }
// //
// int test04() {
//     init_malloc();
//     char *ptr12 = p_malloc(12);
//     p_free(ptr12);
//     p_free(ptr12);
//     destroy_malloc();
//     return 0;
// }
// // 多线程测试, 目前应该不支持多线程
// 
#endif
