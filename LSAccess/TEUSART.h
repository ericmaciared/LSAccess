//---------------------------------------------------------
// @File: TEUSART*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TEUSART_H_
#define _TEUSART_H_

#define BUFFER_RX_SIZE   64
#define BUFFER_TX_SIZE  128

//------------------------ INCLUDES -----------------------

#include <Arduino.h>

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif


void initTEUSART(void);
//Pre: timer ADT has been initialized.
//Post: initializes EUSART module baudrate

void motorTEUSART(void);

int SioCharAvailable(void);
// Pre: returns the number for characters that has not been chosen
// with the GetChar function

char SioGetChar(void);
// Pre: SiCharAvail() Is greater than 0
// Post: Extracts and returns the first characters at the reception queue.

void SioSendChar(char c);
// Post: Waits until the previous character has been sent and sends this one.

char SioTxReady(void);
// Pre: --
// Post: Returns 1 if nothing to send.

void SioPutsCooperative(char *s);
//Pre: The reference to the char *s is a const char or I can guaranty that
//     it won't be overwritten until it has been send.
//Post: Add *s at the queue of chains to send...

static char* SioGetTX(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
