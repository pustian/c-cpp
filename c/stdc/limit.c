#include <stdio.h>
#include <limits.h>

int main() { 
    printf("The number of bits in a byte 0X%x\n", CHAR_BIT);

    puts("SIGNED CHAR INFO ===");
    printf("The minimum value of SIGNED CHAR = 0X%x\n", SCHAR_MIN);
    printf("The maximum value of SIGNED CHAR = 0X%x\n", SCHAR_MAX);
    printf("The maximum value of UNSIGNED CHAR = 0X%x\n", UCHAR_MAX);
    printf("The sizeof char %d bytes, unsigned char %d bytes\n", sizeof(char), sizeof(unsigned char));

    puts("SHORT INT INFO ===");
    printf("The minimum value of SHORT INT = 0X%x\n", SHRT_MIN);
    printf("The maximum value of SHORT INT = 0X%x\n", SHRT_MAX); 
    printf("The sizeof short int %d bytes\n", sizeof(short int));

    puts("INT INFO ===");
    printf("The minimum value of INT = 0X%x\n", INT_MIN);
    printf("The maximum value of INT = 0X%x\n", INT_MAX);
    printf("The sizeof int %d bytes\n", sizeof(int));

    puts("CHAR INFO ===");
    printf("The minimum value of CHAR = 0X%x\n", CHAR_MIN);
    printf("The maximum value of CHAR = 0X%x\n", CHAR_MAX);
    printf("The sizeof char %d bytes, unsigned char %d bytes\n", sizeof(char), sizeof(unsigned char));


    puts("LONG INFO ===");
    printf("The minimum value of LONG = 0X%x\n", LONG_MIN);
    printf("The maximum value of LONG = 0X%x\n", LONG_MAX);
    printf("The sizeof long %d bytes\n", sizeof(long));
                                          
    return(0);
}
