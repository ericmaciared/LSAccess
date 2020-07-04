//---------------------------------------------------------
// @File: TAuthentication*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TAuthentication.h"

//------------------------ VARIABLES ----------------------

static User* user;
static unsigned char usersInside;
static unsigned char usersRegistered;
static unsigned char counter;
static int doorOpened;
static int accessDenied;
static char process;
static char state;
static char index;
static char finish;
unsigned char sendUsersRegistered[4], sendUsersInside[4], sendCounter[4], sendHour[3], sendMin[3], sendMinInside[6],
         sendMinStay[6], sendDoorOpened[6], sendAccessDenied[6], sendMax1[3], sendMax2[3], sendMin1[3], sendMin2[3],
         sendUid1[3], sendUid2[3], sendUid3[3], sendUid4[3], sendUid5[3];
static unsigned char initBuffer;
static unsigned char endBuffer;
static unsigned char howManyBuffer;
static char* buffer[BUFFER_SIZE];

//------------------------ FUNCTIONS ----------------------

void initTAuthentication(void) {
  usersInside = 0;
  usersRegistered = 1;
  counter = 0;
  doorOpened = 0;
  accessDenied = 0;
  process = PROCESS_IDLE;
  state = 0;
  index = 0;
  finish = 0;
  initBuffer = 0;
  endBuffer = 0;
  howManyBuffer = 0;
}

void AuMainMenu(void) {
  SioPutsCooperative("\n\r---------------\n\r");
  SioPutsCooperative("Main Menu:\n\r");
  SioPutsCooperative("---------------\n\r");
  SioPutsCooperative("Choose an option:\n\r\n\r");
  SioPutsCooperative("\t1. Register new user\n\r");
  SioPutsCooperative("\t2. Eliminate user\n\r");
  SioPutsCooperative("\t3. Modify system time\n\r");
  SioPutsCooperative("\t4. Show statistics\n\r\n\r");
  SioPutsCooperative("Option:\n\r");
}

void myItoa(int number, char* out) {
  int it = 0, temp = 10000, valid = 0;

  while (temp > 1) {
    out[it] = number % temp / (temp / 10);
    valid += (out[it] != 0);
    out[it] += '0';
    it = (out[it] != 0 && valid) ? ++it : it;
    temp /=  10;
  }
  if (number == 0) out[it + 1] = '\0';
  else out[it] = '\0';
}

void hexToAscii(char hex, char* out) {
  static char a = 0;
  static char b = 0;
  a = ((hex & 0xf0) >> 4);
  b = (hex & 0x0f);

  out[0] = a + ( (a > 9) ? 55 : '0' );
  out[1] = b + ( (b > 9) ? 55 : '0' );
  out[2] = '\0';
}

void AuShowRFID(void) {
  hexToAscii(user->uid[0], sendUid1);
  SioPutsCooperative(sendUid1);
  SioPutsCooperative("-");
  hexToAscii(user->uid[1], sendUid2);
  SioPutsCooperative(sendUid2);
  SioPutsCooperative("-");
  hexToAscii(user->uid[2], sendUid3);
  SioPutsCooperative(sendUid3);
  SioPutsCooperative("-");
  hexToAscii(user->uid[3], sendUid4);
  SioPutsCooperative(sendUid4);
  SioPutsCooperative("-");
  hexToAscii(user->uid[4], sendUid5);
  SioPutsCooperative(sendUid5);
}

