#include<unistd.h>
#include<stdio.h>
#include<getopt.h>
// gcc -g  argopt_long.c
// ./a.out -im -lr "hello" "tian" -f argopt.c -u
int main(int argc, char* argv[]) {
    int opt;
    struct option longopts[] = {
        {"initialize", 0, NULL, 'i'},
        {"file", 1, NULL, 'f'},
        {"list", 0, NULL, 'l'},
        {"restart", 0, NULL, 'r'},
        {0, 0, 0, 0},
    };

    // 选项处理完毕返回-1
    while((opt = getopt_long(argc, argv, "if:lr", longopts, NULL) ) != -1) {
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
