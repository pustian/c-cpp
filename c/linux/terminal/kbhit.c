#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>

static struct termios initial_settings;
static struct termios new_settings;
static int peek_character = -1;
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

int main() {
    int ch = 0;

    // 配置终端
    init_keyboard();
    // 每隔一秒调用kbhit， 如果按键为q则退出循环
    while(ch != 'q') {
        // printf("looping\n");
        // sleep(1);
        if(kbhit() ) {
            ch = readch();
            printf("You hit %c\n", ch);
        }
    }
    // 恢复终端为标准模式
    close_keyboard();
    return 0;
}
// 开始配置终端
void init_keyboard() {
    tcgetattr(0, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}
// 
void close_keyboard() {
    tcsetattr(0, TCSANOW, &initial_settings);
}
// 检测是否有击键动作
int kbhit() {
    char ch;
    int nread;

    if(peek_character != -1 ) {
        return 1;
    }
    new_settings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0, &ch, 1);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);

    if(nread == 1) {
        peek_character = ch;
        return 1;
    }

    return 0;
}
// 按键对应字符串给下一个readch，将变量peek_character重置为 -1，以方便下一个循环使用
int readch() {
    char ch;

    if(peek_character != -1) {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0, &ch, 1);
    return ch;
}
