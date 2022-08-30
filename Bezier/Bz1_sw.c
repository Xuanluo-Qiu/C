#include <ncurses.h>
#include <unistd.h>
#include <math.h>

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);

    float t = 0;
    int p0[2] = {10, 15};
    int p1[2] = {15, 10}; 
    for (int i=0; i<51; i++) {
        float B_x = (1-t)*p0[0] + t*p1[0];
        float B_y = (1-t)*p0[1] + t*p1[1];
        mvprintw(B_x+10, B_y+10, "*");
        t = t+0.02;
    }


    mvprintw(p0[1]+10, p0[0]+10, "@");
    mvprintw(p1[1]+10, p1[0]+10, "@");
    
    refresh();

    sleep(5);

    endwin();
    return 0;
}