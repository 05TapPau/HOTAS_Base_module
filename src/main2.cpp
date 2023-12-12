#include <Arduino.h>
#include "Joystick.h"

#define xaxies A0
#define yaxies A1
#define rudder A2
#define throttle A3
#define pedalbrakes A4

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS,
  32, 0,                  // Button Count, Hat Switch Count                 32 possible buttons but no hatswitches
  true, true, false,      // X and Y, but no Z Axis                         aka roll and pitch
  false, false, false,    // No Rx, Ry, or Rz
  true, true,             // Rudder and throttle                            yaw
  false, true, false);    // No accelerator,but pedalbrakes(i gues) and no steering

void setup(){
    Joystick.begin();
    Joystick.setXAxisRange(0, 1023);
    Joystick.setYAxisRange(0, 1023);
    Joystick.setRudderRange(0, 1023);
    Joystick.setThrottleRange(0,1023);
    Joystick.setBrakeRange(0, 1023);
}

void loop(){
    analogRead();
}