#include "buzzer_manager.h"
#include "common.h"

// 静态数组定义和初始化
const note_data BuzzerManager::GoSchool[] =
{
    {NOTE_C, 4, 250}, {NOTE_D, 4, 250}, {NOTE_E, 4, 250}, {NOTE_C, 4, 250}, {NOTE_G, 4, 1000},
    {NOTE_A, 4, 250}, {NOTE_A, 4, 250}, {NOTE_C, 5, 250}, {NOTE_A, 4, 250}, {NOTE_G, 4, 1000},
    {NOTE_A, 4, 250}, {NOTE_A, 4, 250}, {NOTE_C, 5, 500}, {NOTE_G, 4, 250}, {NOTE_A, 4, 250}, {NOTE_E, 4, 500},
    {NOTE_A, 4, 250}, {NOTE_G, 4, 250}, {NOTE_E, 4, 250}, {NOTE_G, 4, 250}, {NOTE_E, 4, 250},
    {NOTE_C, 4, 250}, {NOTE_D, 4, 250}, {NOTE_E, 4, 250}, {NOTE_G, 4, 1000},
    {NOTE_C, 4, 250}, {NOTE_D, 4, 250}, {NOTE_E, 4, 250}, {NOTE_C, 4, 250}, {NOTE_G, 4, 1000},
    {NOTE_A, 4, 250}, {NOTE_A, 4, 250}, {NOTE_C, 5, 250}, {NOTE_A, 4, 250}, {NOTE_G, 4, 1000},
    {NOTE_A, 4, 250}, {NOTE_A, 4, 250}, {NOTE_C, 5, 500}, {NOTE_G, 4, 250}, {NOTE_A, 4, 250}, {NOTE_E, 4, 500},
    {NOTE_A, 4, 250}, {NOTE_G, 4, 250}, {NOTE_E, 4, 250}, {NOTE_G, 4, 250}, {NOTE_E, 4, 250},
    {NOTE_C, 4, 250}, {NOTE_D, 4, 250}, {NOTE_E, 4, 250}, {NOTE_C, 4, 1000}
};

const note_data BuzzerManager::GGBoom[] = {
    {NOTE_E, 4, 250}, {NOTE_E, 4, 250}, {NOTE_E, 4, 250}, {NOTE_C, 4, 250},  // 3 3 3 1
    {NOTE_E, 4, 125}, {NOTE_F, 4, 250}, {NOTE_E, 4, 125},{NOTE_E, 4, 125}, {NOTE_E, 4, 125}, {NOTE_F, 4, 125}, {NOTE_E, 4, 125},  // 3 4 3 3 3 4 3
    {NOTE_D, 4, 125}, {NOTE_D, 4, 375}, {NOTE_A, 4, 250}, {NOTE_D, 4, 125}, {NOTE_D, 4, 125},
    {NOTE_D, 4, 1000},                        
    {NOTE_G, 4, 250}, {NOTE_G, 4, 250}, {NOTE_G, 4, 250}, {NOTE_D, 4, 250},  // 5 5 5 2
    {NOTE_G, 4, 125},{NOTE_A, 4, 125},{NOTE_G, 4, 125},{NOTE_G, 4, 250},{NOTE_G, 4, 125},{NOTE_A, 4, 125},{NOTE_G, 4, 125},
    {NOTE_F, 4, 125},{NOTE_F, 4, 250},{NOTE_F, 4, 125}, {NOTE_G, 4, 125},{NOTE_F, 4, 250},{NOTE_E, 4, 125},
    {NOTE_E, 4, 1000},
    {NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_D, 4, 250},
    {NOTE_G, 4, 125},{NOTE_A, 4, 125},{NOTE_G, 4, 125},{NOTE_G, 4, 250},{NOTE_G, 4, 125},{NOTE_A, 4, 125},{NOTE_B, 4, 125},
    {NOTE_C, 5, 125},{NOTE_C, 5, 375},{NOTE_B, 4, 125},{NOTE_B, 4, 250},{NOTE_C, 5, 1250}
};

