#include<stdio.h>
#include<regex.h>
#include<string.h>

#define MAX_FILEPATH_LENGTH 4*1024
#define __FILE_DIR_FLAG '/'
#define MAX_DIR_DEPTH 99
// 1 未包含中文， 0 中文替换为_, -1 错误
int replace_zh_char(char *replaced_str, const char *zh_str, const char repace_char) {
    regex_t reg;
    regmatch_t match; // 细究的话可以 - MAX_DIR_DEPTH
    // unicode编码: \u4e00-\u9fa5 // 一个汉字编码方式是1110xxxx 10xxxxxx 10xxxxxx
    char pattern[] = {'[', 0xe4, 0xb8, 0x80, 0x2d, 0xe9, 0xbe, 0xa5, ']', '+', '\0', };
    char error_buf[1024];
    int ret = 0;
    memset((void*)&match, 0x0, sizeof(regmatch_t));
    ret = regcomp(&reg, pattern, REG_EXTENDED);
    if(ret != 0 ) {
        regerror(ret, &reg, error_buf, sizeof(error_buf));
    }
    // 一次只能匹配一个
    do {
        ret = regexec(&reg, zh_str, 1, &match, 0);
        if(ret != 0 ){
            if (ret == REG_NOMATCH ) {
               regerror(ret, &reg, error_buf, sizeof(error_buf));
               break;
           } else {
               regerror(ret, &reg, error_buf, sizeof(error_buf));
               regfree(&reg);
               return -1;
           }
        } else {
           printf("regex  begin=%d end=%d\n", match.rm_so, match.rm_eo);
           int i=0;
           for(i = 0; i <match.rm_so; ++i) {
               replaced_str[i] = zh_str[i];
           }
           for(i=match.rm_so; i< match.rm_eo; ++i) {
               replaced_str[i] = repace_char;
           }
           replaced_str += match.rm_eo;
           zh_str += match.rm_eo;
        }
    } while(match.rm_so != -1);
   
    // 其余字节
    while(*zh_str) {
         *replaced_str++ = *zh_str++;
    }
    regfree(&reg);

    return ret;
}

int main() {
    char *str0 = "中国人 Love 人民币";
    char *str1 = "Janpanes 日元 nice";
    char buf[1024] = {0};
    replace_zh_char(buf, str0, '+');
    printf("str0 len=%d val=%s\n buf len=%d val=%s \n",strlen(str0), str0, strlen(buf),buf);
    memset(buf, 0x0, 1024);
    replace_zh_char(buf, str1, '_');
    printf("str1 len=%d val=%s\n buf len=%d val=%s \n",strlen(str1), str1, strlen(buf),buf);
    return 0;
}
