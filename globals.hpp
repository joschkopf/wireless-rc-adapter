#pragma once

#include <Arduino.h>
#include "defines.hpp"

extern const uint8_t FLAGS[8];
extern volatile uint16_t rc_values[CHANNELS];
extern uint16_t rc_min_values[], rc_max_values[CHANNELS];
extern uint8_t tx_shared_flags;