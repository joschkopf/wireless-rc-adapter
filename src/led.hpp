#pragma once

#include <Arduino.h>

void initLed();
void ledOn();
void ledOff();
void blinkLed(uint8_t times, uint8_t dly);
void waveLed(uint16_t dly);