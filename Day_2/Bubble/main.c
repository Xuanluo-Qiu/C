// #include <stdio.h>
#include <ncurses.h>

int main() {
    initscr();
    printw("123");
    refresh();
    getchar();
    endwin();
    return 0;
}

