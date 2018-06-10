#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Begin\n");
    system("ps -ax &");
    printf("Done\n");
    exit(0);
}
