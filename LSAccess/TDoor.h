//---------------------------------------------------------
// @File: TDoor*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TDOOR_H_
#define _TDOOR_H_

#define DOOR 22      //Door OUTPUT PIN

#define TIME_PWM 20 //20 mS
#define T_HIGH 13   //13.5 mS
#define T_OPEN 3000 //3 S

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TTimer.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initTDoor(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets the PWM to the minimum DC.

void motorTDoor(void);

void DoOpenDoor(void);
//Pre: --
//Post: Opens door for 3 seconds.

#ifdef __cplusplus
} // extern "C"
#endif

#endif
