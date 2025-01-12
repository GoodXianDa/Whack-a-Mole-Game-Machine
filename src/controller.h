#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <stdlib.h>
#include <string.h>

class PIDController {
private:
    double kp;  // 比例系数
    double ki;  // 积分系数
    double kd;  // 微分系数

    double prev_error;  // 上一次误差
    double integral;    // 积分累计值

public:
    double output_max;
    double output;
      // 默认构造函数
    PIDController() : kp(0), ki(0), kd(0), prev_error(0), integral(0),output_max(0),output(0) {}

    // 带参数的构造函数
    PIDController(double p, double i, double d, double outputmax) : kp(p), ki(i), kd(d), prev_error(0), integral(0),output_max(outputmax), output(0) {}
    void reset();
    void compute(double ref, double fdb);
    // 调整 PID 参数
    void setParameters(double p, double i, double d);
};

#endif 
