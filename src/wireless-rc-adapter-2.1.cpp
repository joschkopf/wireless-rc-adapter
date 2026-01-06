/* Wireless RC Adapter v2.1
 *  http://wireless-rc-adapter.github.io
 * 
 * Connects an RC receiver as a HID compatible
 * joystick to almost any kind of device, with
 * just a simple USB cable.
 * 
 *  GregNau    2015-2019
 */

#include <Arduino.h>
#include "defines.hpp"
#include "globals.hpp"
#include "led.hpp"
#include "memory.hpp"
#include "serial.hpp"
#include "ppm.hpp"
#include "calibration.hpp"
#include "joystick.hpp"

// Global variables
const uint8_t FLAGS[8] = {1, 2, 4, 8, 16, 32, 64, 128};  // Channel value position flags
volatile uint16_t rc_values[CHANNELS] = {0};  // Actual channel values
uint16_t rc_min_values[CHANNELS], rc_max_values[CHANNELS];  // Calibration data arrays
uint8_t tx_shared_flags = 0;

// Setup function
void setup() {
  initLed();  // Configure and init the leds on the board
  readMem();  // Read calibration data from eeprom

  #if defined(SERIAL_DEBUG)
    initSerial();  // Start serial debug output
  #endif

  #if defined(PPM_RECEIVER)
    rcSetupPpm();  // Attach interrupt timer to PPM pin
  #elif defined(PWM_RECEIVER)
    rcSetupPwm();  // Attach interrupt timers to PWM pins
  #endif

  delay(250);  // Give signals some time to settle...

  // Waits here until valid signal on CAL_CHANNEL
  rcCalibrate();  // Check if calibration necessary or triggered with full throttle

  #if !defined(SERIAL_DEBUG)
    initJoystick();  // Setup joystick output
    startJoystick();  // Start joystick output
  #endif
}

void loop() {
  #if defined(PWM_RECEIVER)
    rcProcessPwm();  // Measure channels pwm timing values.
  #endif
  
  #if defined(SERIAL_DEBUG)
    rcPrintChannels();  // Print RAW channel values on serial terminal.
  #else
    outputJoystick();  // Output channels where there is new data
  #endif
}
