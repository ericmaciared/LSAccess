//---------------------------------------------------------
// @File: TKeyboard*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TKEYBOARD_H_
#define _TKEYBOARD_H_

#define COL0 24
#define COL1 26
#define COL2 28
#define ROW0 30
#define ROW1 32
#define ROW2 34
#define ROW3 36

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
