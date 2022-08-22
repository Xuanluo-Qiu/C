#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

int end = 0;
int coiled = 0;
int goout = 0;

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(FALSE);

    while (!goout) {
        mvprintw(2, 33, "Coiled: %d", coiled);
        mvprintw(4, 33, "End: %d", end);
        refresh();

        mvprintw(30, 0, "[----][----][----][----]");

        int x_d = rand() % 4;
        int x, y = 0;
        switch (x_d) {
        case 0:
            x = 0;
            break;
        case 1:
            x = 6;
            break;
        case 2:
            x = 12;
            break;
        case 3:
            x = 18;
            break;
        default:
            break;
        }

        char block[] = "[(--)]";
        for (int i = 0; i < 30; i++) {
            mvprintw(y, x, block);
            mvprintw(y - 1, x, "      ");
            refresh();
            usleep(30000);
            y++;
        }

        timeout(0);
        int ch = getch();
        switch (ch) {
            case 'a':
                if (x_d == 0) {
                    coiled++;
                } else {
                    end++;
                }
                break;
            case 's':
                if (x_d == 1) {
                    coiled++;
                } else {
                    end++;
                }
                break;
            case 'd':
                if (x_d == 2) {
                    coiled++;
                } else {
                    end++;
                }
                break;
            case 'f':
                if (x_d == 3) {
                    coiled++;
                } else {
                    end++;
                }
                break;
            case 'q':
                goout = 1;
                break;
            default:
                end++;
                break;
        }

        if (end>10) {
            clear();
            mvprintw(15, 8, "[Bad End(10)]");
            refresh();
            sleep(1);
            goout = 1;
        }
        usleep(30000);
        clear();
    }

    endwin();
    return 0;
}