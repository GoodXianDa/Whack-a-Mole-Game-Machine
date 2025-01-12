
#include "mode_manager.h"
#include "common.h"

void ModeManager::handleShortPress() {
    // 处理短按的逻辑，如果当前是 listen_music_mode，则切换到 hamster_mode_mute，否则递增到下一个模式
    this->mode = (this->mode == listen_music_mode) ? hamster_mode_mute : (Equipment_mode)(this->mode + 1);  //listen_music_mode为累举最后一个数
    switch (this->mode)
    {
    case stop_mode:
        this->music_enable = false;
        break;
    case hamster_mode_mute:
        this->music_enable = false;
        this->music_mode_init_flag = false;  
        break;
    case hamster_mode_voice:
        this->music_enable = true;
        break;
    case play_music_mode:
        buzzer_manager.mute();
        button_manager.reset();
        this->music_enable = true;
        this->hamster_mode_init_flag = false;
        break;
    case listen_music_mode:
        buzzer_manager.mute();
        button_manager.reset();
        this->music_enable = true;
        break;
    default:
        break;
    }
    Serial.println(this->mode);
}

void ModeManager::handleLongPress() {
    // 长按处理，如果当前是 stop_mode，切换到 hamster_mode_mute，否则切换到 stop_mode
    if (this->mode == stop_mode) {
        this->mode = hamster_mode_mute;  // 开机进入 hamster_mode_mute
        Serial.println("Mode changed to: hamster_mode_mute");
    } else {
        this->mode = stop_mode;  // 长按关机进入 stop_mode
        Serial.println("Mode changed to: stop_mode");
    }
}

ModeManager::ModeManager() {
}

void ModeManager::init() {
    Serial.println("ModeManager::init");

    if (xTaskCreate(               // pdPASS表示创建成功
        mode_control_task,          // 函数名
        "mode_control_task",        // 任务名
        1024,              // 分配内存
        NULL,                  // 传参
        1,                     // 优先级
        &_mode_control_task_handler // 操作指针
        ) == pdPASS)
    Serial.println("mode_control_task Created.");

    this->reset();
}

void ModeManager::deinit() {
    Serial.println("ModeManager::deinit");
    if (NULL != _mode_control_task_handler)
    {
        vTaskDelete(_mode_control_task_handler);
        _mode_control_task_handler = NULL;
    }
}

void ModeManager::reset() {
    this->mode = stop_mode;
    this->music_enable = false;
    this->button_press_start_time = 0; 
    this->is_button_pressed = 0;
    this->hamster_mode_init_flag = false;
    this->music_mode_init_flag = false;
}

void ModeManager::update_all_mode() {
    unsigned long time_now = millis();
    static unsigned long time_cnt = 0;
    static bool reset_time_cnt = true; // 用于重置计时器
    switch (this->mode)
    {
    case stop_mode:
        this->music_enable = false;
        break;
    case hamster_mode_mute:
        this->music_enable = false;  
        break;
    case hamster_mode_voice:
        this->music_enable = true;
        break;
    case play_music_mode:
        this->music_enable = true;
        break;      
    case listen_music_mode:
        this->music_enable = true;
        break;
    default:
        break;
    }
}

void ModeManager::handleButtonPress() {
    bool button_state = digitalRead(MODE_PIN);  // 读取按键状态
    if(button_state == LOW){   //按下
        if(!this->is_button_pressed){  //如果之前没被按下
            this->is_button_pressed = true;
            button_press_start_time = millis();  //开始计时
        }
    }else{  //按键释放
        if(this->is_button_pressed){
            this->is_button_pressed = false;  //更新按键状态(已松开)
            unsigned long press_duration = millis() - button_press_start_time;
            // 先判断长按，再判断短按
            if (press_duration > longPressDuration) {  // 长按超过0.8s
                handleLongPress();
            } else if(press_duration > shortPressDuration && this->mode != stop_mode){  // 短按(60ms)
                handleShortPress();
            }
        }
    }
    //Serial.println(button_state);   //调试用
}

void mode_control_task(void* pt) {
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(30));
        mode_manager.handleButtonPress();
        mode_manager.update_all_mode();
        //Serial.println(mode_manager.mode);  //调试用
    }
}
