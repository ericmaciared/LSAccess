
/*
   File:   LSAccess.ino
   Author: Eric Macià (eric.macia)
           Guillermo Sabaté (guillermo.sabate)

   Created on 24/04/2020
*/

//includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "TTimer.h"
#include "TDoor.h"
#include "TSpeaker.h"
#include "TEUSART.h"
#include "TKeyboard.h"
#include "TInput.h"
#include "TRFID.h"
#include "TGlobalTimer.h"
#include "TAuthentication.h"
//#include "TLCD.h"
//#include "LcTLCD.h"

void setup() {
  initTimer();
  initTDoor();
  initTSpeaker();
  initTEUSART();
  SioPutsCooperative("Booting...\n");
  initTKeyboard();
  initTAuthentication();
  initTInput();
  initTRFID();
  initTGlobalTimer();
  //initMotorLCD();
  //LcInit(2, 16);
}

void loop() {
  motorTDoor();
  motorTSpeaker();
  motorTEUSART();
  motorTKeyboard();
  motorTInput();
  motorTRFID();
  motorTGlobalTimer();
  motorTAuthentication();
  //MotorLCD();
}
