#include <ncurses.h>
#include <unistd.h>


void playMusic() {
    
}

void display() {
    initscr();
    
    int row,col;
    getmaxyx(stdscr,row,col);
    
    noecho();
    curs_set(FALSE);

    // col:x
    // row:y
    int bezel_a_col = col-82;
    int bezel_a_row = row-1;

    int bezel_b_col = col-79;
    int bezel_b_row = row-20;

    // Draw Bezel A
    for (int i=0; i<row; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, bezel_a_col, "|");
    }

    for (int i=0; i<bezel_a_col; i++) {
        mvprintw(0, i, "-");
        mvprintw(bezel_a_row, i, "-");
    }

    mvprintw(0, 0, " ");
    mvprintw(0, bezel_a_col, " ");
    mvprintw(bezel_a_row, 0, " ");
    mvprintw(bezel_a_row, bezel_a_col, " ");

    // Draw Bezel B
    for (int i=0; i<row-bezel_b_row-4; i++) {
        mvprintw(i, bezel_b_col, "|");
        mvprintw(i, col-4, "|");
    }

    for (int i=0; i<col-54; i++) {
        mvprintw(0, bezel_b_col+i, "-");
        mvprintw(bezel_b_row, bezel_b_col+i, "-");
    }

    mvprintw(0, bezel_b_col, " ");
    mvprintw(bezel_b_row, bezel_b_col, " ");
    mvprintw(bezel_b_row, col-4, " ");
    mvprintw(0, col-4, " ");

    refresh();

    // usleep(30000);
    sleep(2);
    endwin();
}

int main() {
    display();
    return 0;
}