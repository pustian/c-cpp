#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

int main(int argc, char* argv[]) {
    const char* pattern = "{{( )*(([[:alnum:]]+\\.)*)?[[:alnum:]]+( )*}}";
    regex_t rex;
    int rc;

    if ((rc = regcomp(&rex, pattern, REG_EXTENDED))) {
        fprintf(stderr, "error %d compiling regex\n", rc);
        /* retrieve error here with regerror */
        return -1;
    }

    regmatch_t* matches = malloc(sizeof(regex_t) * (rex.re_nsub + 1));
    if ((rc = regexec(&rex, argv[1], rex.re_nsub + 1, matches, 0))){
        printf("no match\n");
        /* error or no match */
    } else {
        int i=0;
        for(i = 0; i < rex.re_nsub; ++i) {
            printf("match %d from index %d to %d: ", i, matches[i].rm_so, matches[i].rm_eo);
            int j=0;
            for(j = matches[i].rm_so; j < matches[i].rm_eo; ++j) {
                printf("%c", argv[1][j]);
            }   
            printf("\n");
        }
    }
    free(matches);
    regfree(&rex);
    return 0;
}
