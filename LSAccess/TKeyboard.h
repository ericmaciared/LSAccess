//---------------------------------------------------------
// @File: TKeyboard*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TKEYBOARD_H_
#define _TKEYBOARD_H_

#define COL0 1
#define COL1 2
#define COL2 3
#define ROW0 4
#define ROW1 5
#define ROW2 6
#define ROW3 7

#define T_PRESS 5000 //0.5 S

//------------------------ INCLUDES -----------------------

#include "TTimer.h"
#include "arduino.h"

//------------------------ FUNCTIONS ----------------------

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

#endif
