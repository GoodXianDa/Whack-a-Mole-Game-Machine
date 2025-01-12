#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_

#include "Arduino.h"
#include "equipment_def.h"

class MotorManager 
{
private:
    TaskHandle_t _motor_control_task_handler = NULL;
public:
    bool motor_enable;
    MotorManager();
    void init();
    void deinit();
    void reset();
    void update();
};

void motor_control_task(void *pt);

#endif