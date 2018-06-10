#include<stdio.h>
int main(int argc, char *argv[]) {
    char i_str[4] = {0};
    printf("addr i_str+0:%p\n",i_str+0);
    printf("addr i_str+1:%p\n",i_str+1);
    printf("addr i_str+4:%p\n",i_str+4);
    
    int i = 0;
    printf("addr &i+0:%p\n",&i);
    printf("addr &i+1:%p\n",&i+1);

    char *c_p = (char *)&i;
    printf("c_p+0:%p %x \n", c_p+0, *(c_p+0));
    printf("c_p+1:%p %x \n", c_p+1, *(c_p+1));
    printf("c_p+2:%p %x \n", c_p+2, *(c_p+2));
    printf("c_p+3:%p %x \n", c_p+3, *(c_p+3));
    printf("i    :%p %x\n", &i, i);
    
    *c_p = 0x0f;
    *(c_p+1) = 0x1a;
    *(c_p+2) = 0x2b;
    *(c_p+3) = 0x3c;
    printf("c_p+0:%p %x \n", c_p+0, *(c_p+0));
    printf("c_p+1:%p %x \n", c_p+1, *(c_p+1));
    printf("c_p+2:%p %x \n", c_p+2, *(c_p+2));
    printf("c_p+3:%p %x \n", c_p+3, *(c_p+3));
    printf("i    :%p %x\n", &i, i);

    i = 0xf1234567;
    printf("c_p+0:%p %x \n", c_p+0, *(c_p+0));
    printf("c_p+1:%p %x \n", c_p+1, *(c_p+1));
    printf("c_p+2:%p %x \n", c_p+2, *(c_p+2));
    printf("c_p+3:%p %x \n", c_p+3, *(c_p+3));
    printf("i    :%p %x\n", &i, i);

    return 0;
}

