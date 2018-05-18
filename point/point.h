#ifndef __point_c_
#define __point_c_
#ifdef __cplusplus
extern "C"{
#endif

#include<stdio.h>
typedef struct point {
    float x;
    float y;
} point;

void print_point(point* ptr_point);

#ifdef __cplusplus
}
#endif

#endif
