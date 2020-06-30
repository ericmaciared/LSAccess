//---------------------------------------------------------
// @File: TAuthentication*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TAuthentication.h"

//------------------------ VARIABLES ----------------------

static char usersInside;
static unsigned char usersRegistered;
static int doorOpened;
static int accessDenied;
static char process;
static char state;
static char index;
static char uid[20];

//------------------------ FUNCTIONS ----------------------

void initTAuthentication(void) {
  usersInside = 0;
  usersRegistered = 1;
  doorOpened = 0;
  accessDenied = 0;
  process = IDLE_PROCESS;
  state = 0;
  index = 0;
}

void AuMainMenu(void) {
  SioPutsCooperative("\n---------------\n");
  SioPutsCooperative("Main Menu:\n");
  SioPutsCooperative("---------------\n");
  SioPutsCooperative("Choose an option:\n\n");
  SioPutsCooperative("\t1. Register new user\n");
  SioPutsCooperative("\t2. Eliminate user\n");
  SioPutsCooperative("\t3. Modify system time\n");
  SioPutsCooperative("\t4. Show statistics\n\n");
  SioPutsCooperative("Option:\n");
}


void motorTAuthentication(void) {

  switch (state) {
    case 0:
      AuMainMenu();
      state = 1;
      break;
    case 1:
      if (process == IDLE_PROCESS) {
        //SioPutsCooperative("LCD\n");
      }
      else if (process == LOGIN) {
        SioPutsCooperative("LOGIN\n");
        process = IDLE_PROCESS;
        SioPutsCooperative("Introduce UID: ");
        state = 2;
      }
      else if (process == RFID) {
        SioPutsCooperative("RFID\n");
        process = IDLE_PROCESS;
      }
      else if (process == REGISTER) {
        SioPutsCooperative("REGISTER\n");
        process = IDLE_PROCESS;
        state = 0;
      }
      else if (process == CHANGE_TIME) {
        SioPutsCooperative("CHANGE_TIME\n");
        process = IDLE_PROCESS;
        state = 0;
      }
      else if (process == STATISTICS) {
        SioPutsCooperative("STATISTICS\n");
        process = IDLE_PROCESS;
        state = 0;
      }
      break;
    case 2:

      break;
  }
}

void AuAuthenticate(unsigned char* uid) {

}

void AuIdle(void) {
  process = IDLE_PROCESS;
  state = 0;
}

void AuLogin(void) {
  process = LOGIN;
}

void AuRegister(void) {
  process = REGISTER;
}

void AuDelete(void) {
}

void AuRFID(void) {
  process = RFID;
}

void AuChangeTime(void) {
  process = CHANGE_TIME;
}

void AuStatistics(void) {
  process = STATISTICS;
}

void AuReset(void) {
  initTUser();
  initTGlobalTimer();
  initTAuthentication();
}

void AuAddChar(char input) {
  uid[index++] = input;
}

void AuSwitchChar(char input) {
  uid[--index] = input;
}

char AuState(void) {
  return process;
}
