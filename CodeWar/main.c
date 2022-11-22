#include <stdio.h>
#include <unistd.h>

int map_data[12][12];
int p1_data = 1;
int p2_data = 2;

int p1_now[] = {0,0};
int p2_now[] = {11,11};

/* Load the map */
void base() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            map_data[j][i] = 0;
        }
    }
}

/* Mobile control */
void move(int direction, int player) {
    if (player==1) {
        switch (direction) {
            /* down */
            case 1:
                p1_now[0] = p1_now[0]+1;
                break;
            /* up */
            case 2:
                p1_now[0] = p1_now[0]-1;
                break;
            /* left */
            case 3:
                p1_now[0] = p1_now[1]-1;
                break;
            /* right */
            case 4:
                p1_now[0] = p1_now[1]+1;
                break;
            default:
                break;
        }
    } else {
        switch (direction) {
            /* down */
            case 1:
                p2_now[0] = p2_now[0]+1;
                break;
            /* up */
            case 2:
                p2_now[0] = p2_now[0]-1;
                break;
            /* left */
            case 3:
                p2_now[0] = p2_now[1]-1;
                break;
            /* right */
            case 4:
                p2_now[0] = p2_now[1]+1;
                break;
            default:
                break;
        }
    }
}

/* Control the player */
void player_1() {
    move(1, 1);
    move(1, 1);
}

void player_2() {
    move(2, 2);
}

/* Read the player data */
void lod_player() {
    player_1();
    player_2();
}

/* Apply colours to a drawing map */
void lod_map() {
    map_data[p1_now[0]][p1_now[1]] = p1_data;
    map_data[p2_now[0]][p2_now[1]] = p2_data;

    printf("\n");
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            printf("[%d]", map_data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Statistical game data */
void lod_end() {
    int p1_num;
    int p2_num;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (map_data[i][j] == 1) {
                p1_num++;
            } else if (map_data[i][j] == 2) {
                p2_num++;
            }
        }
    }
    /* printf("[INFO]Game data: P1:%d, P2:%d\n", p1_num-12, p2_num-12); */
    if (p1_num<p2_num) {
        printf("[WIN]P2 win!\n");
    } else if (p1_num>p2_num) {
        printf("[WIN]P1 win!\n");
    } else {
        printf("[WIN]No Winner.");
    }
    
}

/* Game Logic */
int main() {
    printf("\n[INFO] Start Game\n\n");
    base();
    for (int i=0; i<12; i++) {
        printf("[INFO] Round %d", i);
        lod_player();
        lod_map();
        sleep(1);
        
        /* Some mod(?) */
        //printf("\33[2J \033[0m");
        //printf("\007 \033[0m\n");
    }

    lod_end();

    return 0;
}