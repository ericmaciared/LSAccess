//---------------------------------------------------------
// @File: TSpeaker*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TSPEAKER_H_
#define _TSPEAKER_H_

#define SPEAKER 23      //Speaker OUTPUT PIN

#define T_BEEP 1500 //150 mS
#define T_PWM 15 //1.5 mS    770Hz Frequency
#define T_HIGH 7  //0.7 mS

//------------------------ INCLUDES -----------------------

#include "TTimer.h"
#include "arduino.h"

//------------------------ FUNCTIONS ----------------------

void initTSpeaker(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets the PWM to the minimum DC.

void motorTSpeaker(void);

void SpAddBeeps(char numBeeps);
//Pre: --
//Post: Sets number of beeps to sound in speaker.

#endif