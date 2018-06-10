#include <stdio.h>
#include <stdlib.h>

void get_mem(void **p) {
    void *ptr = malloc(sizeof(int));
    printf("func:%p\n", ptr);
    *p = ptr;
}
int main() {
    int *p0 = malloc(sizeof(int));
    int *ptr = NULL;
    get_mem((void *)&ptr);
    printf("p0:%p ptr:%p\n", p0, ptr);
    putchar('\n');

    return 0;
}
