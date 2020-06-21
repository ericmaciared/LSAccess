
/*
 * File:   LSAccess.ino
 * Author: Eric Macià (eric.macia)
 *         Guillermo Sabaté (guillermo.sabate)
 *
 * Created on 24/04/2020
 */

//includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "TTimer.h"
#include "TDoor.h"
#include "TSpeaker.h"
#include "TEUSART.h"

void setup(){
  initTimer();
  initTDoor();
  initTSpeaker();
  initTEUSART();
  SioPutsCooperative("Booting...");
}

void loop(){
  motorTDoor();
  motorTSpeaker();
  motorTEUSART();
}
