#include <stdio.h>

int main() {
    const char *menu[] = {
        "open file",
        "edit",
        "about",
    };

    printf("len %d\n", sizeof(menu)/sizeof(void *)) ;
    int i=0; 
    for(i=0; i< 3; ++i) {
        printf("%d %p %s\n", i, menu[i], menu[i] );
    }

    return 0;
}
