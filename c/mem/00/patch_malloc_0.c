#include <string.h>
#include "patch_malloc_0.h"
// gcc -DTEST -DMONITOR patch_malloc_0.c

/**
 * 操作数据外记录到结构中
 * patch_malloc_head --> patch_malloc_t
 *                   --> patch_malloc_t
 *                   --> patch_malloc_t
 * 申请时先检查分配的是否可用。
 * 释放时，patch_malloc_t->avail_map
 * +多线程调用需要加锁
 */

patch_malloc_head _patch_malloc_head;
patch_malloc_head *ptr_head=&_patch_malloc_head;
// 通过日志文件可以监控使用情况，甚至使用%
#ifdef MONITOR 
static void monitor() {
    DEBUG("ptr_head=%p patch_size=%d ptr_patch_malloc=%p", 
            ptr_head, ptr_head->patch_size, ptr_head->ptr_patch_malloc);
    int i=0;
    for(i=0; i< _MAX_PATCH_SIZE; ++i) {
        patch_malloc_t *ptr_patch_malloc = &(ptr_head->ptr_patch_malloc[i]);
        DEBUG("index=%d ptr_patch_malloc->data=%p  ptr_patch_malloc=>used_bytes=%d",
                i, ptr_patch_malloc->data, ptr_patch_malloc->used_bytes);
    }
}
#else
static void monitor(){}
#endif
// 开始内存块初始化.
// 内存示例如下
// [ptr_match_head.ptr_patch_malloc[0--_MAX_PATCH_SIZE]  +++]
// [ptr_match_malloc[0].data: _DEFAULT_BLOCK_SIZE        +++]
// [ptr_match_malloc[1].data: _DEFAULT_BLOCK_SIZE        +++]
// [ptr_match_malloc[2].data: _DEFAULT_BLOCK_SIZE        +++]
// [......]
// 一次性分配，内部动态化管理 预期分配管理相对简单。 
// 0 成功 -1: 失败
int init_patch_malloc() {
    DEBUG("++++++ init_patch_malloc begin");
    const size_t head_size = sizeof(patch_malloc_t) * _MAX_PATCH_SIZE ;
    const size_t data_size = _MAX_PATCH_SIZE * _DEFAULT_BLOCK_SIZE;
    const size_t total_size = head_size + data_size;
    void *ptr =  malloc(total_size);
    if(NULL == ptr ) {
        ptr_head->patch_size = 0;
        ptr_head->ptr_patch_malloc = NULL;
        return -1;
    }
    memset((void *)ptr, 0x0,  total_size);

    ptr_head->patch_size = _MAX_PATCH_SIZE;
    ptr_head->ptr_patch_malloc = ptr;
    int i = 0;
    char *ptr_data = ptr + head_size;
    for(i = 0; i< _MAX_PATCH_SIZE; ++i) {
         ptr_head->ptr_patch_malloc[i].data = (char *)ptr_data + i * _DEFAULT_BLOCK_SIZE;
         // ptr_head->ptr_patch_malloc[i].used_bytes = 0; // memset 已经为0
    }
    monitor();
    DEBUG("++++++ init_patch_malloc end");
    return 0;
}

// 销毁内存块结构，释放所有管理的内存
void destory_patch_malloc() {
    // 整块内存
    DEBUG("++++++ destory_patch_malloc begin");
    free(ptr_head->ptr_patch_malloc);
    monitor();
    DEBUG("++++++ destory_patch_malloc end");
}

// 0 成功 0 返回NULL，否则会造成free时异常
void *patch_malloc(size_t num) {
    DEBUG("++++++ patch_malloc begin num = %d", num);
    monitor();

    void *ptr = NULL;
    int i=0;
    if(num > 0 && num <= _DEFAULT_BLOCK_SIZE) {
        do {
            if(0 == ptr_head->ptr_patch_malloc[i].used_bytes) {
                ptr = ptr_head->ptr_patch_malloc[i].data;
                ptr_head->ptr_patch_malloc[i].used_bytes = num;
            }
        } while(NULL == ptr && i++ < _MAX_PATCH_SIZE );
    }
    if(ptr == NULL && i > _MAX_PATCH_SIZE) {
        fprintf(stderr, "ERROR: %d block are using, modified the _MAX_PATCH_SIZE at header\n", _MAX_PATCH_SIZE);
    }
    
    monitor();
    DEBUG("++++++ patch_malloc end result=%p", ptr);

    return ptr;
}

// 0 成功
int patch_free(const void *ptr) {
    DEBUG("++++++ patch_free begin ptr = %p", ptr);
    monitor();
    int i = 0;
    for(i=0; i<_MAX_PATCH_SIZE; ++i){
        if(ptr == ptr_head->ptr_patch_malloc[i].data) {
            ptr_head->ptr_patch_malloc[i].used_bytes = 0;
            break;
        }
    }
    monitor();
    DEBUG("++++++ patch_free end");
    return 0;
}
#ifdef TEST
int main() {
    puts("\ntest00"); test00();
    puts("\ntest01"); test01();
    puts("\ntest02"); test02();
    puts("\ntest03"); test03();
    puts("\ntest04"); test04();
    return 0;
}
// normal usage 
int test00() {
    init_patch_malloc();
    char *ptr19 = patch_malloc(19);
    char *ptr20 = patch_malloc(20);
    char *ptr1 = patch_malloc(1);
    char *ptr2 = patch_malloc(2);
    char *ptr3 = patch_malloc(3);

    patch_free(ptr1);
    char *ptr4 = patch_malloc(14);
    
    patch_free(ptr2);
    ptr2 = patch_malloc(15);
    destory_patch_malloc();
    return 0;
}
// more than _MAX_PATCH_SIZE
int test01() {
    init_patch_malloc();
    char *ptr19 = patch_malloc(19);
    char *ptr20 = patch_malloc(20);
    char *ptr1 = patch_malloc(1);
    char *ptr2 = patch_malloc(2);
    char *ptr3 = patch_malloc(3);
    char *ptr4 = patch_malloc(4); // ptr4 = null;

    patch_free(ptr1);
    ptr4 = patch_malloc(4);
    destory_patch_malloc();
    return 0;
}
// 申请0内存
int test02() {
    init_patch_malloc();
    char *ptr0 = patch_malloc(0);
    char *ptr1 = patch_malloc(1);
    patch_free(ptr0);
    patch_free(ptr1);
    destory_patch_malloc();
    return 0;
}
// more than _DEFAULT_BLOCK_SIZE 
int test03() {
    init_patch_malloc();
    char *ptr21 = patch_malloc(21);
    destory_patch_malloc();
    return 0;
}
//
int test04() {
    init_patch_malloc();
    char *ptr12 = patch_malloc(12);
    patch_free(ptr12);
    patch_free(ptr12);
    destory_patch_malloc();
    return 0;
}
// 多线程测试, 目前应该不支持多线程

#endif
