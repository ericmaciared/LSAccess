//---------------------------------------------------------
// @File: TAuthentication*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TAUTHENTICATION_H_
#define _TAUTHENTICATION_H_

#define IDLE_PROCESS 1
#define LOGIN 2
#define RFID 3
#define REGISTER 4
#define CHANGE_TIME 5
#define STATISTICS 6

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TUser.h"
#include "TInput.h"
#include "TGlobalTimer.h"
#include "TSpeaker.h"
#include "TDoor.h"
#include "TEUSART.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initTAuthentication(void);
//Pre: --
//Post: --

void motorTAuthentication(void);

void AuAuthenticate(unsigned char* uid);
//Pre: --
//Post: Authenticates user with UID.

void AuIdle(void);
//Pre: --
//Post: The system moves to an idle state.

void AuLogin(void);
//Pre: --
//Post: Sets process state to Login.

void AuRFID(void);
//Pre: --
//Post: Sets process state to RFID login.

void AuRegister(void);
//Pre: --
//Post: Sets process state to Register.

void AuDelete(void);
//Pre: --
//Post: Deletes user with follwoing uid.

void AuChangeTime(void);
//Pre: --
//Post: Sets process state to Change Time

void AuStatistics(void);
//Pre: --
//Post: Starts sending statistics process.

void AuReset(void);
//Pre: --
//Post: The system resets.

void AuAddChar(char input);
//Pre: --
//Post: Sends received char to Authentication module.

void AuSwitchChar(char input);
//Pre: --
//Post: Switches previous char with new char.

char AuState(void);
//Pre: --
//Post: 1 if state is idle.


#ifdef __cplusplus
} // extern "C"
#endif

#endif*/
