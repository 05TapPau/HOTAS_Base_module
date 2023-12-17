#include "Arduino.h"
#include <Wire.h>

#define buttonCount 5

// data to be sent and received
struct I2cTxStruct
{
    byte Buttondata[buttonCount]; // 26
};

bool Buttons[buttonCount]{
    0, 0, 0, 0, 0, /*hat0*/

//    0, 0, 0, 0, 0, /*hat1*/
//    0, 0, 0, 0, 0, /*hat2*/
//    0, 0, 0, 0, 0, /*hat3*/
//    0, 0,          /*trig*/
//    0,             /*pnky*/
//    0,             /*indx*/
//    0,             /*padd*/
//    0              /*Pckl*/
};

I2cTxStruct txData = {0, 0, 0, 0, 0, /*0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0*/};

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

void updateDataToSend()
{
    // update the data after the previous message has been sent
    // this ensures the new data will ready when the next request arrives
    if (rqSent == true)
    {
        rqSent = false;
        for (int i = 0; i < buttonCount; i++)
        {
            txData.Buttondata[i] = Buttons[i];
        }
    }
}

/*

//======Buttonreadout======
void checkHat(int HatNum,int NumOfDir){

}
*/
void updateButtonStates(){
    //      void checkHat();            should i get bored i can code this out further so the hats are contained within one function
    for (int i = 0; i < buttonCount; i++)
    {
        Buttons[i] = digitalRead(Buttons[i]);
    }
}




//======Arduino======
void setup()
{
    // set up I2C
    Wire.begin(thisAddress);      // join i2c bus
    Wire.onRequest(requestEvent); // register function to be called when a request arrives
}

void loop()
{
    // this function updates the data in txData
    updateButtonStates();
    updateDataToSend();
    // this function sends the data if one is ready to be sent
}