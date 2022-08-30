#include <stdio.h>

float t=0;

int main() {
    int p0[2] = {1, 5};
    int p1[2] = {5, 1}; 
    for (int i=0; i<51; i++) {
        float B_x = (1-t)*p0[0] + t*p1[0];
        float B_y = (1-t)*p0[1] + t*p1[1];
        printf("[t:%f](x:%f, y:%f)\n", t, B_x, B_y);
        t = t+0.02;
    }
    return 0;
}