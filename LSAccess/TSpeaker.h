//---------------------------------------------------------
// @File: TSpeaker*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TSPEAKER_H_
#define _TSPEAKER_H_

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SPEAKER 23      //Speaker OUTPUT PIN

#define T_BEEP 250 //250 mS
#define T_PWM 2 //2 mS
#define T_HIGH 1  //1 mS

//------------------------ INCLUDES -----------------------

#include "TTimer.h"

//------------------------ FUNCTIONS ----------------------

void initTSpeaker(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets the PWM to the minimum DC.

void motorTSpeaker(void);

void SpAddBeeps(char numBeeps);
//Pre: --
//Post: Sets number of beeps to sound in speaker.

#ifdef __cplusplus
} // extern "C"
#endif

#endif
