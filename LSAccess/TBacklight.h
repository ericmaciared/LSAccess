//---------------------------------------------------------
// @File: TBacklight.h
// @Purpose:
// @Author: eric.macia
//          guillermo.sabate
// @Data: 05/05/2020
//---------------------------------------------------------
#ifndef TBACKLIGTH_H
#define TBACKLIGTH_H

//------------------------ INCLUDES -----------------------
#include "TTimer.h"
#include <arduino.h>

//------------------------ DEFINES ------------------------
#define TIME_PWM 500
// Will have to set the pins
#define SET_BL_DIR()  digitalWrite(BACKLIGHT, LOW);
#define BL_OFF() digitalWrite(BACKLIGHT, LOW);
#define BL_ON() digitalWrite(BACKLIGHT, HIGH);

#define PERIODBL   20  //Period of the LED backlight


//------------------------ FUNCTIONS ----------------------
void initTBacklight();
//Post: Asks for a timer and initializes the backlight at 50%.

void motorTBacklight(void);

char getTBacklightDuty(void);
//Post: returns the duty value of the backlight (between 0 and 20).

void setTBacklightDuty(char);
//Pre: duty lies between 0 and 20




#endif	/* BLTBACKLIGHT_H */
