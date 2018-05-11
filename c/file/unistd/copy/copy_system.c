#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int main() {
    char ch;
    int in;
    int out;

    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    while(read(in, &ch, 1) == 1) {
        write(out, &ch, 1);
    }

    return 0;
}
