#include "Arduino.h"
#include <Wire.h>

#define buttonNum   26
#define EnableTrim  0
#define EnableTMS   1
#define EnableDMS   2

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

I2cTxStruct txData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool newTxData = false;
bool rqSent = false;

// I2C control stuff
const byte thisAddress = 9; // these need to be swapped for the other Arduino
const byte otherAddress = 8;

//======I2C functions======
void requestEvent()
{
    Wire.write((byte *)&txData, sizeof(txData));
    rqSent = true;
}


//      Change the schematic and board to the requiered pull ups on the arduino side, right now its still on a pulldown config
void CheckTrim()
{
    digitalWrite(EnableTrim,HIGH);

    digitalWrite(EnableTrim,LOW);
}
void CheckTMS()
{
    digitalWrite(EnableTrim,HIGH);

    digitalWrite(EnableTrim,LOW);

}
void CheckDMS()
{
    digitalWrite(EnableTrim,HIGH);

    digitalWrite(EnableTrim,LOW);
}

void updateDataToSend()
{
    // update the data after the previous message has been sent
    // this ensures the new data will ready when the next request arrives
    if (rqSent == true)
    {
        rqSent = false;
        for (int i = 0; i < buttonNum; i++)
        {
            txData.Buttondata[i] = Buttons[i];

            // oh noooo
            // Buttons but fr this thime :/
            /*
            Trim, TMS and DMS have to be enabled, cuz they run on one bus
            For now this will be divided into three functions, so its easyer to find any errors

            go into function
            enable the Hatswitch, read out its 5 pins, write them into the data that should be sent, disable the hat go to next and repeat
            */
            void CheckTrim();
            void CheckTMS();
            void CheckDMS();
        }
    }
}

/*

//======Buttonreadout======
void checkHat(int HatNum,int NumOfDir){

}
*/

void updateButtonStates()
{
    //      void checkHat();            should i get bored i can code this out further so the hats are contained within one function

    for (int i = 0; i < buttonNum; i++)
    {
        Buttons[i] = digitalRead(i + 2);
    }
}

//======Arduino======
void setup()
{
    // set up I2C
    Wire.begin(thisAddress);      // join i2c bus
    Wire.onRequest(requestEvent); // register function to be called when a request arrives

    //  setup Arduino
    pinMode(Buttons[3], INPUT_PULLUP);
    pinMode(Buttons[4], INPUT_PULLUP);
    pinMode(Buttons[5], INPUT_PULLUP);
    pinMode(Buttons[6], INPUT_PULLUP);
    pinMode(Buttons[7], INPUT_PULLUP);

    pinMode(EnableTrim,OUTPUT);
    pinMode(EnableTMS,OUTPUT);
    pinMode(EnableDMS,OUTPUT);
}

void loop()
{
    // this function updates the data in txData
    updateButtonStates();
    updateDataToSend();
    // this function sends the data if one is ready to be sent
}
