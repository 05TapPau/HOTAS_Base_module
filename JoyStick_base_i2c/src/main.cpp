#include "Arduino.h"
#include <Wire.h>

//===================
// Using I2C to send and receive structs between two Arduinos
//   SDA is the data connection and SCL is the clock connection
//   On an Uno  SDA is A4 and SCL is A5
//   On an Mega SDA is 20 and SCL is 21
//   GNDs must also be connected
//===================

// data to be received
struct I2cRxStruct
{
    bool Button[26];  // 26 bytes
                      //------
                      // 36
};

int messageSize = 26;

I2cRxStruct rxData;

const byte thisAddress = 8;
const byte otherAddress = 9;

void setup(){
    Wire.begin(thisAddress);
}

void requestData()
{
    byte stop = true;
    byte numBytes = messageSize;
    Wire.requestFrom(otherAddress, numBytes, stop);
    // the request is immediately followed by the read for the response
    Wire.readBytes((byte *)&rxData, numBytes);
}

void loop()
{
    requestData();
    // this bit checks if a message has been received
}