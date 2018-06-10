#include <stdio.h>
#include <string.h>

int main () {
    int ret;
    FILE *fp;
    char filename[] = "abwwfile.txt";
    fp = fopen(filename, "w");
    fprintf(fp, "%s", "这里是 runoob.com");
    fclose(fp);
    // 不存在文件删除
    ret = remove(filename);
    if(ret == 0) {
        puts("文件删除成功");
    } else {
        puts("错误：不能删除该文件");
    }
                            
    return(0);
}
