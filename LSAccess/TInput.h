//---------------------------------------------------------
// @File: TInput*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TINPUT_H_
#define _TINPUT_H_

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TTimer.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initTInput(void);
//Pre: timer ADT has been initialized.
//Post: initializes TInput ADT

void motorTInput(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
