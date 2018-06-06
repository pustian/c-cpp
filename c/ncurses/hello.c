#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main() {
    initscr();

    int i=0;
    for(i = 0; i< 20; ++i) {
        move(2*i, 4*i);
        printw("%s\n", "hello world.");
        sleep(1);
        // clearok(stdscr, 1);
        refresh();
        clear();
    }

    endwin();
    return 0;
}
