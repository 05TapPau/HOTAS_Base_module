#include "Arduino.h"
#include <Wire.h>
#include <Joystick.h>

#define buttonCount 26

//======I2C-All-Code======
// data to be received
struct I2cRxStruct
{
    bool Button[buttonCount]; // 26 bytes one byte for on button kinda wast of mem but who cares
};

bool LastButtonState[26]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool currentButtonState = 0;

I2cRxStruct rxData;
const byte BaseAddress = 8;
const byte StickAddress = 9;
// prep for future ideas ?!
const byte ThrottleAddress = 10;

//======I2C======
void requestData()
{
    byte stop = true;
    byte numBytes = buttonCount;
    Wire.requestFrom(StickAddress, numBytes, stop);
    // the request is immediately followed by the read for the response
    Wire.readBytes((byte *)&rxData, numBytes);
}



//======Joystick-All-Code======
Joystick_ Base_module( //  name the axies down below whatever you want, most games will recognize them anyways so dont even bother :/
    JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
    32, 0,               //  26  Buttons total on flightstick (might increas with an addition of a throttle); 0 hatswitches //i know i have hats on there butt i read them out as buttons
    true, true, false,   //  X,Y Axies used (roll and pitch yaw at some point with rudders maybe?)
    false, false, false, //  no "right" X,Y, and Z
    false, false, false, //  rudder, Throttle and accelorator
    false, false);       //  brakes and steering

void hotas()
{   //      Do da Hotas shit
    Base_module.setYAxis(analogRead(A0));
    Base_module.setXAxis(analogRead(A1));
    Base_module.setThrottle(analogRead(A2));

    for (int index = 0; index < 26; index++)
    {
        currentButtonState = !rxData.Button[index];
        if (currentButtonState != LastButtonState[index])
        {
            switch (index)
            {
            case 0:
                Base_module.setButton(0, currentButtonState);
                break;
            case 1:
                Base_module.setButton(1, currentButtonState);
                break;
            case 2:
                Base_module.setButton(2, currentButtonState);
                break;
            case 3:
                Base_module.setButton(3, currentButtonState);
                break;
            case 4:
                Base_module.setButton(4, currentButtonState);
                break;
            case 5:
                Base_module.setButton(5, currentButtonState);
                break;
            case 6:
                Base_module.setButton(6, currentButtonState);
                break;
            case 7:
                Base_module.setButton(7, currentButtonState);
                break;
            case 8:
                Base_module.setButton(8, currentButtonState);
                break;
            case 9:
                Base_module.setButton(9, currentButtonState);
                break;
            case 10:
                Base_module.setButton(10, currentButtonState);
                break;
            case 11:
                Base_module.setButton(11, currentButtonState);
                break;
            case 12:
                Base_module.setButton(12, currentButtonState);
                break;
            case 13:
                Base_module.setButton(13, currentButtonState);
                break;
            case 14:
                Base_module.setButton(14, currentButtonState);
                break;
            case 15:
                Base_module.setButton(15, currentButtonState);
                break;
            case 16:
                Base_module.setButton(16, currentButtonState);
                break;
            case 17:
                Base_module.setButton(17, currentButtonState);
                break;
            case 18:
                Base_module.setButton(18, currentButtonState);
                break;
            case 19:
                Base_module.setButton(19, currentButtonState);
                break;
            case 20:
                Base_module.setButton(20, currentButtonState);
                break;
            case 21:
                Base_module.setButton(21, currentButtonState);
                break;
            case 22:
                Base_module.setButton(22, currentButtonState);
                break;
            case 23:
                Base_module.setButton(23, currentButtonState);
                break;
            case 24:
                Base_module.setButton(24, currentButtonState);
                break;
            case 25:
                Base_module.setButton(25, currentButtonState);
                break;
            default:
                break;
            }
        }
    }
}



//======All-Arduino-Code======
void setup()
{
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);

    Base_module.begin();
    Base_module.setXAxisRange(0, 1023);
    Base_module.setYAxisRange(0, 1023);
    Base_module.setThrottleRange(0, 1023);
}

void loop()
{
    hotas();
}