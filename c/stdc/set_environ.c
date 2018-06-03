#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *var = NULL;
    char *value = NULL;
    int ret = 0;

    if(argc == 1 || argc > 3 ) {
        fprintf(stderr, "usage: environ var [value]\n");
        ret = 1;
        goto end;
    }

    var = argv[1];
    value = getenv(var);
    if(value) {
       printf("Variable %s has value %s\n", var, value); 
    } else {
       printf("Variable %s has no value\n", var);
    }

    if(argc == 3) {
        char *string = NULL;
        value = argv[2];
        string =  malloc(strlen(var) + strlen(value) + 2) ;
        if(!string) {
            fprintf(stderr, "out of memory\n");
            ret = 1;
            goto end;
        }
        strcpy(string, var);
        strcat(string, "=");
        strcpy(string, value);
        printf("Calling putenv with:%s\n", string);
        if(putenv(string) != 0 ) {
            fprintf(stderr, "putenv failed\n");
            ret = 1;
            free(string);
            goto end;
        } else {
            free(string);
        }

        value = getenv(var);
        if(value) {
           printf("new value of %s is %s\n", var, value); 
        } else {
           printf("new value of %s is NULL?\n", var);
        }
    }

end: 
    return ret;
}
