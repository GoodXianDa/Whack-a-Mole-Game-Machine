#ifndef _BUZZER_MANAGER_H_
#define _BUZZER_MANAGER_H_

#include "Arduino.h"
#include "equipment_def.h"

typedef struct note_data_t
{
    note_t note;    //音符 音符频率
    uint8_t octave; //音阶 中音为4
    uint16_t time;  // 持续时间 单位毫秒
}note_data;

class BuzzerManager
{
private:
    // 按键到音符的映射
    const note_t button_to_note[NUM_BUTTONS] = {
        NOTE_C,  // 按键 0 -> C
        NOTE_D,  // 按键 1 -> D
        NOTE_E,  // 按键 2 -> E
        NOTE_F,  // 按键 3 -> F
        NOTE_G,  // 按键 4 -> G
        NOTE_A,  // 按键 5 -> A
        NOTE_B   // 按键 6 -> B
    };
    TaskHandle_t _buzzer_task_handler = NULL;
public:
    //存储七首歌曲
    static const note_data GoSchool[];  
    static const note_data GGBoom[];
    static const note_data Balala[];
    static const note_data KillRockCity[];
    static const note_data LoveSong[];
    static const note_data Song_for_No_One[];
    static const note_data Maple[];

    static const uint16_t GoSchool_tonesize;
    static const uint16_t GGBoom_tonesize;
    static const uint16_t Balala_tonesize;
    static const uint16_t KillRockCity_tonesize;
    static const uint16_t LoveSong_tonesize;
    static const uint16_t Song_for_No_One_tonesize;
    static const uint16_t Maple_tonesize;

    static const note_data* song_array[];       // 存储乐谱指针数组
    static const uint16_t song_length[];        // 存储乐谱长度数组

    int song_list;
    BuzzerManager();
    void init();
    void deinit();
    void reset();
    void update();
    void mute();
    void playErrorSound();  
    void playRightSound();
};

void buzzer_task(void *pt);


#endif