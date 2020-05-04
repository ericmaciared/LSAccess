//---------------------------------------------------------
// @File: TDoorPWM*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TDOORPWM_H_
#define _TDOORPWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DOOR 22

//------------------------ INCLUDES -----------------------

#include "TTimer.h"
#include "arduino.h"

//------------------------ FUNCTIONS ----------------------

void initTDoorPWM(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets the PWM to the minimum DC.

void motorTDoorPWM(void);

void DpSetTimeHigh(char value);
//Pre: 0<= value <= TIMEPWM
//Post: it sets a value to the DC of the PWM
//proportional to "value".

#ifdef __cplusplus
} // extern "C"
#endif

#endif
