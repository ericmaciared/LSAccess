/*//---------------------------------------------------------
// @File: TEUSART
// @Purpose:
// @Author: ericm
// @Data: 04/05/2020
//---------------------------------------------------------

#ifndef _TEUSART_H_
#define _TEUSART_H_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------ INCLUDES -----------------------

#include "arduino.h"

//------------------------ FUNCTIONS ----------------------

void initTEUSART(void);
//Pre: --
//Post: Initializes EUSART module

void motorTEUSART(void);

char SioIsAvailable(void);
//Pre: EUSART is initialized
//Post: Returns 1 if channel is available to sends




#ifdef __cplusplus
} // extern "C"
#endif

#endif*/
