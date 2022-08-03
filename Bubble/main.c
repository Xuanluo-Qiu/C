/*
 Run: make && ./main
*/

#include <ncurses.h>
#include <unistd.h>

#define CENTER_Y 20
#define CENTER_X 30

int num_data[5] = {1, 3, 2, 5, 4};
int length = 0;

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

void display() {
    for (int f=0; f<5; f++) {
        x = x+10;
        histogram(num_data[f]);
    }
}


int main() {
    length = sizeof(num_data) / sizeof(int); 
    printf("[NUM_LEN](%d)\n", length);
    printf("[OUT_NOW](%d, %d, %d, %d, %d)\n", num_data[0], num_data[1], num_data[2], num_data[3], num_data[4]);
    sleep(1);

    initscr();
    noecho();
    curs_set(FALSE);

    display();
    x = CENTER_X;
    sleep(1);
    clear();

    for (int i=1; i<length; i++) {
        for (int j=0; j<length; j++) {
            if (num_data[i] < num_data[j]) {
                int temp;
                temp = num_data[i];
                num_data[i] = num_data[j];
                num_data[j] = temp;
            }
        }
        display();
        x = CENTER_X;
        sleep(1);
        clear();
    }

    mvprintw(y, x + 30, "[END]");
    refresh();
    sleep(1);

    endwin();
    
    printf("[OUT_NEW](%d, %d, %d, %d, %d)\n", num_data[0], num_data[1], num_data[2], num_data[3], num_data[4]);

    return 0;
}