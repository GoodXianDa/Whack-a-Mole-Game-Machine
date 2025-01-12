#include "controller.h"
#include "common.h"

void PIDController::reset() {
    this->prev_error = 0;
    this->integral = 0;
}

void PIDController::compute(double ref, double fdb) {
    // 计算误差
    double error = ref - fdb;
    // 积分项
    this->integral += error;
    // 微分项
    double derivative = error - prev_error;
    // PID 输出
    this->output = this->kp * error + this->ki * this->integral + this->kd * derivative;
    this->output = Mid(this->output,-this->output_max,this->output_max);
    // 更新上一次误差
    this->prev_error = error;
}

void PIDController::setParameters(double p, double i, double d) {
    this->kp = p;
    this->ki = i;
    this->kd = d;
}
