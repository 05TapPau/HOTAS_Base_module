#include "Arduino.h"
#include <Wire.h>

//  possibly a future imprivement to use les storage allthough thtas not yet a problem and probably wont get one either
/*
#define ByteNum 4
int BitNum = 0, PinI = 0;
bool Button;

byte ButtonBytes[ByteNum]{
  0,0,0,0
};


bitWrite(ByteNum,BitNum, Button); //byte, bit, set/clear
*/

#define buttonNum 26
#define EnableTrim 2
#define EnableTMS 3
#define EnableDMS 4

//  there is a struct named I2cTxStruct witch consists of a Bytearray with 26 Bytes
struct I2cTxStruct
{
    byte Buttondata[buttonNum]; // 26
    
};

I2cTxStruct txData = {
    0, 0, 0, 0, 0, /*hat0*/
    0, 0, 0, 0, 0, /*hat1*/
    0, 0, 0, 0, 0, /*hat2*/
    0, 0, 0, 0, 0, /*hat3*/
    0, 0,          /*trig*/
    0,             /*pnky*/
    0,             /*indx*/
    0,             /*padd*/
    0              /*Pckl*/
};

bool newTxData = false;
bool rqSent = false;

// I2C Addresses
const byte thisAddress = 9; // these need to be swapped for the other Arduino
const byte otherAddress = 8;

//======I2C functions======
//  Original with struct
void requestEvent()
{
    Wire.write((byte *)&txData, sizeof(txData));
}
void CheckTrim()
{
    digitalWrite(EnableTrim, LOW);
    txData.Buttondata[0] = digitalRead(5);
    txData.Buttondata[1] = digitalRead(6);
    txData.Buttondata[2] = digitalRead(7);
    txData.Buttondata[3] = digitalRead(8);
    txData.Buttondata[4] = digitalRead(9);
    digitalWrite(EnableTrim, HIGH);
}
void CheckTMS()
{
    digitalWrite(EnableTMS, LOW);
    txData.Buttondata[5] = digitalRead(5);
    txData.Buttondata[6] = digitalRead(6);
    txData.Buttondata[7] = digitalRead(7);
    txData.Buttondata[8] = digitalRead(8);
    txData.Buttondata[9] = digitalRead(9);
    digitalWrite(EnableTMS, HIGH);
}
void CheckDMS()
{
    digitalWrite(EnableDMS, LOW);
    txData.Buttondata[10] = digitalRead(5);
    txData.Buttondata[11] = digitalRead(6);
    txData.Buttondata[12] = digitalRead(7);
    txData.Buttondata[13] = digitalRead(8);
    txData.Buttondata[14] = digitalRead(9);
    digitalWrite(EnableDMS, HIGH);
}

void updateButtonStates()
{
    //      void checkHat();            should i get bored i could code this out further so the hats are contained within one function
    //      haha i got bored :)         CheckHats(1); gotta give it a int so it knows what hat to check
    /*
            Trim, TMS and DMS have to be enabled, cuz they run on one bus
            For now this will be divided into three functions, so its easyer to find any errors
            go into function
            enable the Hatswitch, read out its 5 pins, write them into the data that should be sent, disable the hat go to next and repeat
    */
    CheckTrim();
    CheckTMS();
    CheckDMS();

    txData.Buttondata[15] = digitalRead(10);
    txData.Buttondata[16] = digitalRead(11);
    txData.Buttondata[17] = digitalRead(12);
    txData.Buttondata[18] = !digitalRead(13);
    txData.Buttondata[19] = digitalRead(A0);
    txData.Buttondata[20] = digitalRead(A1);
    txData.Buttondata[21] = digitalRead(A2);
    txData.Buttondata[22] = digitalRead(A3);
    (analogRead(A6)>512) ? txData.Buttondata[23] = 1 : txData.Buttondata[23] = 0;   //  Dont aske me why butt i couldnt read these pins digitaly?
    (analogRead(A7)>512) ? txData.Buttondata[24] = 1 : txData.Buttondata[24] = 0;   //  so if analog above 512 (1024/2) its =true elese =false
}

//======Arduino======
void setup()
{
    // set up I2C
    Wire.begin(thisAddress);      // join i2c bus
    Wire.onRequest(requestEvent); // register function to be called when a request arrives

    //  setup Arduino
    pinMode(EnableTrim, OUTPUT);
    pinMode(EnableTMS, OUTPUT);
    pinMode(EnableDMS, OUTPUT);

    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
}

void loop()
{
    // this function updates the data in txData
    updateButtonStates();
}
