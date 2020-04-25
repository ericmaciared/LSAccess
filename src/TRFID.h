//---------------------------------------------------------
// @File: TRFID
// @Purpose:
// @Author: ericm
// @Data: 25/04/2020
//---------------------------------------------------------

#ifndef _TRFID_H_
#define _TRFID_H_

#define SS_PIN 53
#define RST_PIN 49

//------------------------ INCLUDES -----------------------


//------------------------ FUNCTIONS ----------------------

void initTRFID(void);
//Pre: -
//Post: Initializes the RFID module.

void motorTRFID(void);
//Pre: RFID is initialized
//Post:

#endif
