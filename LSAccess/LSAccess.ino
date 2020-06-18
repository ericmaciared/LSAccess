
/*
 * File:   main.c
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

void setup(){
  Serial.begin(9600);
  initTimer();
  initTDoor();
  initTSpeaker();
}

void loop(){
  motorTDoor();
  motorTSpeaker();
}
