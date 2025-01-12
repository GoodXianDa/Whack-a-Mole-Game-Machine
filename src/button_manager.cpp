#include "button_manager.h"
#include "common.h"

const int ButtonManager::button_index[NUM_BUTTONS] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN, BUTTON_5_PIN, BUTTON_6_PIN, BUTTON_7_PIN};

// 每个等级下不同档次地鼠的生成概率（一级、二级、三级）
const uint8_t ButtonManager::level_probabilities[7][3] = {
    {100, 0, 0},    // level_1: 100% 一级地鼠, 0% 二级, 0% 三级
    {90, 10, 0},    // level_2: 90% 一级, 10% 二级, 0% 三级
    {80, 15, 5},   // level_3: 80% 一级, 15% 二级, 5% 三级
    {75, 20, 5},   // level_4: 75% 一级, 20% 二级, 5% 三级
    {75, 20, 5},   // level_5: 75% 一级, 20% 二级, 5% 三级
    {70, 20, 10},   // level_6: 70% 一级, 20% 二级, 10% 三级
    {60, 35, 15}    // level_7: 60% 一级, 35% 二级, 15% 三级
};
void ButtonManager::handleShortPress(int i) {
    switch (mode_manager.mode)
    {
    case stop_mode:  // 停止模式，重置所有地鼠状态
        for(int i = 0;i < NUM_BUTTONS;i++){
            this->hamsterStates[i] = 0;
        }
        this->hamster_cnt = 0;
        break;
    case hamster_mode_mute:
    case hamster_mode_voice:  // 地鼠游戏模式
        if(!this->is_level_raising && mode_manager.hamster_mode_init_flag && !this->is_deading){  //提示时按键无效
            if(this->hamsterStates[i] >= 1){  //如果按的地方有地鼠
                this->hamsterStates[i]--;  //地鼠被打击一次
                if(this->hamsterStates[i] == 0){
                    this->hamster_cnt--;
                    this->beat_hamster_cnt++;
                }
                this->is_right_beat = 1;
            }else{
                this->hamster_life--;
                this->is_right_beat = 2;
            }
            //Serial.println("dadadada"); //测试用
        }
        break;
    case play_music_mode:  // 电子琴模式，无操作
        break;
    case listen_music_mode:  // 听音乐模式，切换歌曲
        buzzer_manager.song_list = (i+1);
        if(this->is_music_on){
            this->is_music_on = false;
        }else{
            this->is_music_on = true;
        }
        break;
    default:
        break;
    }
}

void ButtonManager::handleLongPress() {
}

ButtonManager::ButtonManager() {
}

void ButtonManager::init() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(this->button_index[i], INPUT_PULLUP);  // 配置按钮为上拉输入模式
    }
    Serial.println("ButtonManager::init");

    if (xTaskCreate(               // pdPASS表示创建成功
        button_task,          // 函数名
        "button_task",        // 任务名
        1024,              // 分配内存
        NULL,                  // 传参
        1,                     // 优先级
        &_button_task_handler // 操作指针
        ) == pdPASS)
    Serial.println("button_task Created.");

    this->reset();   // 初始化重置状态
}

void ButtonManager::deinit() {
    Serial.println("ButtonManager::deinit");
    if (NULL != _button_task_handler)
    {
        vTaskDelete(_button_task_handler);
        _button_task_handler = NULL;
    }
}

void ButtonManager::reset() {
    this->hamster_cnt = 0;
    this->hamster_life = GAME_LIFE;  // 初始生命值
    this->beat_hamster_cnt = 0;
    this->is_music_on = false;
    this->is_level_raising = false;
    this->is_right_beat = 0;
    this->is_deading = false;
    this->level_now = level_1;  // 初始等级
    for(int i = 0;i < NUM_BUTTONS;i++){  // 清空所有地鼠状态
        this->hamsterStates[i] = 0;
    } 
}

void ButtonManager::update() {
    if(mode_manager.mode == hamster_mode_mute|| mode_manager.mode == hamster_mode_voice){
        if(mode_manager.hamster_mode_init_flag && this->is_level_raising == false){
            this->Hamstermode_generate_hamster();
        }
        this->Hamstermode_check_gameover();
    }else{

    }
}

