//---------------------------------------------------------
// @File: TDoor*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TDOOR_H_
#define _TDOOR_H_

#define DOOR 22      //Door OUTPUT PIN

#define TIME_PWM 200 //20 mS
#define T_HIGH 135   //13.5 mS
#define T_OPEN 30000 //3 S

//------------------------ INCLUDES -----------------------

#include "TTimer.h"
#include "arduino.h"

//------------------------ FUNCTIONS ----------------------

void initTDoor(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets the PWM to the minimum DC.

void motorTDoor(void);

void DoOpenDoor(void);
//Pre: --
//Post: Opens door for 3 seconds.

#endif