const note_data BuzzerManager::Balala[] =
{
    {NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 500},{NOTE_E, 4, 250},{NOTE_G, 4, 1250},
    {NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_E, 4, 250},{NOTE_D, 4, 500},{NOTE_C, 4, 1250},
    {NOTE_A, 4, 500},{NOTE_A, 4, 500},{NOTE_A, 4, 500},{NOTE_A, 4, 500},
    {NOTE_G, 4, 250},{NOTE_C, 5, 250},{NOTE_B, 4, 250},{NOTE_C, 5, 250},{NOTE_G, 4, 500},{NOTE_G, 4, 250},{NOTE_E, 4, 250},
    {NOTE_F, 4, 500},{NOTE_G, 4, 500},{NOTE_A, 4, 500},{NOTE_G, 4, 250},{NOTE_G, 4, 1250},
    {NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_E, 4, 250},{NOTE_G, 4, 1250},
    {NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_G, 4, 250},{NOTE_C, 5, 250},{NOTE_B, 4, 250},{NOTE_C, 5, 1250},
    {NOTE_E, 5, 250},{NOTE_D, 5, 250},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_A, 4, 500},
    {NOTE_G, 4, 500},{NOTE_C, 5, 500},{NOTE_C, 5, 500},{NOTE_B, 4, 250},{NOTE_C, 5, 1250}
};

const note_data BuzzerManager::KillRockCity[] =
{
    {NOTE_G, 5, 250},{NOTE_G, 5, 500},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_E, 5, 250},
    {NOTE_E, 5, 1000},{NOTE_C, 5, 250},
    {NOTE_A, 4, 500},{NOTE_C, 5, 500},{NOTE_D, 5, 500},{NOTE_D, 5, 500},
    {NOTE_E, 5, 1000},{NOTE_G, 5, 250},
    {NOTE_G, 5, 500},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_E, 5, 250},
    {NOTE_E, 5, 250},{NOTE_C, 5, 250},{NOTE_C, 5, 500},{NOTE_A, 4, 250},{NOTE_B, 4, 250},
    {NOTE_C, 5, 500},{NOTE_D, 5, 500},{NOTE_A, 4, 750},{NOTE_G, 4, 250},
    {NOTE_G, 4, 250},{NOTE_A, 4, 250},{NOTE_A, 4, 250},{NOTE_G, 5, 250},
    {NOTE_G, 5, 500},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_E, 5, 250},
    {NOTE_E, 5, 1000},{NOTE_C, 5, 250},
    {NOTE_A, 4, 500},{NOTE_C, 5, 500},{NOTE_D, 5, 500},{NOTE_D, 5, 500},
    {NOTE_E, 5, 1000},{NOTE_G, 5, 250}, 
    {NOTE_G, 5, 500},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_G, 5, 250},{NOTE_E, 5, 250},
    {NOTE_E, 5, 250},{NOTE_C, 5, 250},{NOTE_C, 5, 500},{NOTE_A, 4, 250},{NOTE_B, 4, 250},
    {NOTE_C, 5, 500},{NOTE_D, 5, 500},{NOTE_A, 4, 750},{NOTE_G, 4, 250},
    {NOTE_A, 4, 750},{NOTE_A, 4, 250},{NOTE_B, 4, 250},
    {NOTE_C, 5, 750},{NOTE_D, 5, 750},
    {NOTE_A, 4, 750},{NOTE_G, 4, 750},
    {NOTE_A, 4, 1250}
};

