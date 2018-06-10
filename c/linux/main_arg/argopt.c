#include<unistd.h>
#include<stdio.h>
// gcc -g -o argopt argopt.c
// ./argopt -im -lr "hello" "tian" -f argopt.c -u
// ./a.out -i
// ./a.out -i aa
// ./a.out -l
// ./a.out -r
// ./a.out -f
// ./a.out -u
int main(int argc, char* argv[]) {
    int opt;
    // 选项处理完毕返回-1
    while((opt = getopt(argc, argv, "if:lr")) != -1) {
        switch(opt) {
        case 'i':
        case 'l':
        case 'r':
            printf("option:%c\n", opt);
            break;
        // 有关联值，则关联值放到optarg
        case 'f':
            printf("filename:%s\n", optarg);
            break;
        // 选项需要关联值，但未提供
        case ':':
            printf("option:%c needs a value\n", optopt);
            break;
        // 无法识别的选项，返回？保存在optopt中
        case '?':
            printf("unknow option:%c\n", optopt);
            break;
        }
    }
    // 外部变量optind 被设置为下一个待处理参数的索引
    for(; optind < argc; ++optind) {
        printf("argument:%s\n", argv[optind]);
    }
    return 0;
}
