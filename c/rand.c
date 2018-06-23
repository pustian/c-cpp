#include<stdlib.h>
#include<stdio.h>

int main() {
    do {
        int j=0;
        for(j=0; j<05; j++) {
            // srand(1);  // 相同种子会出现一样的随机数
            srand((unsigned)time(NULL));
            int i = rand()%500;
            printf("%d\n", i);
        }
        sleep(1);
    }while(1);
    return 0;
}
