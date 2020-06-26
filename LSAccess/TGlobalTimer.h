//---------------------------------------------------------
// @File: TGlobalTimer*
// @Purpose:
// @Author: guillermo.sabate
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TGLOBALTIMER_H_
#define	_TGLOBALTIMER_H_

#define ONEMINUTE 60000
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

void GlSetTime(char hour, char min);
//Pre: --
//Post: Sets global time to given values

char GlGetHour(void);
//Pre: --
//Post: Returns global hour.

char GlGetMin(void);
//Pre: --
//Post: Return global mins.

#ifdef __cplusplus
} // extern "C"
#endif

#endif	/* TGLOBALTIMER_H */