const note_data BuzzerManager::LoveSong[] =
{
    {NOTE_G, 5, 500},{NOTE_E, 5, 500},
    {NOTE_E, 5, 250},{NOTE_F, 5, 250},{NOTE_E, 5, 250},{NOTE_D, 5, 500},{NOTE_C, 5, 250},{NOTE_B, 4, 500},
    {NOTE_G, 5, 500},{NOTE_E, 5, 500},
    {NOTE_E, 5, 250},{NOTE_F, 5, 250},{NOTE_E, 5, 250},{NOTE_D, 5, 500},{NOTE_C, 5, 250},{NOTE_E, 5, 500},
    {NOTE_A, 5, 500},{NOTE_E, 5, 750},{NOTE_E, 5, 250},
    {NOTE_D, 5, 250},{NOTE_C, 5, 250},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_C, 5, 750},{NOTE_E, 5, 250},
    {NOTE_D, 5, 250},{NOTE_C, 5, 250},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_C, 5, 500},{NOTE_C, 5, 250},{NOTE_D, 5, 250},
    {NOTE_E, 5, 250},{NOTE_C, 5, 250},{NOTE_C, 5, 500},{NOTE_G, 4, 250},{NOTE_A, 4, 250},{NOTE_C, 5, 250},{NOTE_D, 5, 250},
    {NOTE_G, 5, 500},{NOTE_E, 5, 500},
    {NOTE_E, 5, 250},{NOTE_F, 5, 250},{NOTE_E, 5, 250},{NOTE_D, 5, 500},{NOTE_C, 5, 250},{NOTE_B, 4, 500},
    {NOTE_G, 5, 500},{NOTE_E, 5, 500},
    {NOTE_E, 5, 250},{NOTE_F, 5, 250},{NOTE_E, 5, 250},{NOTE_D, 5, 500},{NOTE_C, 5, 250},{NOTE_E, 5, 500},
    {NOTE_A, 5, 750},{NOTE_E, 5, 250},{NOTE_D, 5, 250},{NOTE_E, 5, 250},{NOTE_A, 4, 250},
    {NOTE_C, 5, 250},{NOTE_D, 5, 250},{NOTE_Eb, 5, 250},{NOTE_Cs, 5, 750},{NOTE_C, 5, 250},{NOTE_D, 5, 250},
    {NOTE_B, 4, 250},{NOTE_G, 4, 250},{NOTE_A, 4, 250},{NOTE_G, 4, 500},{NOTE_G, 4, 250},{NOTE_C, 5, 250},{NOTE_D, 5, 250},
    {NOTE_E, 5, 250},{NOTE_D, 5, 250},{NOTE_C, 5, 250},{NOTE_A, 4, 250},{NOTE_C, 5, 500},{NOTE_C, 5, 250},{NOTE_A, 4, 250},
    {NOTE_E, 5, 500},{NOTE_D, 5, 500},{NOTE_C, 5, 250},{NOTE_D, 5, 250},{NOTE_C, 5, 250},{NOTE_D, 5, 250},
    {NOTE_G, 5, 500},{NOTE_Eb, 5, 250},{NOTE_Cs, 5, 250},{NOTE_C, 5, 1000},
    {NOTE_Eb, 5, 250},{NOTE_Cs, 5, 250},{NOTE_D, 5, 500},
    {NOTE_C, 5, 1250}
};

const note_data BuzzerManager::Song_for_No_One[] =
{
    {NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 400},{NOTE_E, 4, 200},{NOTE_B, 3, 200},
    {NOTE_B, 3, 800}, {NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 400},{NOTE_E, 4, 200},{NOTE_C, 4, 400},
    {NOTE_C, 4, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_A, 4, 200},{NOTE_A, 4, 200},{NOTE_C, 4, 200},{NOTE_C, 4, 400},
    {NOTE_C, 4, 400},{NOTE_Gs, 3, 200},{NOTE_C, 4, 200},{NOTE_C, 4, 1080},{NOTE_G, 3, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_C, 4, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_C, 4, 200},
    {NOTE_C, 4, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_B, 3, 200},
    {NOTE_B, 3, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 400},{NOTE_E, 4, 200},{NOTE_C, 4, 400},
    {NOTE_C, 4, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_A, 4, 200},{NOTE_A, 4, 200},{NOTE_C, 4, 200},{NOTE_C, 4, 200},{NOTE_D, 4, 200},{NOTE_D, 4, 200},{NOTE_E, 4, 1080},
    {NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_F, 4, 200},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 200},{NOTE_C, 4, 200},{NOTE_D, 4, 800},
    {NOTE_D, 4, 400},{NOTE_C, 4, 400},{NOTE_C, 4, 2000},{NOTE_C, 4, 400},{NOTE_B, 3, 400},
    {NOTE_B, 3, 2000},{NOTE_B, 3, 400},{NOTE_D, 4, 800},
    {NOTE_D, 4, 400},{NOTE_C, 4, 400},{NOTE_C, 4, 2400},
    {NOTE_G, 4, 3200},
    {NOTE_A, 3, 400},{NOTE_C, 4, 400},{NOTE_D, 4, 400},{NOTE_E, 4, 600},{NOTE_C, 4, 200},{NOTE_C, 4, 200},{NOTE_D, 4, 400},{NOTE_E, 4, 200},
    {NOTE_E, 4, 600},{NOTE_C, 4, 200},{NOTE_C, 4, 400},{NOTE_D, 4, 400},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_G, 4, 200},{NOTE_G, 4, 400},
    {NOTE_C, 4, 200},{NOTE_D, 4, 400},{NOTE_Eb, 4, 200},{NOTE_E, 4, 400},{NOTE_C, 4, 400},{NOTE_C, 4, 400},{NOTE_G, 3, 400},
    {NOTE_Gs, 4, 600},{NOTE_Gs, 4, 200},{NOTE_Gs, 4, 400},{NOTE_Bb, 4, 200},{NOTE_B, 4, 200},{NOTE_G, 4, 1000},{NOTE_F, 4, 200},{NOTE_G, 4, 600},
    {NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 400},{NOTE_E, 4, 200},{NOTE_B, 3, 200},
    {NOTE_B, 3, 800}, {NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 400},{NOTE_E, 4, 200},{NOTE_C, 4, 400},
    {NOTE_C, 4, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_A, 4, 200},{NOTE_A, 4, 200},{NOTE_C, 4, 200},{NOTE_C, 4, 400},
    {NOTE_C, 4, 400},{NOTE_Gs, 3, 200},{NOTE_C, 4, 200},{NOTE_C, 4, 1080},{NOTE_G, 3, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_C, 4, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_C, 4, 200},
    {NOTE_C, 4, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_B, 3, 200},
    {NOTE_B, 3, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_F, 4, 200},{NOTE_F, 4, 400},{NOTE_E, 4, 200},{NOTE_C, 4, 400},
    {NOTE_C, 4, 800},{NOTE_E, 4, 200},{NOTE_G, 4, 400},{NOTE_A, 3, 200},{NOTE_A, 4, 200},{NOTE_C, 4, 200},{NOTE_C, 4, 200},{NOTE_D, 4, 200},{NOTE_D, 4, 200},{NOTE_E, 4, 1080},
    {NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_F, 4, 200},{NOTE_E, 4, 400},{NOTE_F, 4, 200},{NOTE_E, 4, 200},{NOTE_E, 4, 200},{NOTE_F, 4, 200},{NOTE_E, 4, 200},{NOTE_C, 4, 200},{NOTE_D, 4, 800},
    {NOTE_D, 4, 400},{NOTE_C, 4, 400},{NOTE_C, 4, 2000},{NOTE_C, 4, 400},{NOTE_B, 3, 400},
    {NOTE_B, 3, 2000},{NOTE_B, 3, 400},{NOTE_D, 4, 800},
    {NOTE_D, 4, 400},{NOTE_C, 4, 400},{NOTE_C, 4, 2400},
    {NOTE_G, 4, 3200},
    {NOTE_B, 3, 400},{NOTE_D, 4, 800},{NOTE_D, 4, 400},{NOTE_C, 4, 400},{NOTE_C, 4, 1200}
};

