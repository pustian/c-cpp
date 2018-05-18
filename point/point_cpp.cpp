#include<iostream>
#include<memory>
#include "point.h"
//
// g++ -c point.c
// g++ -c point_cpp.cpp
// g++ -o point point_cpp.o  point.o
// ./point

int main() {
    point _point;
    point *ptr_point = new point;
    ptr_point->x = 1.1;
    _point.y = 2.2;
    print_point(ptr_point);

    std::cout<<"x:"<<ptr_point->x 
        <<"y:"<<ptr_point->y
        <<std::endl;
    
    delete ptr_point;
       
    return 0;
}
