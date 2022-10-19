#pragma once

#include <Arduino.h>
#include "defines.hpp"

#if defined(SERIAL_DEBUG)
    void initSerial();
    void rcPrintChannels();
#endif