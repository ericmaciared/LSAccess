//---------------------------------------------------------
// @File: TGlobalTimer*
// @Purpose:
// @Author: guillermo.sabate
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TGLOBALTIMER_H_
#define	_TGLOBALTIMER_H_

#define T_MIN 60000
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

char * getTime(void);
//Pre: initTGlobalTimer.
//Post: Returns pointer to the time array with hour and minute

void initTGlobalTimer(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets initial variables.

#ifdef __cplusplus
} // extern "C"
#endif

#endif	/* TGLOBALTIMER_H */
