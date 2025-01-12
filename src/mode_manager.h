#ifndef _MODE_MANAGER_H_
#define _MODE_MANAGER_H_

#include "Arduino.h"
#include "equipment_def.h"

typedef enum Equipment_mode_e {
    stop_mode = 0,
    hamster_mode_mute,
    hamster_mode_voice,
    play_music_mode,
    listen_music_mode
}Equipment_mode;

class ModeManager 
{
private:
    unsigned long button_press_start_time;  // 按下时间记录
    bool is_button_pressed;                 // 按键状态标志
    TaskHandle_t _mode_control_task_handler = NULL;

    void handleShortPress();
    void handleLongPress();

public:
    Equipment_mode mode;
    bool music_enable;
    bool hamster_mode_init_flag;
    bool music_mode_init_flag;
    ModeManager();
    void init();
    void deinit();
    void reset();
    void update_all_mode();
    void handleButtonPress();  // 按键处理逻辑
};

void mode_control_task(void *pt);

#endif  // _MODE_MANAGER_H_