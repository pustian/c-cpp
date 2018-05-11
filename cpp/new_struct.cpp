#include<stdio.h>
typedef struct point {
    float x;
    float y;
} point;

int main() {
    point _point;
    point *ptr_point = new point;
    delete ptr_point;
    return 0;
}
