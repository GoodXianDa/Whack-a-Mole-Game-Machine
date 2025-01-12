// Copyright (c) 2025 GoodXianDa
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/M
#include <Arduino.h>
#include "common.h"

void setup() {
  Serial.begin(9600);
  mode_manager.init();
  button_manager.init();
  light_manager.init();
  buzzer_manager.init();
  motor_manager.init();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelay(pdMS_TO_TICKS(1000));
}
