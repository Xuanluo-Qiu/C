#include <stdio.h>


int num_data[5] = {1, 4, 2, 3, 5};
int num_now;

int main() {
    /*
    for (int d = 0; d < 5; d++) {
        printf(">>> ");
        scanf("%d", &num_data[d]);
        printf(">>> num[%d]:%d\n", d, num_data[d]);
    }
    printf("\n");
    */
    for (int i=1; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (num_data[i] < num_data[j]) {
                num_now = num_data[i];
                num_data[i] = num_data[j];
                num_data[j] = num_now;
             }
        }
        printf("[OUT](%d, %d, %d, %d, %d)\n", num_data[0], num_data[1], num_data[2], num_data[3], num_data[4]);
    }

    return 0;
}