#include <ncurses.h>
#include <unistd.h>
#include <math.h>

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);

    int P0[2] = {1, 2};
    int P1[2] = {6, 2};
    int P2[2] = {2, 1};
    float t = 0;
    for (int i = 0; i < 50; i++) {
        t = t + 0.02;
        float P_x = pow((1 - t), 2) * P0[0] + 2 * t * (1 - t) * P1[0] + pow(t, 2) * P2[0];
        float P_y = pow((1 - t), 2) * P0[1] + 2 * t * (1 - t) * P1[1] + pow(t, 2) * P2[1];
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