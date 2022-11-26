#include <stdio.h>

// 地图数据
int map_data[12][12];

// 初始化游戏数据
void lod_data() {
    // 初始化地图
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            map_data[i][j] = 0;
        }
    }
    // 初始化生命数据
    map_data[0][1] = 1;
    map_data[1][2] = 1;
    map_data[2][0] = 1;
    map_data[2][1] = 1;
    map_data[2][2] = 1;
}

void control() {
    int _map[12][12];
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            _map[i][j] = map_data[i][j];
        }
    }
    // 遍历地图
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            // 设定变量储存周边生命
            int state = 0;
            // 探测生命
            if (!(i==0 || j==0)) {
                state = state + map_data[i - 1][j - 1];
            }
            if (!(i==0)) {
                state = state + map_data[i - 1][j];
            }
            if (!(i==0 || j==11)) {
                state = state + map_data[i - 1][j + 1];
            }
            if (!(j==0)) {
                state = state + map_data[i][j - 1];
            }
            if (!(j==11)) {
                state = state + map_data[i][j + 1];
            }
            if (!(i==11 || j==0)) {
                state = state + map_data[i + 1][j - 1];
            }
            if (!(i==11)) {
                state = state + map_data[i + 1][j];
            }
            if (!(i==11 || j==11)) {
                state = state + map_data[i + 1][j + 1];
            }

            if (state > 3 || state < 2) {
                _map[i][j] = 0;
            } else if (state == 3) {
                _map[i][j] = 1;
            }

            if (_map[i][j] == 1) {
                printf("\033[47m  \033[0m");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            map_data[i][j] = _map[i][j];
        }
    }
}

int main() {
    lod_data();
    printf("Control+C == Exit\n\n");
    while(1) {
        control();
        getchar();
        printf("\33[2J \033[0m");
    }
    return 0;
}