const note_data BuzzerManager::Maple[] =
{
    {NOTE_G, 4 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},{NOTE_C, 5 ,375},{NOTE_D, 5 ,375},{NOTE_E, 5 ,375},{NOTE_C, 5 ,375},
    {NOTE_D, 5 ,375},{NOTE_G, 5 ,750},{NOTE_G, 5 ,375},{NOTE_D, 5 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},
    {NOTE_C, 5 ,375},{NOTE_C, 5 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},{NOTE_C, 5 ,375},{NOTE_D, 5 ,375},{NOTE_E, 5 ,375},{NOTE_F, 5 ,375},
    {NOTE_F, 5 ,375},{NOTE_E, 5 ,1125},{NOTE_E, 5 ,375},{NOTE_E, 5 ,375},{NOTE_G, 5 ,375},
    {NOTE_G, 5 ,375},{NOTE_A, 5 ,1125},{NOTE_C, 5 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},{NOTE_B, 4 ,375},{NOTE_A, 5 ,375},
    {NOTE_A, 5 ,375},{NOTE_G, 5 ,375},{NOTE_G, 5 ,375},{NOTE_E, 5 ,187},{NOTE_E, 5 ,187},{NOTE_E, 5 ,187},{NOTE_E, 5 ,562},{NOTE_F, 5 ,187},{NOTE_G, 5 ,187},
    {NOTE_G, 5 ,375},{NOTE_F, 5 ,375},{NOTE_F, 5 ,375},{NOTE_E, 5 ,187},{NOTE_E, 5 ,187},{NOTE_E, 5 ,187},{NOTE_D, 5 ,562},{NOTE_D, 5 ,375},{NOTE_D, 5 ,187},{NOTE_E, 5 ,187},
    {NOTE_G, 5 ,375},{NOTE_F, 5 ,187},{NOTE_F, 5 ,187},{NOTE_F, 5 ,187},{NOTE_E, 5 ,562},{NOTE_E, 5 ,375},{NOTE_D, 5 ,187},{NOTE_D, 5 ,187},{NOTE_D, 5 ,187},{NOTE_C, 5 ,562},
    {NOTE_G, 4 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},{NOTE_C, 5 ,375},{NOTE_D, 5 ,375},{NOTE_E, 5 ,375},{NOTE_C, 5 ,375},
    {NOTE_D, 5 ,375},{NOTE_G, 5 ,750},{NOTE_G, 5 ,375},{NOTE_D, 5 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},
    {NOTE_C, 5 ,375},{NOTE_C, 5 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},{NOTE_C, 5 ,375},{NOTE_D, 5 ,375},{NOTE_E, 5 ,375},{NOTE_F, 5 ,375},
    {NOTE_F, 5 ,375},{NOTE_E, 5 ,1125},{NOTE_E, 5 ,375},{NOTE_E, 5 ,375},{NOTE_G, 5 ,375},
    {NOTE_G, 5 ,375},{NOTE_A, 5 ,750},{NOTE_C, 5 ,375},{NOTE_C, 5 ,375},{NOTE_B, 4 ,375},{NOTE_B, 4 ,375},{NOTE_A, 5 ,375},
    {NOTE_A, 5 ,375},{NOTE_G, 5 ,375},{NOTE_G, 5 ,375},{NOTE_E, 5 ,187},{NOTE_B, 5 ,187},{NOTE_B, 5 ,187},{NOTE_C, 6,675},
    {NOTE_F, 5 ,187},{NOTE_G, 5 ,187},
    {NOTE_G, 5 ,375},{NOTE_F, 5 ,375},{NOTE_F, 5 ,375},{NOTE_E, 5 ,187},{NOTE_E, 5 ,187},{NOTE_E, 5 ,187},{NOTE_D, 5 ,562},{NOTE_D, 5 ,375},{NOTE_D, 5 ,187},{NOTE_E, 5 ,187},
    {NOTE_G, 5 ,375},{NOTE_F, 5 ,187},{NOTE_F, 5 ,187},{NOTE_F, 5 ,187},{NOTE_E, 5 ,562},{NOTE_D, 5 ,375},{NOTE_C, 5 ,375},{NOTE_D, 5 ,562},{NOTE_C, 5 ,187},
    {NOTE_C, 5 ,1875}
};

