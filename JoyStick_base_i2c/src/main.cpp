#include "Arduino.h"
#include <Wire.h>

#define buttonCount 5

// data to be received
struct I2cRxStruct
{
    bool Button[buttonCount];  // 26 bytes one byte for on button kinda wast of mem but who cares
};

I2cRxStruct rxData;

const byte thisAddress = 8;
const byte otherAddress = 9;


//======I2C======
void requestData()
{
    byte stop = true;
    byte numBytes = buttonCount;
    Wire.requestFrom(otherAddress, numBytes, stop);
    // the request is immediately followed by the read for the response
    Wire.readBytes((byte *)&rxData, numBytes);
}

//======Joystick======
void hotas(){
//      Do da Hotas shit 
}


//======Arduino======
void setup(){
    Serial.begin(9600);
    Wire.begin(thisAddress);
}

void loop()
{
    requestData();
    hotas();
    for (int i = 0; i < buttonCount; i++)
    {
        Serial.print("Byte ");
        Serial.print(i);
        Serial.print(" = ");
        Serial.println(rxData.Button[i]);
    }
    delay(500);
}