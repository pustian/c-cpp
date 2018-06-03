#include<stdio.h>
#include<errno.h>

int main() {
    char template[] = "temp-XXXXXX";  /// must XXXXXX 结尾
    int fd = -1;
    fd = mkstemp(template);
    if(fd > 0) {
        printf("Opened a temporary file OK fd:%d template:%s\n", fd, template);
        close(fd);
    } else {
        printf("tmpfile failed:%s", strerror(errno));
    }

    return 0;
}
