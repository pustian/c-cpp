#include<stdio.h>
//  gcc -DTEST display_data.c
static void  display_hex(char *data, int length) {
    printf("show data begin args length:%d\n", length);
    int i = 0;
    for(i = 0; i < length; i++) {
        printf("%3X", 0xff &data[i]);
        if((i+1)%8 == 0)  putchar('|');
        if((i+1)%32 == 0) putchar('\n');
        fflush(stdout);
    }
    if((i+1)%32 ) putchar('\n');
    printf("show data end\n");
}

static void display_binary(char *data, int length) {
}

// #ifdef TEST
int main() {
    long l = 0x1a2b3c4d5e6f7081L; 
    display_hex((char *)(&l), sizeof(long));
    printf("l:%ld %lx\n", l, l);

    int i = 0x1a2b3c4d; 
    display_hex((char *)(&i), sizeof(int));
    printf("i:%d %x\n", i, i);

}
// #endif
