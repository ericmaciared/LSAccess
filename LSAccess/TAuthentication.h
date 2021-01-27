//---------------------------------------------------------
// @File: TAuthentication*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TAUTHENTICATION_H_
#define _TAUTHENTICATION_H_

#define TO_HEX(ascii_value) ((ascii_value > 57)? (ascii_value-55):(ascii_value-48))

#define PROCESS_IDLE 1
#define PROCESS_LOGIN 2
#define PROCESS_REGISTER_K 3
#define PROCESS_REGISTER_C 4
#define PROCESS_DELETE 5
#define PROCESS_TIME 6
#define PROCESS_STATISTICS 7
#define PROCESS_RFID 8

#define BUFFER_SIZE 16

//------------------------ INCLUDES -----------------------

#include <Arduino.h>
#include "TUser.h"
#include "TInput.h"
#include "TGlobalTimer.h"
#include "TSpeaker.h"
#include "TDoor.h"
#include "TLCD.h"
#include "TEUSART.h"

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initTAuthentication(void);
//Pre: --
//Post: --

void motorTAuthentication(void);

void AuIdle(void);
//Pre: --
//Post: The system moves to an idle state.

void AuLogin(void);
//Pre: --
//Post: Sets process state to Login.

void AuRegisterK(void);
//Pre: --
//Post: Sets process state to Register from Keyboard.

void AuRegisterC(void);
//Pre: --
//Post: Sets process state to Register from Computer.

void AuDelete(void);
//Pre: --
//Post: Sets process state to delete user;

void AuChangeTime(void);
//Pre: --
//Post: Sets process state to Change Time

void AuStatistics(void);
//Pre: --
//Post: Starts sending statistics process.

void AuRFID(void);
//Pre: --
//Post: Sets process state to RFID login.

void AuReset(void);
//Pre: --
//Post: The system resets.

void AuAddChar(char* input);
//Pre: --
//Post: Sends received char to Authentication module.

void AuSwitchChar(char* input);
//Pre: --
//Post: Switches previous char with new char.

void AuFinishChar(void);
//Pre: --
//Post: indicates last char sent is already fixed

void AuFinishInput(void);
//Pre: --
//Post: indicates last string sent is finished

char AuState(void);
//Pre: --
//Post: 1 if state is idle.


#ifdef __cplusplus
} // extern "C"
#endif

#endif*/
