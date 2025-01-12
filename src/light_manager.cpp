#include "light_manager.h"
#include "common.h"

const CRGB LightManager::RAINBOW_COLORS[7] = {
    CRGB(255, 0, 0),     // 红色
    CRGB(255, 165, 0),   // 橙色
    CRGB(255, 255, 0),   // 黄色
    CRGB(0, 255, 0),     // 绿色
    CRGB(0, 255, 255),   // 青色
    CRGB(0, 0, 255),     // 蓝色
    CRGB(139, 0, 255)    // 紫色
};

const CRGB LightManager::HAMASTER_COLORS[4] = {
    CRGB(0, 0, 0),     // 无地鼠
    CRGB(240, 115, 110),   // 第一形态
    CRGB(230,206,40),   // 第二形态
    CRGB(10,197,205),     // 第三形态
};

LightManager::LightManager() {
}

void LightManager::init() {
    Serial.println("LightManager::init");
    
    FastLED.addLeds<WS2812, LED_PIN, GRB>(this->leds, NUM_LEDS); // 初始化灯带
    this->max_bright = 18;
    FastLED.setBrightness(this->max_bright); // 设置亮度
    if (xTaskCreate(               // pdPASS表示创建成功
        light_task,          // 函数名
        "light_task",        // 任务名
        4096,              // 分配内存
        NULL,                  // 传参
        1,                     // 优先级
        &_light_task_handler // 操作指针
        ) == pdPASS)
    Serial.println("light_task Created.");
    
    this->reset();
}

void LightManager::deinit() {
    Serial.println("LightManager::deinit");
    if (NULL != _light_task_handler)
    {
        vTaskDelete(_light_task_handler);
        _light_task_handler = NULL;
    }
}

void LightManager::reset() {
    for(int index = 0;index < NUM_LEDS;index++){
        this->leds[index] = CRGB(0, 0, 0); // 设置颜色
    }
    FastLED.show();
}

void LightManager::update() {
    switch (mode_manager.mode)
    {
    case stop_mode:
        for (int i = 0; i < NUM_LEDS; i++) {
            if(mode_manager.mode !=stop_mode){
                return;
            }
            this->reset();  // 先熄灭所有灯
            this->leds[i] = CRGB(random(256), random(256), random(256));
            FastLED.show();
            vTaskDelay(pdMS_TO_TICKS(500));  // 每500ms切换一个灯
        }
        break;
    case hamster_mode_mute:
    case hamster_mode_voice:
        if(!mode_manager.hamster_mode_init_flag){
            this->Hamstermode_light_init();
        }
        if(button_manager.is_level_raising){
            this->Hamstermode_levelChangeNotification();
        }
        this->Hamstermode_light_update();
        break;
    case play_music_mode:
    case listen_music_mode:
            if(!mode_manager.music_mode_init_flag){
                this->Musicmode_light_init();
            }
        break;
    default:
        break;
    }
    FastLED.show();
}

void LightManager::Musicmode_light_init() {
    for (int i = 0; i < NUM_LEDS; i++) {
        this->leds[i] = RAINBOW_COLORS[i];  // 使用彩虹七色数组
    }
    mode_manager.music_mode_init_flag = true;
}

void LightManager::Hamstermode_light_init(){
    for(int i = 1;i < 4;i++){
        for(int j = 0;j < NUM_LEDS;j++){
            this->leds[j] = HAMASTER_COLORS[i];
        }
        FastLED.show();
        vTaskDelay(pdMS_TO_TICKS(500));
        this->reset();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    mode_manager.hamster_mode_init_flag = true;
}

void LightManager::Hamstermode_levelChangeNotification() {
    int index = button_manager.level_now;
    this->reset();  // 先熄灭所有灯
    vTaskDelay(pdMS_TO_TICKS(500));
    for(int i = 0;i < NUM_LEDS;i++){
        this->leds[i] = RAINBOW_COLORS[index];
    }
    FastLED.show();
    vTaskDelay(pdMS_TO_TICKS(500));
    this->reset();
    vTaskDelay(pdMS_TO_TICKS(500));
    for(int i = 0;i < NUM_LEDS;i++){
        this->leds[i] = RAINBOW_COLORS[index];
    }
    FastLED.show();
    vTaskDelay(pdMS_TO_TICKS(500));
    this->reset();
    vTaskDelay(pdMS_TO_TICKS(500));

    button_manager.is_level_raising = false;  //提示完后不再提示
}

void LightManager::Hamstermode_light_update() {
    if(button_manager.is_deading){
        for(int i = 0;i < NUM_LEDS;i++){
            this->leds[i] = CRGB(255, 0, 0);
        }
    }else{
        for(int i = 0;i < NUM_LEDS;i++){
            this->leds[i] = HAMASTER_COLORS[button_manager.hamsterStates[i]];
        }
    }
}

void LightManager::Musicmode_setMusicLight(int note_index,int duration) {
    this->reset();
    int light_index = 0;
    switch (note_index)
    {
    case NOTE_C:
    case NOTE_Cs:
        light_index = 0;
        break;
    case NOTE_D:
        light_index = 1;
        break;
    case NOTE_E:
    case NOTE_Eb:
        light_index = 2;
        break;
    case NOTE_F:
    case NOTE_Fs:
        light_index = 3;
        break;
    case NOTE_G:
    case NOTE_Gs:
        light_index = 4;
        break;
    case NOTE_A:
        light_index = 5;
        break;
    case NOTE_B:
    case NOTE_Bb:
        light_index = 6;
        break;         
    default:
        break;
    }
    this->leds[light_index] = CRGB(random(256), random(256), random(256));  // 随机颜色
    FastLED.show();
}

void light_task(void* pt) {
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(5));
        light_manager.update();
    }
}
