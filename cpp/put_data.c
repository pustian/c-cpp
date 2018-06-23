#include<stdio.h>
//  gcc -DTEST display_data.c
void  put_hex(char *data, int length, int line_bytes) {
//    printf("show data begin args length:%d\n", length);
    int i = 0;
    for(i = 0; i < length; i++) {
        printf("%9X ", 0xff &data[i]);
        if((i+1)%4 == 0)  putchar('|');
        if((i+1)%line_bytes == 0) putchar('\n');
        fflush(stdout);
    }
//    if((i+1)%line_bytes ) putchar('\n');
//    printf("show data end\n");
}

void put_binary_char(char ch) {
    int i =0;
    int mask = 0x01;
    for(i = 0; i< 8 ; ++i) {
        int output_bit = (ch & mask<<(7-i));
        putchar(output_bit >= 1?'1':'0');
        if(i == 3) {
            putchar(' ');
        }
    }
    putchar(' ');
}
void put_binary(char *data, int length, int line_bytes) {
//    printf("show data begin args length:%d\n", length);
    int i = 0;
    for(i = 0; i < length; i++) {
        put_binary_char(data[i]);
        if((i+1)%4 == 0)  putchar('|');
        if((i+1)%line_bytes == 0) putchar('\n');
        fflush(stdout);
    }
//    if((i+1)%line_bytes == 0) putchar('\n');
 //   printf("show data end\n");
}

// #ifdef TEST
int main() {
    char ch = 0x33;
    printf("ch:%d 0x%x\n", ch, ch);
    put_binary_char(ch);
    putchar('\n');

    long l = 0x1a2b3c4d5e6f7081L; 
    printf("%ld 0x%lx\n", l, l);
    put_hex((char *)(&l), sizeof(long), 4);
//    putchar('\n');
    put_binary((char *)(&l), sizeof(long), 4);
    putchar('\n');

    int i = 0x3f4b57f3; 
    printf("%d 0x%x\n", i, i);
    put_hex((char *)(&i), sizeof(int), 4);
//    putchar('\n');
    put_binary((char *)(&i), sizeof(int), 4);
    putchar('\n');

}
// #endif