// tonesize 在类外定义
const uint16_t BuzzerManager::GoSchool_tonesize = sizeof(BuzzerManager::GoSchool) / sizeof(note_data);
const uint16_t BuzzerManager::GGBoom_tonesize = sizeof(BuzzerManager::GGBoom) / sizeof(note_data);
const uint16_t BuzzerManager::Balala_tonesize = sizeof(BuzzerManager::Balala) / sizeof(note_data);
const uint16_t BuzzerManager::KillRockCity_tonesize = sizeof(BuzzerManager::KillRockCity) / sizeof(note_data);
const uint16_t BuzzerManager::LoveSong_tonesize = sizeof(BuzzerManager::LoveSong) / sizeof(note_data);
const uint16_t BuzzerManager::Song_for_No_One_tonesize = sizeof(BuzzerManager::Song_for_No_One) / sizeof(note_data);
const uint16_t BuzzerManager::Maple_tonesize = sizeof(BuzzerManager::Maple) / sizeof(note_data);

const note_data* BuzzerManager::song_array[] = { BuzzerManager::GoSchool, BuzzerManager::GGBoom, BuzzerManager::Balala,
BuzzerManager::KillRockCity,BuzzerManager::LoveSong,BuzzerManager::Song_for_No_One, BuzzerManager::Maple};
const uint16_t BuzzerManager::song_length[] = { BuzzerManager::GoSchool_tonesize, BuzzerManager::GGBoom_tonesize, BuzzerManager::Balala_tonesize,
BuzzerManager::KillRockCity_tonesize,BuzzerManager::LoveSong_tonesize,BuzzerManager::Song_for_No_One_tonesize ,BuzzerManager::Maple_tonesize};

BuzzerManager::BuzzerManager() {
}

void BuzzerManager::init() {
    Serial.println("ButtonManager::init");

    ledcSetup(CHANNEL_0,FREQUENCY,RESOLUTION);
    ledcAttachPin(BUZZER_PIN,CHANNEL_0);    
    if (xTaskCreate(               // pdPASS表示创建成功
        buzzer_task,          // 函数名
        "buzzer_task",        // 任务名
        8192,              // 分配内存
        NULL,                  // 传参
        2,                     // 优先级
        &_buzzer_task_handler // 操作指针
        ) == pdPASS)
    Serial.println("button_task Created.");

    this->reset();
}