void ButtonManager::Hamstermode_generate_hamster() {
    this->Hamstermode_decide_level(beat_hamster_cnt);  //先判断当前的level
    static bool is_generating = false;
    static unsigned long startTime = 0;
    static unsigned long interval = 0; // 初始随机时间间隔
    if(!is_generating){
        interval = this->Hamstermode_generate_interval();
        is_generating = true;
        startTime = millis();
    }
    if((millis() - startTime) > interval){
        int index = 0;
        do
        {
            index = random(0,7);
        } while (this->hamsterStates[index] >= 1 && this->hamster_cnt < 7);
        this->hamsterStates[index] = this->Hamstermode_generate_each_level();
        this->hamster_cnt++;
        is_generating = false;  // 重置生成状态

        // for(int i=0;i<7;i++){  //debug用
        //     Serial.print("i: ");
        //     int num = i;
        //     num+=1;
        //     Serial.print(num);
        //     Serial.print(" | state: ");
        //     Serial.println(this->hamsterStates[i]);
        // }
    }

}

long ButtonManager::Hamstermode_generate_interval() {
    unsigned long interval = 0;
    switch (this->level_now)
    {
    case level_1:
        interval = random(400,751);
        break;
    case level_2:
        interval = random(350,651);
        break;
    case level_3:
        interval = random(300,501);
        break;
    case level_4:
        interval = random(300,401);
        break;
    case level_5:
        interval = random(250,401);
        break;
    case level_6:
        interval = random(250,351);
        break;
    case level_7:
        interval = random(200,301);
        break;;
    default:
        break;
    }
    return interval;
}

uint8_t ButtonManager::Hamstermode_generate_each_level() {
    int randNum = random(100);  // 生成 0-99 的随机数
    uint8_t level_index = static_cast<uint8_t>(this->level_now);  // 当前等级索引

    // 获取当前等级的概率分布
    const uint8_t* probabilities = &level_probabilities[level_index][0];  // 正确获取行指针

    if (randNum < probabilities[0]) {  // 一级地鼠
        return 1;
    } else if (randNum < (probabilities[0] + probabilities[1])) {  // 二级地鼠
        return 2;
    } else {  // 三级地鼠
        return 3;
    }
}

void ButtonManager::Hamstermode_decide_level(uint16_t cnt) {
    hamster_level new_level;
    // 根据 cnt 决定新的等级
    if (cnt < LEVEL_1_CNT_MAX) new_level = level_1;
    else if (cnt < LEVEL_2_CNT_MAX) new_level = level_2;
    else if (cnt < LEVEL_3_CNT_MAX) new_level = level_3;
    else if (cnt < LEVEL_4_CNT_MAX) new_level = level_4;
    else if (cnt < LEVEL_5_CNT_MAX) new_level = level_5;
    else if (cnt < LEVEL_6_CNT_MAX) new_level = level_6;
    else if (cnt < LEVEL_7_CNT_MAX) new_level = level_7;
    else new_level = level_7;

    // 检测等级是否发生变化
    if (new_level != this->level_now) {
        this->is_level_raising = true;  // 等级发生变化
        this->level_now = new_level;  // 更新当前等级
    } else {
        this->is_level_raising = false;  // 等级未发生变化
    }
}

void ButtonManager::Hamstermode_check_gameover() {
    if(this->hamster_cnt >=7 || this->hamster_life <=0){
        this->is_deading = true;
        if(mode_manager.music_enable){
            motor_manager.motor_enable = true;
        }
        vTaskDelay(pdMS_TO_TICKS(250));  // 短暂延时提示玩家游戏结束
        motor_manager.motor_enable = false;
        vTaskDelay(pdMS_TO_TICKS(1250));
        button_manager.reset();
        mode_manager.reset();
        motor_manager.reset();
    }
}

void ButtonManager::handleButtonPress() {
    for(int i = 0;i < NUM_BUTTONS;i++){
        int button_state = digitalRead(this->button_index[i]);
        if(button_state == LOW){   //按下
            if(!this->is_button_pressed[i]){  //如果之前没被按下
                this->is_button_pressed[i] = true;
                button_press_start_time[i] = millis();  //开始计时
            }
        }else{  //按键释放
            if(this->is_button_pressed[i]){
                this->is_button_pressed[i] = false;  //更新按键状态(已松开)
                unsigned long press_duration = millis() - button_press_start_time[i];
                // // 先判断长按，再判断短按
                // if (press_duration > longPressDuration) {  // 长按超过1s
                //     handleLongPress();
                // } else if(press_duration > shortPressDuration){  // 短按(100ms)
                //     handleShortPress();
                // }
                if(press_duration > shortPressDuration){
                    handleShortPress(i);
                }
            }
        }
    }

}


void button_task(void* pt) {
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(75));
        if(mode_manager.mode != stop_mode){
            button_manager.handleButtonPress();
            button_manager.update();
        }
    }
}



