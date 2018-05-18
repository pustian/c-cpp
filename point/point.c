#include "point.h"
// gcc -DTEST point.c
void print_point(point *ptr_point) {
    printf("point x:%.2f y:%.2f\n", ptr_point->x, ptr_point->y);
}
#if TEST
int main() {
    point p;
    p.x =1.3; 
    p.y =-1.6;
    print_point(&p);
    return 0;
}
#endif