void BuzzerManager::deinit() {
    Serial.println("BuzzerManager::deinit");
    if (NULL != _buzzer_task_handler)
    {
        vTaskDelete(_buzzer_task_handler);
        _buzzer_task_handler = NULL;
    }
}

void BuzzerManager::reset() {
    this->song_list = 0;  //0代表不播放音乐列表中的歌曲
    this->mute();
}

void BuzzerManager::update() {
    switch (mode_manager.mode)
    {
    case hamster_mode_voice:
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (button_manager.is_right_beat == 1) {
                buzzer_manager.playRightSound();
                button_manager.is_right_beat = 0;
            }else if(button_manager.is_right_beat == 2){
                motor_manager.motor_enable = true;
                buzzer_manager.playErrorSound();
                motor_manager.motor_enable = false;
                button_manager.is_right_beat = 0;
            }
        }
        break;
    case play_music_mode:{
        // 检查是否有按键按下
        bool any_button_pressed = false;
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (button_manager.is_button_pressed[i]) {
                any_button_pressed = true;
                break;
            }
        }

        if (any_button_pressed) {
            // 播放所有按下的按键对应的音符
            for (int i = 0; i < NUM_BUTTONS; i++) {
                if (button_manager.is_button_pressed[i]) {
                    ledcWriteNote(CHANNEL_0, button_to_note[i], 4);  // 播放对应音符
                }
            }
        } else {
            // 没有按键按下时静音
            ledcWrite(CHANNEL_0, 0);
        }
        break;
    }
    case listen_music_mode:
        static int target_song_index = -1;
        target_song_index = this->song_list - 1;  //当进入listen_music_mode先储存一开始的歌曲

        if (target_song_index < 0 || target_song_index >= sizeof(song_array) / sizeof(song_array[0])) {  //防止越界访问
            return;
        }

        for(int i=0;i<this->song_length[target_song_index];i++){
            if(!mode_manager.music_enable || mode_manager.mode != listen_music_mode || ((this->song_list - 1) != target_song_index) || button_manager.is_music_on == false) {  // 立即中断
                buzzer_manager.mute();
                light_manager.Musicmode_light_init();
                button_manager.reset();
                break;
            }
            ledcWriteNote(CHANNEL_0,this->song_array[target_song_index][i].note,this->song_array[target_song_index][i].octave);
            light_manager.Musicmode_setMusicLight(this->song_array[target_song_index][i].note,this->song_array[target_song_index][i].time);  // // 更新灯光，和音符的持续时间一致,传递音符的索引
            vTaskDelay(pdMS_TO_TICKS(this->song_array[target_song_index][i].time));
            ledcWrite(CHANNEL_0,0);  //音符播放结束后关闭蜂鸣器
            light_manager.reset();
            vTaskDelay(pdMS_TO_TICKS(5));  //模拟音符小的停顿
        }
        this->song_list = 0;  //不再重复播放音乐
        mode_manager.music_mode_init_flag = false;  //使其重新初始化音乐模式下的灯光效果
        button_manager.is_music_on = false;
        break;
    default:
        break;
    }
}

void BuzzerManager::mute() {
    ledcWrite(CHANNEL_0,0);  //静音
}

void BuzzerManager::playErrorSound() {
    if(mode_manager.music_enable){
        ledcWriteNote(CHANNEL_0,NOTE_C,5);
        vTaskDelay(pdMS_TO_TICKS(25));
        ledcWriteNote(CHANNEL_0,NOTE_D,5);
        vTaskDelay(pdMS_TO_TICKS(25));
        ledcWriteNote(CHANNEL_0,NOTE_C,5);
        vTaskDelay(pdMS_TO_TICKS(25));
        ledcWrite(CHANNEL_0,0);  //音符播放结束后关闭蜂鸣器
    }
}

void BuzzerManager::playRightSound() {
    if(mode_manager.music_enable){
        ledcWriteNote(CHANNEL_0,NOTE_C,4);
        vTaskDelay(pdMS_TO_TICKS(50));
        ledcWriteNote(CHANNEL_0,NOTE_E,4);
        vTaskDelay(pdMS_TO_TICKS(50));
        ledcWriteNote(CHANNEL_0,NOTE_G,4);
        vTaskDelay(pdMS_TO_TICKS(50));
        ledcWrite(CHANNEL_0,0);  //音符播放结束后关闭蜂鸣器
    }
}

void buzzer_task(void* pt) {
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(10));
        if(mode_manager.music_enable){
            buzzer_manager.update();
        }
        else{
            buzzer_manager.mute();
        }
    }
}
