#include <stdio.h>
#include <math.h>

int main() {
    int P0[2] = {1, 2};
    int P1[2] = {6, 2};
    int P2[2] = {2, 1};
    int P3[2] = {3, 1};
    float t = 0;
    for (int i=0; i<50; i++) {
        t = t+0.02;
        float P_x = P0[0] * pow((1-t), 3) + P1[0] * 3*pow((1-t), 3) + P2[0] * 3*pow(t, 2)*(1-t) * P3[0] * pow(t, 3);
        float P_y = P0[1] * pow((1-t), 3) + P1[1] * 3*pow((1-t), 3) + P2[1] * 3*pow(t, 2)*(1-t) * P3[1] * pow(t, 3);

        int x = P_x;
        int y = P_y;
        printf("[t:%f x:%d y:%d]\n", t, x, y);
    }
    return 0;
}