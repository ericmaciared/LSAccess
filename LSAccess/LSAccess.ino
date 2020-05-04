/*
 * File:   main.c
 * Author: Eric Macià (eric.macia)
 *         Guillermo Sabaté (guillermo.sabate)
 *
 * Created on 24/04/2020
 */

//includes
#include "TTimer.h"
#include "TDoorPWM.h"
#include "TEUSART.h"

// Configuration Bits


//Main Config
void setup(){
  //inits
  initTimer();
  initTDoorPWM();
}


//Main Loop
void loop(){
    while(1){
        //motors
        motorTDoorPWM();
    }
}
