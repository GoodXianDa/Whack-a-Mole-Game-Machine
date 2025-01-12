#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_

#include "Arduino.h"
#include "equipment_def.h"

typedef enum hamster_level_e{
    level_1,
    level_2,
    level_3,
    level_4,
    level_5,
    level_6,
    level_7
}hamster_level;
class ButtonManager
{
private:
    unsigned long button_press_start_time[NUM_BUTTONS];  // 记录每个按钮的按下时间
    static const int button_index[];  // 按钮对应的引脚索引数组
    static const uint8_t level_probabilities[7][3];  // 各等级下不同地鼠生命值的概率分布
    TaskHandle_t _button_task_handler = NULL;

    void handleShortPress(int i);
    void handleLongPress();
public:
    bool is_button_pressed[NUM_BUTTONS];  // 按键状态标志
    uint8_t hamsterStates[NUM_BUTTONS];   // 地鼠状态数组（0-3，表示地鼠生命值）
    bool is_music_on;  // 是否开启音乐模式标志
    bool is_level_raising;  // 等级是否正在提升
    bool is_deading;  // 游戏是否结束标志
    uint8_t is_right_beat;  // 击打状态：1表示正确击打，2表示错误击打，0表示未击打
    uint8_t hamster_cnt;  // 当前地鼠数量
    uint8_t hamster_life;   // 玩家剩余生命值
    uint16_t beat_hamster_cnt;  // 已击打地鼠总数
    hamster_level level_now;  // 当前游戏等级
    ButtonManager();
    void init();
    void deinit();
    void reset();
    void update();
    void Hamstermode_generate_hamster();  // 随机生成地鼠
    long Hamstermode_generate_interval();  // 计算生成地鼠的时间间隔
    uint8_t Hamstermode_generate_each_level();  // 根据当前等级生成对应生命值的地鼠
    void Hamstermode_decide_level(uint16_t cnt);  // 根据击打数量决定当前游戏等级
    void Hamstermode_check_gameover();   // 检查游戏是否结束
    void handleButtonPress();  // 按键处理逻辑
};

void button_task(void *pt);


#endif