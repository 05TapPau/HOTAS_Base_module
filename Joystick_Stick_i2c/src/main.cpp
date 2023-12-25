#include "Arduino.h"
#include <Wire.h>

#define buttonNum 26
#define EnableTrim 0
#define EnableTMS 1
#define EnableDMS 2

// data to be sent and received
struct I2cTxStruct
{
    byte Buttondata[buttonNum]; // 26
};

bool Buttons[buttonNum]{
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
    rqSent = true;
}

/*
    //   try without struct straight from array
void requestEventNoStruct()
{
    Wire.write((byte *)&Buttons, sizeof(Buttons));
    rqSent = true;
}
*/

void CheckHats(int HatNum)
{ // requires the number of the Hat wich equals to the Enable pin of the Hatswitch
    switch (HatNum)
    {
    case 0:
        digitalWrite(EnableTrim, HIGH);
        digitalRead(Buttons[3]);
        digitalRead(Buttons[4]);
        digitalRead(Buttons[5]);
        digitalRead(Buttons[6]);
        digitalRead(Buttons[7]);
        digitalWrite(EnableTrim, LOW);
        break;

    case 1:
        digitalWrite(EnableTMS, HIGH);
        digitalRead(Buttons[3]);
        digitalRead(Buttons[4]);
        digitalRead(Buttons[5]);
        digitalRead(Buttons[6]);
        digitalRead(Buttons[7]);
        digitalWrite(EnableTMS, LOW);
        break;

    case 2:
        digitalWrite(EnableDMS, HIGH);
        digitalRead(Buttons[3]);
        digitalRead(Buttons[4]);
        digitalRead(Buttons[5]);
        digitalRead(Buttons[6]);
        digitalRead(Buttons[7]);
        digitalWrite(EnableDMS, LOW);
        break;

    default:
        break;
    }
}

void CheckTrim()
{
    digitalWrite(EnableTrim, HIGH);
    Buttons[0] = digitalRead();
    Buttons[1] = digitalRead();
    Buttons[2] = digitalRead();
    Buttons[3] = digitalRead();
    Buttons[4] = digitalRead();
    digitalWrite(EnableTrim, LOW);
}
void CheckTMS()
{
    digitalWrite(EnableTMS, HIGH);
    Buttons[5] = digitalRead();
    Buttons[6] = digitalRead();
    Buttons[7] = digitalRead();
    Buttons[8] = digitalRead();
    Buttons[9] = digitalRead();
    digitalWrite(EnableTMS, LOW);
}
void CheckDMS()
{
    digitalWrite(EnableDMS, HIGH);
    Buttons[10] = digitalRead();
    Buttons[11] = digitalRead();
    Buttons[12] = digitalRead();
    Buttons[13] = digitalRead();
    Buttons[14] = digitalRead();
    digitalWrite(EnableDMS, LOW);
}

void updateDataToSend()
{
    // update the data after the previous message has been sent
    // new data will be ready when the next request arrives
    if (rqSent == true)
    {
        rqSent = false;
        for (int i = 0; i < buttonNum; i++)
        {
            txData.Buttondata[i] = Buttons[i];
        }
    }
}

void updateButtonStates()
{
    //      void checkHat();            should i get bored i could code this out further so the hats are contained within one function
    //      haha i got bored :)         CheckHats(1); gotta give it a int so it knows what hat to check

/*
    for (int i = 0; i < buttonNum; i++)
    {
        Buttons[i] = digitalRead(i + 2);
    }
*/
/*
        Trim, TMS and DMS have to be enabled, cuz they run on one bus
        For now this will be divided into three functions, so its easyer to find any errors

        go into function
        enable the Hatswitch, read out its 5 pins, write them into the data that should be sent, disable the hat go to next and repeat
*/
    CheckTrim();
    CheckTMS();
    CheckDMS();
}

//======Arduino======
void setup()
{
    // set up I2C
    Wire.begin(thisAddress);      // join i2c bus
    Wire.onRequest(requestEvent); // register function to be called when a request arrives
                                  //    Wire.onRequest(requestEventNoStruct);   // register function to be called when a request arrives trying without an array

    //  setup Arduino
    pinMode(Buttons[3], INPUT_PULLUP);
    pinMode(Buttons[4], INPUT_PULLUP);
    pinMode(Buttons[5], INPUT_PULLUP);
    pinMode(Buttons[6], INPUT_PULLUP);
    pinMode(Buttons[7], INPUT_PULLUP);

    pinMode(EnableTrim, OUTPUT);
    pinMode(EnableTMS, OUTPUT);
    pinMode(EnableDMS, OUTPUT);
}

void loop()
{
    // this function updates the data in txData
    updateButtonStates();
    updateDataToSend();
    // this function sends the data if one is ready to be sent
}
