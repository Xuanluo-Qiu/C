#include <stdio.h>
#include <unistd.h>

// 地图数据
int map_data[12][12];

// 初始化游戏数据
void lod_data() {
    // 初始化地图
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            map_data[j][i] = 0;
        }
    }
    // 初始化生命数据
    map_data[0][1] = 1;
    map_data[1][2] = 1;
    map_data[2][0] = 1;
    map_data[2][1] = 1;
    map_data[2][2] = 1;
}

// 游戏逻辑
void control() {
    // 设定变量储存周边生命
    int state_data;
    // 遍历地图
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            // 探测生命
            if (map_data[i+1][j] == 1) {
                state_data++;
            }
            if (map_data[i-1][j] == 1) {
                state_data++;
            }
            if (map_data[i][j-1] == 1) {
                state_data++;
            }
            if (map_data[i][j+1] == 1) {
                state_data++;
            }
            if (map_data[i+1][j+1] == 1) {
                state_data++;
            }
            if (map_data[i+1][j-1] == 1) {
                state_data++;
            }
            if (map_data[i-1][j+1] == 1) {
                state_data++;
            }
            if (map_data[i-1][j-1] == 1) {
                state_data++;
            }

            // 决定生死
            if (state_data >= 3) {
                if (map_data[i][j] == 0) {
                    map_data[i][j] = 1;
                } else {
                    map_data[i][j] = 0;
                }
            } else {
                map_data[i][j] = 1;
            }
            // 重制数据
            state_data = 0;
        }
    }
}

// 渲染世界
void lod_world() {
    printf("\n");
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            printf("[%d]", map_data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // 加载世界数据
    lod_data();
    for (int i=0; i<3; i++) {
        // 进行判定
        control();
        // 渲染
        lod_world();
        sleep(1);
        // 清屏
        // printf("\33[2J \033[0m");
    }
    // 使用清屏时打开
    // lod_world();

    return 0;
}