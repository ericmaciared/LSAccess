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
unsigned char auxUid[5];
unsigned char message[30] = "00:00 - 000 people - Main Menu\0";
unsigned char sendUid[15] = "00-00-00-00-00\0";
static int i;
static unsigned char usersRegistered;
static unsigned char usersInside;
static unsigned char counter;
static int doorOpened;
static int accessDenied;
static char process;
static char state;
static char index;
static char finishChar, finish;
static unsigned char sendUsersRegistered[4], sendUsersInside[4], sendCounter[4], sendHour[3], sendMin[3], sendMinInside[6],
       sendMinStay[6], sendDoorOpened[6], sendAccessDenied[6], sendMax1[3], sendMax2[3], sendMin1[3], sendMin2[3],
       sendUid1[3], sendUid2[3], sendUid3[3], sendUid4[3], sendUid5[3];
static unsigned char initBuffer, endBuffer, howManyBuffer;
static char* buffer[BUFFER_SIZE];

//------------------------ FUNCTIONS ----------------------

void initTAuthentication(void) {
  usersInside = 2;
  usersRegistered = 3;
  counter = 0;
  doorOpened = 0;
  accessDenied = 0;
  process = PROCESS_IDLE;
  state = 0;
  index = 0;
  finishChar = finish = 0;
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
  int j = 0, temp = 10000, valid = 0;

  while (temp > 1) {
    out[j] = number % temp / (temp / 10);
    valid += (out[j] != 0);
    out[j] += '0';
    j = (out[j] != 0 && valid) ? ++j : j;
    temp /=  10;
  }
  if (number == 0) out[j + 1] = '\0';
  else out[j] = '\0';
}

void AuLCDMainMenu(void) {
  myItoa(GlGetHour(), sendHour);
  if (sendHour[1] == '\0') {
    message[0] = '0';
    message[1] = sendHour[0];
  }
  else {
    message[0] = sendHour[0];
    message[1] = sendHour[1];
  }

  myItoa(GlGetMin(), sendMin);
  if (sendMin[1] == '\0') {
    message[3] = '0';
    message[4] = sendMin[0];
  }
  else {
    message[3] = sendMin[0];
    message[4] = sendMin[1];
  }
  myItoa(usersInside, sendUsersInside);
  if (sendUsersInside[1] == '\0') {
    message[8] = '0';
    message[9] = '0';
    message[10] = sendMin[0];
  }
  else if (sendUsersInside[2] == '\0'){
    message[8] = '0';
    message[9] = sendMin[0];
    message[10] = sendMin[1];
  }
  else {
    message[8] = sendMin[0];
    message[9] = sendMin[1];
    message[10] = sendMin[2];
   }
  LCDDisplay(message, 1);
}

void hexToAscii(char hex, char* out) {
  char a = 0;
  char b = 0;
  a = ((hex & 0xf0) >> 4);
  b = (hex & 0x0f);

  out[0] = a + ( (a > 9) ? 55 : '0' );
  out[1] = b + ( (b > 9) ? 55 : '0' );
  out[2] = '\0';
}

char myAtoi(char num1, char num2) {
  char aux1 = num1 - '0';
  char aux2 = num2 - '0';

  return aux1 * 10 + aux2;
}

char asciiToHex(char left, char right) {
  unsigned char result = 0;
  unsigned char aux1 = (TO_HEX(left) << 4) & 0x00f0;
  unsigned char aux2 = (TO_HEX(right) & 0x0f);
  result = aux1 | aux2;

  return result;
}

