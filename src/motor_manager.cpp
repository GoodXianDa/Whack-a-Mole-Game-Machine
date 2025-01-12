#include "motor_manager.h"
#include "common.h"

MotorManager::MotorManager() {
}

void MotorManager::init() {
    pinMode(MOTOR_PIN,OUTPUT);
    digitalWrite(MOTOR_PIN,LOW);
    Serial.println("MotorManager::init");

    if (xTaskCreate(               // pdPASS表示创建成功
        motor_control_task,          // 函数名
        "motor_control_task",        // 任务名
        256,              // 分配内存
        NULL,                  // 传参
        1,                     // 优先级
        &_motor_control_task_handler // 操作指针
        ) == pdPASS)
    Serial.println("motor_control_task Created.");

    this->reset();
}

void MotorManager::deinit() {
    Serial.println("ModeManager::deinit");
    if (NULL != _motor_control_task_handler)
    {
        vTaskDelete(_motor_control_task_handler);
        _motor_control_task_handler = NULL;
    }
}

void MotorManager::reset() {
    this->motor_enable = false;
}

void MotorManager::update() {
    if(this->motor_enable){
        digitalWrite(MOTOR_PIN,HIGH);
    }else{
        digitalWrite(MOTOR_PIN,LOW);
    }
}

void motor_control_task(void* pt) {
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(25));
        motor_manager.update();
        //Serial.println(motor_manager.motor_enable);  //debug用
    }
}
