#include<stdio.h>
#include<errno.h>

int main() {
    char tmpname[L_tmpnam];
    char *filename = NULL;;
    FILE *tmpfp = NULL;

    // 警告
    filename = tmpnam(tmpname);
    printf("Temporary file name is:%s\n", filename);
    tmpfp = tmpfile();
    if(tmpfp) {
        printf("Opened a temporary file OK\n");
        fclose(tmpfp);
    } else {
        printf("tmpfile failed:%s", strerror(errno));
    }


    return 0;
}
