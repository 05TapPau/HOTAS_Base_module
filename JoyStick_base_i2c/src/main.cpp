#include "Arduino.h"
#include <Wire.h>

//===================
// Using I2C to send and receive structs between two Arduinos
//   SDA is the data connection and SCL is the clock connection
//   On an Uno  SDA is A4 and SCL is A5
//   On an Mega SDA is 20 and SCL is 21
//   GNDs must also be connected
//===================

// data to be sent and received
struct I2cRxStruct
{
    bool textB[26];     // 26 bytes
    byte padding[10];   // 10
                        //------
                        // 36
};

int messageSize = 36;

I2cRxStruct rxData;

bool newRxData = false;
bool rqData = false;

// I2C control stuff
const byte thisAddress = 8; // these need to be swapped for the other Arduino
const byte otherAddress = 9;

// timing variables
unsigned long prevUpdateTime = 0;
unsigned long updateInterval = 500;

//=================================
void setup()
{
    // set up I2C
    Wire.begin(thisAddress); // join i2c bus
    //~ Wire.onReceive(receiveEvent); // register function to be called when a message arrives
}

//=============
void requestData()
{
    if (rqData == true){ // just one request following every Tx
        byte stop = true;
        byte numBytes = messageSize;
        Wire.requestFrom(otherAddress, numBytes, stop);
        // the request is immediately followed by the read for the response
        Wire.readBytes((byte *)&rxData, numBytes);
        newRxData = true;
        rqData = false;
    }
}

//============
void loop()
{
    // this bit checks if a message has been received
    if (newRxData == true){
        newRxData = false;}
    if (millis() - prevUpdateTime >= updateInterval){
        requestData();prevUpdateTime = millis();}
}