void AuShowUID(void) {
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
      AuLCDMainMenu();
      AuMainMenu();
      state = 1;
      break;
    case 1:
      if (GlCountMins() > 0) {
        AuLCDMainMenu();
        state = 2;
        i = 0;
        user = UsGetUser();
      }
      else if (process == PROCESS_LOGIN) {
        //To LCD
        LCDDisplay("Introduce UID: \n\0", 1);
        SioPutsCooperative("Introduce UID: ");
        finish = initBuffer = endBuffer = howManyBuffer = 0;
        state = 10;
      }
      //TODO
      else if (process == PROCESS_RFID) {
        finish = initBuffer = endBuffer = howManyBuffer = 0;
        state = 10;
      }
      else if (process == PROCESS_DELETE) {
        LCDDisplay("Introduce UID: \n\0", 1);
        SioPutsCooperative("Introduce UID: ");
        finish = initBuffer = endBuffer = howManyBuffer = 0;
        state = 50;
      }
      //TODO
      else if (process == PROCESS_REGISTER_K) {
        LCDDisplay("Introduce UID: \n\0", 1);
        SioPutsCooperative("Introduce UID: ");
        state = 60;
      }
      else if (process == PROCESS_REGISTER_C) {
        finish = initBuffer = endBuffer = howManyBuffer = 0;
        user = UsGetUser();
        state = 40;
      }
      else if (process == PROCESS_TIME) {
        LCDDisplay("Introduce time: \n\0", 1);
        SioPutsCooperative("Introduce time: ");
        initBuffer = endBuffer = howManyBuffer = 0;
        state = 20;
      }
      else if (process == PROCESS_STATISTICS) {
        SioPutsCooperative("Statistics Panel:\n\r\n\r");
        SioPutsCooperative("\tUsers inside IoTiCAT: ");
        myItoa(usersInside, sendUsersInside);
        SioPutsCooperative(sendUsersInside);
        SioPutsCooperative("\n\r");
        counter = 0;
        user = UsGetUser();
        state = 30;
      }
      break;
    case 2:
      if (i == MAX_USERS) {
        GlCountMinus();
        i = 0;
        state = 1;
      }
      else if (user->status == 1) user->minInside++;
      i++;
      user = UsGetUser();
      break;

    //LOGIN
    case 10:
      if (howManyBuffer == 10 && finish == 1) {
        auxUid[0] = asciiToHex(buffer[endBuffer], buffer[endBuffer + 1]);
        auxUid[1] = asciiToHex(buffer[endBuffer + 2], buffer[endBuffer + 3]);
        auxUid[2] = asciiToHex(buffer[endBuffer + 4], buffer[endBuffer + 5]);
        auxUid[3] = asciiToHex(buffer[endBuffer + 6], buffer[endBuffer + 7]);
        auxUid[4] = asciiToHex(buffer[endBuffer + 8], buffer[endBuffer + 9]);
        SioPutsCooperative("\nUID: ");
        hexToAscii(auxUid[0], sendUid1);
        SioPutsCooperative(sendUid1);
        SioPutsCooperative("-");
        hexToAscii(auxUid[1], sendUid2);
        SioPutsCooperative(sendUid2);
        SioPutsCooperative("-");
        hexToAscii(auxUid[2], sendUid3);
        SioPutsCooperative(sendUid3);
        SioPutsCooperative("-");
        hexToAscii(auxUid[3], sendUid4);
        SioPutsCooperative(sendUid4);
        SioPutsCooperative("-");
        hexToAscii(auxUid[4], sendUid5);
        SioPutsCooperative(sendUid5);
        howManyBuffer = endBuffer = initBuffer = i = 0;
        user =  UsGetUser();
        state = 11;
      }
      break;
    case 11:
      if (counter == MAX_USERS) {
        accessDenied++;
        SpAddBeeps(5);
        howManyBuffer = endBuffer = initBuffer = 0;
        //TODO LCD
        LCDDisplay("Hello Random! \n\0", 1);
        SioPutsCooperative("\nHello Random!\n");
        hexToAscii(auxUid[0], sendUid1);
        SioPutsCooperative(sendUid1);
        SioPutsCooperative("-");
        hexToAscii(auxUid[1], sendUid2);
        SioPutsCooperative(sendUid2);
        SioPutsCooperative("-");
        hexToAscii(auxUid[2], sendUid3);
        SioPutsCooperative(sendUid3);
        SioPutsCooperative("-");
        hexToAscii(auxUid[3], sendUid4);
        SioPutsCooperative(sendUid4);
        SioPutsCooperative("-");
        hexToAscii(auxUid[4], sendUid5);
        SioPutsCooperative(sendUid5);
        process = PROCESS_IDLE;
        state = 0;
      }
      else if (user->uid[0] == auxUid[0] && user->uid[1] == auxUid[1] &&
               user->uid[2] == auxUid[2] && user->uid[3] == auxUid[3]
               && user->uid[4] == auxUid[4] && user->status != -1) {
        //LCD TODO
        //LCDPut(user->uid);
        SioPutsCooperative("\nHello ");
        SioPutsCooperative(user->name);
        SioPutsCooperative("!\n");
        hexToAscii(auxUid[0], sendUid1);
        SioPutsCooperative(sendUid1);
        SioPutsCooperative("-");
        hexToAscii(auxUid[1], sendUid2);
        SioPutsCooperative(sendUid2);
        SioPutsCooperative("-");
        hexToAscii(auxUid[2], sendUid3);
        SioPutsCooperative(sendUid3);
        SioPutsCooperative("-");
        hexToAscii(auxUid[3], sendUid4);
        SioPutsCooperative(sendUid4);
        SioPutsCooperative("-");
        hexToAscii(auxUid[4], sendUid5);
        SioPutsCooperative(sendUid5);
        state = 12;
      }
      else {
        user = UsGetUser();
        counter++;
      }
      break;

    case 12:
      //If user is INSIDE
      if (user -> status == IN) {
        if (user->minInside >= user->minStay) {
          user->status = OUT;
          user->minInside = 0;
          usersInside--;
          doorOpened++;
          DoOpenDoor();
          SpAddBeeps(1);
        }
        else {
          accessDenied++;
          SpAddBeeps(2);
        }
      }
      //If user is OUTSIDE
      else {
        //If GENERAL DIRECTOR
        if (user->uid[0] == 202 && user->uid[1] == 254 && user->uid[3] == 105 &&
            user->uid[0] == 202 && user->uid[0] == 254) {
          user->status = IN;
          user->minInside = 0;
          usersInside++;
          doorOpened++;
          DoOpenDoor();
          SpAddBeeps(1);
        }
        else if (GlGetHour() >= user->minTime[0] && GlGetHour() <= user->maxTime[0]
                 && GlGetMin() >= user->minTime[1] && GlGetMin() <= user->maxTime[1]) {
          if (usersInside >= 100) {
            accessDenied++;
            SpAddBeeps(4);
          }
          else {
            user->status = IN;
            user->minInside = 0;
            usersInside++;
            doorOpened++;
            DoOpenDoor();
            SpAddBeeps(1);
          }
        }
        else {
          accessDenied++;
          SpAddBeeps(2);
        }
      }
      process = PROCESS_IDLE;
      state = 0;
      break;

    //CHANGE TIME
    case 20:
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

    //STATISTICS
    case 30:
      if (counter >= usersInside && SioTxReady() == 1) {
        SioPutsCooperative("\tUsers registered in the system: ");
        myItoa(usersRegistered, sendUsersRegistered);
        SioPutsCooperative(sendUsersRegistered);
        SioPutsCooperative("\n\r");
        counter = 0;
        state = 31;
      }
      else if (user->status == 1 && SioTxReady() == 1) {
        SioPutsCooperative("\t");
        myItoa(++counter, sendCounter);
        SioPutsCooperative(sendCounter);
        SioPutsCooperative(". ");
        AuShowUID();
        SioPutsCooperative(" - ");
        SioPutsCooperative(user->name);
        SioPutsCooperative(" - ");
        myItoa(user->minInside, sendMinInside);
        SioPutsCooperative(sendMinInside);
        SioPutsCooperative("\n\r");
        user = UsGetUser();
      }
      else if (user->status != 1 && SioTxReady() == 1) user = UsGetUser();
      break;
    case 31:
      if (counter >= usersRegistered && SioTxReady() == 1) {
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
      else if (user->status != -1 && SioTxReady() == 1) {
        SioPutsCooperative("\t");
        myItoa(++counter, sendCounter);
        SioPutsCooperative(sendCounter);
        SioPutsCooperative(". ");
        AuShowUID();
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
      else if (user->status == -1 && SioTxReady() == 1) user = UsGetUser();
      break;

    //REGISTRATION COMPUTER
    case 40:
      if (user->status != -1) user = UsGetUser();
      else {
        SioPutsCooperative("Introduce name: ");
        finish = howManyBuffer = endBuffer = initBuffer = 0;
        state = 41;
      }
      break;
    case 41:
      if (finish == 1 && howManyBuffer >= 1 && SioCharAvailable() == 0) {
        for (i = 0; i < howManyBuffer; i++) {
          user->name[i] = buffer[endBuffer + i];
        }
        user->name[i] = '\0';
        i = 0;
        SioPutsCooperative("\nName set to: ");
        SioPutsCooperative(user->name);
        SioPutsCooperative("\n");
        SioPutsCooperative("Introduce UID: ");
        howManyBuffer = 0;
        endBuffer = 0;
        initBuffer = 0;
        state = 42;
      }
      break;
    case 42:
      if (howManyBuffer == 10) {
        user->uid[i++] = asciiToHex(buffer[endBuffer], buffer[endBuffer + 1]);
        user->uid[i++] = asciiToHex(buffer[endBuffer + 2], buffer[endBuffer + 3]);
        user->uid[i++] = asciiToHex(buffer[endBuffer + 4], buffer[endBuffer + 5]);
        user->uid[i++] = asciiToHex(buffer[endBuffer + 6], buffer[endBuffer + 7]);
        user->uid[i++] = asciiToHex(buffer[endBuffer + 8], buffer[endBuffer + 9]);
        SioPutsCooperative("\nUID set to: ");
        AuShowUID();
        SioPutsCooperative("\nInsert minimum entrance hour: ");
        howManyBuffer = 0;
        endBuffer = 0;
        initBuffer = 0;
        state = 43;
      }
      break;
    case 43:
      if (howManyBuffer == 4) {
        user->minTime[0] = myAtoi(buffer[endBuffer], buffer[endBuffer + 1]);
        user->minTime[1] = myAtoi(buffer[endBuffer + 2], buffer[endBuffer + 3]);
        SioPutsCooperative("\nMinimum entrance time set to: ");
        myItoa(user->minTime[0], sendMin1);
        SioPutsCooperative(sendMin1);
        SioPutsCooperative(":");
        myItoa(user->minTime[1], sendMin2);
        SioPutsCooperative(sendMin2);
        SioPutsCooperative("\nInsert maximum entrance hour: ");
        howManyBuffer = 0;
        endBuffer = 0;
        initBuffer = 0;
        state = 44;
      }
      break;
    case 44:
      if (howManyBuffer == 4) {
        user->maxTime[0] = myAtoi(buffer[endBuffer], buffer[endBuffer + 1]);
        user->maxTime[1] = myAtoi(buffer[endBuffer + 2], buffer[endBuffer + 3]);
        SioPutsCooperative("\nMaximum entrance time set to: ");
        myItoa(user->maxTime[0], sendMax1);
        SioPutsCooperative(sendMax1);
        SioPutsCooperative(":");
        myItoa(user->maxTime[1], sendMax2);
        SioPutsCooperative(sendMax2);
        SioPutsCooperative("\nInsert maximum stay: ");
        finish = 0;
        howManyBuffer = 0;
        endBuffer = 0;
        initBuffer = 0;
        state = 45;
      }
      break;
    case 45:
      if (finish == 1 && howManyBuffer >= 1 && SioCharAvailable() == 0) {
        user->minStay = 0;
        int multiplier = 1;
        int aux = 0;
        for (i = 0; i < howManyBuffer; i++) {
          aux = buffer[initBuffer - i - 1] - '0';
          user->minStay += aux * multiplier;
          multiplier *= 10;
        }
        SioPutsCooperative("\nMinimum stay time set to: ");
        myItoa(user->minStay, sendMinStay);
        SioPutsCooperative(sendMinStay);
        SioPutsCooperative("\nUser registered correctly!");
        user->minInside = 0;
        user->status = 0;
        usersRegistered += 1;
        howManyBuffer = 0;
        endBuffer = 0;
        initBuffer = 0;
        process = PROCESS_IDLE;
        state = 0;
      }
      break;

    //DELETE USER
    case 50:
      if (howManyBuffer == 10 && finish == 1) {
        auxUid[0] = asciiToHex(buffer[endBuffer], buffer[endBuffer + 1]);
        auxUid[1] = asciiToHex(buffer[endBuffer + 2], buffer[endBuffer + 3]);
        auxUid[2] = asciiToHex(buffer[endBuffer + 4], buffer[endBuffer + 5]);
        auxUid[3] = asciiToHex(buffer[endBuffer + 6], buffer[endBuffer + 7]);
        auxUid[4] = asciiToHex(buffer[endBuffer + 8], buffer[endBuffer + 9]);
        SioPutsCooperative("\nUID: ");
        hexToAscii(auxUid[0], sendUid1);
        SioPutsCooperative(sendUid1);
        SioPutsCooperative("-");
        hexToAscii(auxUid[1], sendUid2);
        SioPutsCooperative(sendUid2);
        SioPutsCooperative("-");
        hexToAscii(auxUid[2], sendUid3);
        SioPutsCooperative(sendUid3);
        SioPutsCooperative("-");
        hexToAscii(auxUid[3], sendUid4);
        SioPutsCooperative(sendUid4);
        SioPutsCooperative("-");
        hexToAscii(auxUid[4], sendUid5);
        SioPutsCooperative(sendUid5);
        howManyBuffer = endBuffer = initBuffer = i = 0;
        user =  UsGetUser();
        state = 51;
      }
      break;
    case 51:
      if (counter == MAX_USERS) {
        howManyBuffer = endBuffer = initBuffer = 0;
        //TODO LCD
        SioPutsCooperative("\nNo user found!\n");
        hexToAscii(auxUid[0], sendUid1);
        SioPutsCooperative(sendUid1);
        SioPutsCooperative("-");
        hexToAscii(auxUid[1], sendUid2);
        SioPutsCooperative(sendUid2);
        SioPutsCooperative("-");
        hexToAscii(auxUid[2], sendUid3);
        SioPutsCooperative(sendUid3);
        SioPutsCooperative("-");
        hexToAscii(auxUid[3], sendUid4);
        SioPutsCooperative(sendUid4);
        SioPutsCooperative("-");
        hexToAscii(auxUid[4], sendUid5);
        SioPutsCooperative(sendUid5);
        process = PROCESS_IDLE;
        state = 0;
      }
      else if (user->uid[0] == auxUid[0] && user->uid[1] == auxUid[1] &&
               user->uid[2] == auxUid[2] && user->uid[3] == auxUid[3]
               && user->uid[4] == auxUid[4] && user->status != -1) {
        user->status = -1;
        usersRegistered--;
        SioPutsCooperative("\nUser deleted!\n");
        process = PROCESS_IDLE;
        state = 0;
      }
      else {
        user = UsGetUser();
        counter++;
      }
      break;

    //REGISTER KEYBOARD
    case 60:
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
  SioPutsCooperative(input);
  if (initBuffer == BUFFER_SIZE) initBuffer = 0;
  howManyBuffer++;
}

void AuSwitchChar(char *input) {
  if (initBuffer == 0) buffer[BUFFER_SIZE] = input;
  else buffer[initBuffer - 1] = input;
}

void AuFinishChar(void) {
  finishChar = 1;
}

void AuFinishInput(void) {
  finish = 1;
}

char AuState(void) {
  return process == PROCESS_IDLE;
}
