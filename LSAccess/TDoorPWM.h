//---------------------------------------------------------
// @File: TDoorPWM*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TDOORPWM_H_
#define _TDOORPWM_H_

#define LED 1
//#define LED_DIRECTION TRISAbits.TRISA3 // --> BSF / BCF SFR,BIT,0


//------------------------ INCLUDES -----------------------

#include "TTimer.h"

//------------------------ FUNCTIONS ----------------------

void initTPWM(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets the PWM to the minimum DC.

void motorPWM(void);

void setTimeHigh(char value);
//Pre: 0<= value <= TIMEPWM
//Post: it sets a value to the DC of the PWM
//proportional to "value".
#endif
