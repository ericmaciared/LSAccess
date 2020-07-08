//---------------------------------------------------------
// @File: TGlobalTimer*
// @Purpose:
// @Author: guillermo.sabate
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TGLOBALTIMER_H_
#define	_TGLOBALTIMER_H_

#define ONEMINUTE 6000 //60 S
#define ONEHOUR 60
#define ONEDAY 24
#define TRUE 1
#define FALSE 0

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TTimer.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void motorTGlobalTimer(void);

void initTGlobalTimer(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets initial variables.

char GlGetHour(void);
//Pre: --
//Post: Returns global hour.

char GlCountMins(void);
//Pre: --
//Post: Returns number of minutes passed since last update of users.

void GlCountMinus(void);
//Pre: counterMins > 0
//Post: counterMins--

char GlGetMin(void);
//Pre: --
//Post: Return global mins.

void GlSetTime(char hour_in1, char hour_in2, char min_in1, char min_in2);
//Pre: --
//Post: Sets global time to given values

#ifdef __cplusplus
} // extern "C"
#endif

#endif	/* TGLOBALTIMER_H */
