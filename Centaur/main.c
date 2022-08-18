#include <stdio.h>
#include <math.h>

// 引力常数
double G = 1;
// 刷新率
double dt = 0;
// 步长
double t = 0.5;

// 恒星距离
double r(double r_a_x, double r_a_y, double r_b_x, double r_b_y) {
    return pow((fabs(r_a_x - r_b_x)), 2) + pow((fabs(r_a_y - r_b_y)), 2);
}

// 引力加速度
double newton_F(double m, double r) {
    return G * m / pow(r, 2);
}

// 垂直，水平加速度
double axis_F(double newton, double axis, double _axis, double r, double _newton, double __axis, double _r) {
    return newton * (axis - _axis) / r + _newton * (__axis - _axis) / _r;
}

// 计算速度
double v(double axis) {
    return axis + axis * t;
}

// 计算位置
double axis_xy(double axis, double v) {
    return axis + v * t;
}

int main() {
    // 恒星质量
    int fs_a_m = 15;
    int fs_b_m = 12;
    int fs_c_m = 8;
    // 恒星位置
    double fs_a_pos[] = {30, 50};
    double fs_b_pos[] = {-10, -20};
    double fs_c_pos[] = {-10, -15};
    // 恒星初速度
    double fs_a_v_x = 0;
    double fs_b_v_x = 0;
    double fs_c_v_x = 0;
    double fs_a_v_y = 0;
    double fs_b_v_y = 0;
    double fs_c_v_y = 0;

    while (1) {
        // 计算距离
        double r_ab = r(fs_a_pos[0], fs_b_pos[0], fs_a_pos[1], fs_b_pos[1]);
        double r_ac = r(fs_a_pos[0], fs_c_pos[0], fs_a_pos[1], fs_c_pos[1]);
        double r_bc = r(fs_b_pos[0], fs_c_pos[0], fs_b_pos[1], fs_c_pos[1]);

        // A
        // b对a的加速度
        double F_ab = newton_F(fs_a_m, r_ab);
        // c对a的加速度
        double F_ac = newton_F(fs_c_m, r_ac);
        // a受到的水平加速度
        double a_x = axis_F(F_ab, fs_b_pos[0], fs_a_pos[0], r_ab, F_ac, fs_c_pos[0], F_ac);
        // a受到的垂直加速度
        double a_y = axis_F(F_ab, fs_b_pos[1], fs_a_pos[1], r_ab, F_ac, fs_c_pos[1], F_ac);
        // a的速度
        fs_a_v_x = v(fs_a_v_x);
        fs_a_v_y = v(fs_a_v_y);
        // a的位置
        fs_a_pos[0] = axis_xy(a_x, fs_a_v_x);
        fs_a_pos[1] = axis_xy(a_y, fs_a_v_y);

        // B
        double F_ba = newton_F(fs_a_m, r_ab);
        double F_bc = newton_F(fs_c_m, r_bc);
        double b_x = axis_F( F_ba, fs_a_pos[0], fs_b_pos[0], r_ab, F_ac, fs_c_pos[0], F_bc);
        double b_y = axis_F(F_bc, fs_b_pos[1], fs_b_pos[1], r_ab, F_ac, fs_c_pos[1], F_bc);
        fs_b_v_x = v(fs_b_v_x);
        fs_b_v_y = v(fs_b_v_y);
        fs_b_pos[0] = axis_xy(b_x, fs_b_v_x);
        fs_b_pos[1] = axis_xy(b_y, fs_b_v_y);

        // C
        double F_ca = newton_F(fs_a_m, r_ac);
        double F_cb = newton_F(fs_b_m, r_bc);
        double c_x = axis_F(F_ca, fs_a_pos[0], fs_c_pos[0], r_ac, F_cb, fs_c_pos[0], F_cb);
        double c_y = axis_F(F_ca, fs_a_pos[1], fs_c_pos[1], r_ac, F_cb, fs_c_pos[1], F_cb);
        fs_a_v_x = v(fs_c_v_x);
        fs_a_v_y = v(fs_c_v_y);
        fs_c_pos[0] = axis_xy(c_x, fs_c_v_x);
        fs_c_pos[1] = axis_xy(c_y, fs_c_v_y);
        
        dt++;
        if (dt == 1000) {
            printf("(a)[X: %e||Y: %e]\n", fs_a_pos[0], fs_a_pos[1]);
            printf("(b)[X: %e||Y: %e]\n", fs_b_pos[0], fs_b_pos[1]);
            printf("(c)[X: %e||Y: %e]\n", fs_c_pos[0], fs_c_pos[1]);
            dt = 0;
        }

    }
    
    return 0;
}