/*
 Run: make && ./main
*/

#include <ncurses.h>
#include <unistd.h>

#define CENTER_Y 20
#define CENTER_X 30

int num_data[5] = {2, 3, 1, 5, 4};
int num_now;

int x = CENTER_X, y = CENTER_Y;

void histogram(int num) {
    y = CENTER_Y;
    for (int c = 0; c < num; c++) {
        mvprintw(y, x, "[-]");
        refresh();
        usleep(30000);
        y--;
    }
}


int main() {
    
    initscr();
    noecho();
    curs_set(FALSE);

    for (int i=1; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (num_data[i] < num_data[j]) {
                num_now = num_data[i];
                num_data[i] = num_data[j];
                num_data[j] = num_now;
            }
            // printf("[OUT](%d, %d, %d, %d, %d)\n", num_data[0], num_data[1], num_data[2], num_data[3], num_data[4]);
        }
        for (int f=0; f<5; f++) {
            x = x+10;
            histogram(num_data[f]);
        }
        x = CENTER_X;
        sleep(1);
        clear();
    }

    mvprintw(y, x + 30, "[END]");
    refresh();
    sleep(1);

    endwin();

    return 0;
}