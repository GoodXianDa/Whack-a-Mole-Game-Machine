#ifndef _COMMON_H_
#define _COMMON_H_
#include <math.h>
#include "Arduino.h"
#include <Preferences.h>
#include "stdint.h"
#include "mode_manager.h"
#include "button_manager.h"
#include "light_manager.h"
#include "buzzer_manager.h"
#include "motor_manager.h"

#define pi 3.1415926f
#define RAD2DEG (180.0f / pi)
#define DEG2RAD (pi / 180.0f)

// 取最大值
#define Max(a, b) (a > b ? a : b)
// 取最小值
#define Min(a, b) (a < b ? a : b)
// 双端限幅 a<x<b
#define Mid(x, a, b) Max(Min(x, b), a)
// 0的近似值
#define MINI 1e-3

extern ModeManager mode_manager;
extern ButtonManager button_manager;
extern LightManager light_manager;
extern BuzzerManager buzzer_manager;
extern MotorManager motor_manager;


float invSqrt(float x);
int sgn(int x);
int fsgn(float x);
float sgn_like(float x, float d);
#endif