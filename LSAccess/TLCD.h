//---------------------------------------------------------
// @File: TLCD*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TLCD_H_
#define _TLCD_H_

#define MAX_LENGTH 30
#define DISPLAY_MSG 0
#define DISPLAY_INPUT 1
#define MOVE_TIME 450
#define FINISH_TIME 1500

#define END_OF_MSG '\n'
#define SIZE_INPUT_MSG 7

#define INPUT_MSG_ "INPUT: " // or this one

//------------------------ INCLUDES -----------------------

#include "TTimer.h"
#include "LcTLCD.h"
#include <Arduino.h>

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initLCD(void);
//Pre: --
//Post:

void motorLCD (void);
//Pre: --
//Post:

void LCDDisplay(char msg[], char row);
//Pre: --
//Post: Display message in selected row of the LCD

void displayInput(void);
//Pre: --
//Post:

void setCharInput(char c);
//Pre: --
//Post:

void finishInput();
//Pre: --
//Post:

void setDisplayMsgMode();
//Pre: --
//Post:

void setDisplayInputMode();
//Pre: --
//Post:

#ifdef __cplusplus
} // extern "C"
#endif

#endif
