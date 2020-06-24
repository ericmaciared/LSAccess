//---------------------------------------------------------
// @File: TKeyboard*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TKEYBOARD_H_
#define _TKEYBOARD_H_

#define COL1 24 // INPUT
#define ROW0 26 // OUTPUT
#define COL0 28 // INPUT 
#define ROW3 30 // OUTPUT
#define COL2 32 // INPUT
#define ROW2 34 // OUTPUT
#define ROW1 36 // OUTPUT

#define T_DEBOUNCE 20 //20 mS
#define TRUE 1
#define FALSE 0

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TTimer.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

char KeyCharAvailable(void);
//Pre: --
//Post: returns 1 if there are values available.

char KeyGetChar(void);
//Pre: KeyCharAvailable() == 1
//Post: Returns value pressed from keyboard.

void initTKeyboard(void);
//Pre: timer ADT has been initialized.
//Post: asks for a timer and sets initial variables.

void motorTKeyboard(void);

#ifdef __cplusplus
} //extern C
#endif

#endif
