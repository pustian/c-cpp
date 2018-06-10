#include<stdio.h>

int main() {
    int arr[4][2] = {
        {1,5}, 
        {-2, 6 },
        {-3, -7},
        {4, -8},
    };

    int (*arr_ptr)[2] ;


    int i=0;
    for(i=0; i<4; i++) {
        int j=0;
        for(j=0; j<2; j++) {
            printf("%p %4d \t", &arr[i][j], arr[i][j]);
        }
        putchar('\n');
    }

    // 强制转换
    arr_ptr = arr;
    for(i=0; i<4; i++) {
        int j=0;
        for(j=0; j<2; j++) {
            int *ptr = (int *)(arr_ptr + i);
            printf("%p %4d \t", ptr+j, *(ptr+j));
        }
        putchar('\n');
    }

    // 赋值
    arr_ptr = arr;
    for(i=0; i<4; i++) {
        int j=0;
        for(j=0; j<2; j++) {
            printf("%p %4d \t",((int *)(arr_ptr+i)) +j , *(((int *)(arr_ptr+i))+j) );
        }
        putchar('\n');
    }
}
