//---------------------------------------------------------
// @File: TInput*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TINPUT_H_
#define _TINPUT_H_

#define IDLE 1

#define T_PRESS 500  //500 mS
#define T_IDLE 3000 //3 S
#define T_RESET 5000 //5 S

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TTimer.h"
#include "TKeyboard.h"
#include "TEUSART.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initTInput(void);
//Pre: timer ADT has been initialized.
//Post: initializes TInput ADT

void motorTInput(void);

unsigned char InItoa(char key);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
