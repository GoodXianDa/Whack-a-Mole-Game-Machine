#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include "Arduino.h"
#include "equipment_def.h"
#include <FastLED.h>

class LightManager
{
private:
    TaskHandle_t _light_task_handler = NULL;
    static const CRGB RAINBOW_COLORS[];
    static const CRGB HAMASTER_COLORS[];
public:
    uint8_t max_bright;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
    CRGB leds[NUM_LEDS]; // 使用FastLED的CRGB数组
    LightManager();
    void init();
    void deinit();
    void reset();
    void update();
    void Hamstermode_light_init();  // 进入打地鼠模式的灯光初始化
    void Hamstermode_levelChangeNotification();  // 打地鼠模式难度升级的灯光提示
    void Hamstermode_light_update();  // 打地鼠模式下灯光部分的逻辑函数
    void Musicmode_light_init();  // 音乐模式下的灯光初始化
    void Musicmode_setMusicLight(int note_index,int duration);// 听音乐模式下灯光部分的逻辑函数
};

void light_task(void *pt);

#endif