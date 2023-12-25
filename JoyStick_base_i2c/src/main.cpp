#include "Arduino.h"
#include <Wire.h>

#define buttonCount 5

// data to be received
struct I2cRxStruct
{
    bool Button[buttonCount]; // 26 bytes one byte for on button kinda wast of mem but who cares
};

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
    for (int i = 0; i < buttonCount; i++)
    {
        Serial.print("Byte ");
        Serial.print(i);
        Serial.print(" = ");
        Serial.println(rxData.Button[i]);
    }
    Serial.println();
    delay(500);
}

//======Joystick======
void hotas()
{
    //      Do da Hotas shit
}

//======Arduino======
void setup()
{
    Serial.begin(9600);
    Wire.begin(BaseAddress);
}

void loop()
{
    requestData();
    hotas();
}