#include <Arduino.h>
#include "Wire.h"
#include "Joystick.h"

Joystick_ Base_module(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS,
                      26, 0,                // Button Count, Hat Switch Count                 32 possible buttons but no hatswitches
                      true, true, false,    // X and Y, Z Axis                                aka roll and pitch
                      false, false, false,  // Rx, Ry, Rz
                      false, true,          // Rudder and throttle                            yaw
                      false, false, false); // accelerator,brakes and steering

bool LastButtonState[26]
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

bool currentButtonState = 0;

void setup(){
  Base_module.begin();
  Base_module.setXAxisRange(0, 1023);
  Base_module.setYAxisRange(0, 1023);
}
void loop()
{
  currentButtonState = !rxData[];
  if (currentButtonState !=)
  {
    /* code */
  }
  
}