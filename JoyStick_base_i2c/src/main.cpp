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
// const byte ThrottleAddress = 10;
// const byte PedalsAddress = 11;

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
Joystick_ Base_module( //  name the axies down below whatever you want, most games will recognize them anyways so dont even bother
    JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
    32, 0,               //  26  Buttons total on flightstick (might increas with an addition of a throttle); 0 hatswitches //i know i have hats on there butt i read them out as buttons
    true, true, false,   //  X,Y Axies used (roll and pitch yaw at some point with rudders maybe?)
    false, false, false, //  no "right" X,Y, and Z
    false, false, false, //  rudder, Throttle and accelorator
    false, false);       //  brakes and steering

void hotas()
{ //      Do da Hotas 
    Base_module.setYAxis(analogRead(A0));
    Base_module.setXAxis(analogRead(A1));
    Base_module.setThrottle(analogRead(A2));

    Base_module.setButton(0, rxData.Button[0]);
    Base_module.setButton(1, rxData.Button[1]);
    Base_module.setButton(2, rxData.Button[2]);
    Base_module.setButton(3, rxData.Button[3]);
    Base_module.setButton(4, rxData.Button[4]);
    Base_module.setButton(5, rxData.Button[5]);
    Base_module.setButton(6, rxData.Button[6]);
    Base_module.setButton(7, rxData.Button[7]);
    Base_module.setButton(8, rxData.Button[8]);
    Base_module.setButton(9, rxData.Button[9]);
    Base_module.setButton(10, rxData.Button[10]);
    Base_module.setButton(11, rxData.Button[11]);
    Base_module.setButton(12, rxData.Button[12]);
    Base_module.setButton(13, rxData.Button[13]);
    Base_module.setButton(14, rxData.Button[14]);
    Base_module.setButton(15, rxData.Button[15]);
    Base_module.setButton(16, rxData.Button[16]);
    Base_module.setButton(17, rxData.Button[17]);
    Base_module.setButton(18, rxData.Button[18]);
    Base_module.setButton(19, rxData.Button[19]);
    Base_module.setButton(20, rxData.Button[20]);
    Base_module.setButton(21, rxData.Button[21]);
    Base_module.setButton(22, rxData.Button[22]);
    Base_module.setButton(23, rxData.Button[23]);
    Base_module.setButton(24, rxData.Button[24]);
    Base_module.setButton(25, rxData.Button[25]);
}

//======All-Arduino-Code======
void setup()
{
    //  I2C
    Wire.begin(BaseAddress);

    //  Pins in use
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);

    //  Pins not in use (remeber to check if you use Arduino pro micro(does not hjave all pins) or Arduino Micro)
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(A6, OUTPUT);    // D4
    pinMode(A7, OUTPUT);    // D6
    pinMode(A8, OUTPUT);    // D8
    pinMode(A9, OUTPUT);    // D9
    pinMode(A10, OUTPUT);   // D10
    pinMode(A11,OUTPUT);    // D12
        //  and all  digital pins

    Base_module.begin();
    Base_module.setXAxisRange(0, 1023);
    Base_module.setYAxisRange(0, 1023);
    Base_module.setThrottleRange(0, 1023);
}

void loop()
{
    hotas();
    requestData();
}