void motorTAuthentication(void) {

  switch (state) {
    case 0:
      AuMainMenu();
      state = 1;
      break;
    case 1:
      if (process == PROCESS_IDLE) {
        //SioPutsCooperative("LCD\n\r");
      }
      else if (process == PROCESS_LOGIN) {
        //To LCD
        SioPutsCooperative("Introduce UID: ");
        finish = initBuffer = endBuffer = 0;
        state = 2;
      }
      else if (process == PROCESS_RFID) {
        SioPutsCooperative("Introduce UID: ");
        process = PROCESS_IDLE;
      }
      else if (process == PROCESS_REGISTER_K) {
        SioPutsCooperative("Introduce UID: ");
        process = PROCESS_IDLE;
        state = 0;
      }
      else if (process == PROCESS_TIME) {
        SioPutsCooperative("Introduce time: ");
        initBuffer = 0;
        endBuffer = 0;
        finish = 0;
        howManyBuffer = 0;
        state = 6;
      }
      else if (process == PROCESS_STATISTICS) {
        SioPutsCooperative("Statistics Panel:\n\r\n\r");
        SioPutsCooperative("\tUsers inside IoTiCAT: ");
        myItoa(usersInside, sendUsersInside);
        SioPutsCooperative(sendUsersInside);
        SioPutsCooperative("\n\r");
        counter = 0;
        user = UsGetUser();
        state = 4;
      }
      break;
    case 2:
      if (finish == 1 && howManyBuffer == 10) state = 3;
      break;
    case 3:
      break;
    case 4:
      if (counter == usersInside) {
        SioPutsCooperative("\tUsers registered in the system: ");
        myItoa(usersRegistered, sendUsersRegistered);
        SioPutsCooperative(sendUsersRegistered);
        SioPutsCooperative("\n\r");
        user = UsGetUser();
        state = 5;
        counter = 0;
      }
      else if (user->status != 1) {
        user = UsGetUser();
      }
      else if (user->status == 1) {
        SioPutsCooperative("\t");
        myItoa(++counter, sendCounter);
        SioPutsCooperative(sendCounter);
        SioPutsCooperative(". ");
        AuShowRFID();
        SioPutsCooperative(" - ");
        SioPutsCooperative(user->name);
        SioPutsCooperative(" - ");
        myItoa(user->minInside, sendMinInside);
        SioPutsCooperative(sendMinInside);
        SioPutsCooperative("\n\r");
      }
      break;
    case 5:
      if (counter >= usersRegistered) {
        SioPutsCooperative("\tUsers that have been denied access: ");
        myItoa(accessDenied, sendAccessDenied);
        SioPutsCooperative(sendAccessDenied);
        SioPutsCooperative("\n\r");
        SioPutsCooperative("\tNumber of times that the door has been opened: ");
        myItoa(doorOpened, sendDoorOpened);
        SioPutsCooperative(sendDoorOpened);
        SioPutsCooperative("\n\r");
        SioPutsCooperative("\tSystem Time: ");
        myItoa(GlGetHour(), sendHour);
        SioPutsCooperative(sendHour);
        SioPutsCooperative(":");
        myItoa(GlGetMin(), sendMin);
        SioPutsCooperative(sendMin);
        SioPutsCooperative("\n\r");
        state = 0;
        process = PROCESS_IDLE;
      }
      else if (user->status != -1) {
        SioPutsCooperative("\t");
        myItoa(++counter, sendCounter);
        SioPutsCooperative(sendCounter);
        SioPutsCooperative(". ");
        AuShowRFID();
        SioPutsCooperative(" - ");
        SioPutsCooperative(user->name);
        SioPutsCooperative(" - ");
        myItoa(user->minTime[0], sendMin1);
        SioPutsCooperative(sendMin1);
        SioPutsCooperative(":");
        myItoa(user->minTime[1], sendMin2);
        SioPutsCooperative(sendMin2);
        SioPutsCooperative(" - ");
        myItoa(user->maxTime[0], sendMax1);
        SioPutsCooperative(sendMax1);
        SioPutsCooperative(":");
        myItoa(user->maxTime[1], sendMax2);
        SioPutsCooperative(sendMax2);
        SioPutsCooperative(" - ");
        myItoa(user->minStay, sendMinStay);
        SioPutsCooperative(sendMinStay);
        SioPutsCooperative("\n\r");
        user = UsGetUser();
      }
      else user = UsGetUser();
      break;
    case 6:
      if (howManyBuffer == 4) {
        GlSetTime(buffer[endBuffer], buffer[endBuffer + 1],
                  buffer[endBuffer + 2], buffer[endBuffer + 3]);
        SioPutsCooperative("System time set to ");
        myItoa(GlGetHour(), sendHour);
        SioPutsCooperative(sendHour);
        SioPutsCooperative(":");
        myItoa(GlGetMin(), sendMin);
        SioPutsCooperative(sendMin);
        SioPutsCooperative("\n\r");
        state = 0;
        process = PROCESS_IDLE;
      }
      break;
  }
}

void AuIdle(void) {
  process = PROCESS_IDLE;
  state = 0;
}

void AuLogin(void) {
  process = PROCESS_LOGIN;
}

void AuRegisterK(void) {
  process = PROCESS_REGISTER_K;
}

void AuRegisterC(void) {
  process = PROCESS_REGISTER_C;
}

void AuDelete(void) {
  process = PROCESS_DELETE;
}

void AuChangeTime(void) {
  process = PROCESS_TIME;
}

void AuStatistics(void) {
  process = PROCESS_STATISTICS;
}

void AuRFID(void) {
  process = PROCESS_RFID;
}

void AuReset(void) {
  initTUser();
  initTGlobalTimer();
  initTAuthentication();
}

void AuAddChar(char *input) {
  buffer[initBuffer++] = input;
  if (initBuffer == BUFFER_SIZE) initBuffer = 0;
  howManyBuffer++;
}

void AuSwitchChar(char *input) {
  if (initBuffer == 0) buffer[BUFFER_SIZE] = input;
  else buffer[initBuffer - 1] = input;
}

void AuFinishChar(void) {
  finish = 1;
}

char AuState(void) {
  return process == PROCESS_IDLE;
}
