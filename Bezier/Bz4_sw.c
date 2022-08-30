#include <ncurses.h>
#include <unistd.h>
#include <math.h>

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);

    int P0[2] = {0, 0};
    int P1[2] = {12, 12};
    int P2[2] = {22, 32};
    int P3[2] = {32, 42};
    float t = 0;

    for (int i=0; i<50; i++) {
        t = t+0.02;
        float P_x = P0[0] * pow((1-t), 3) + P1[0] * 3*pow((1-t), 3) + P2[0] * 3*pow(t, 2)*(1-t) * P3[0] * pow(t, 3);
        float P_y = P0[1] * pow((1-t), 3) + P1[1] * 3*pow((1-t), 3) + P2[1] * 3*pow(t, 2)*(1-t) * P3[1] * pow(t, 3);

        int x = P_x;
        int y = P_y;

        mvprintw(y+10, x+10, "*");
    }

    mvprintw(P0[1]+10, P0[0]+10, "@");
    mvprintw(P1[1]+10, P1[0]+10, "@");
    mvprintw(P2[1]+10, P2[0]+10, "@");
    refresh();

    sleep(5);

    endwin();
    return 0;
}
