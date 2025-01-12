#include "common.h"

ModeManager mode_manager;
ButtonManager button_manager;
LightManager light_manager;
BuzzerManager buzzer_manager;
MotorManager motor_manager;

// 牛顿迭代法求解1/sqrt(x)
float invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *)&y; // 将float型数据转为long型，注意，通过指针转换只是将内存中的数据换了一种解读方式，与强制类型转换不同
    i = 0x5f3759df - (i >> 1); // 0x5f3759df是一个精度比较高的经验值
    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

// 传入参数为整型数的符号函数
int sgn(int x){
    return x == 0 ? 0 : x > 0 ? 1 : -1;
}

// 传入参数为浮点数的符号函数
int fsgn(float x) {
    return (x != 0.0f ? (x < 0.0f ? -1 : 1) : 0);
}

// fabs(x)≥d时，返回x的符号函数，否则返回x/d
float sgn_like(float x, float d) {
    if (fabs(x) >= d)
        return fsgn(x);
    else
        return x / d;
}