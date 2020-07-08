//---------------------------------------------------------
// @File: TUser*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TUser.h"

//------------------------ VARIABLES ----------------------

static User users[MAX_USERS];
static unsigned char i;

//------------------------ FUNCTIONS ----------------------

void initTUser(void) {
  for (i = 0; i < MAX_USERS; i++) {
    users[i].minStay = 69;
    users[i].status = KILL;
  }

  //General Director Declaration
  users[0].uid[0] = 0xCA;
  users[0].uid[1] = 0xFE;
  users[0].uid[2] = 0x69;
  users[0].uid[3] = 0xCA;
  users[0].uid[4] = 0xFE;

  users[0].name[0] = 'M';
  users[0].name[1] = 'a';
  users[0].name[2] = 'x';
  users[0].name[3] = ' ';
  users[0].name[4] = 'B';
  users[0].name[5] = 'o';
  users[0].name[6] = 's';
  users[0].name[7] = 's';
  users[0].name[8] = '\0';

  users[0].minTime[0] = 0;
  users[0].minTime[1] = 0;
  users[0].maxTime[0] = 23;
  users[0].maxTime[1] = 59;
  users[0].minStay = 0;

  users[0].status = IN;

  users[10].uid[0] = 0xAC;
  users[10].uid[1] = 0xEF;
  users[10].uid[2] = 0x96;
  users[10].uid[3] = 0xAC;
  users[10].uid[4] = 0xEF;

  users[10].name[0] = 'T';
  users[10].name[1] = 'e';
  users[10].name[2] = 's';
  users[10].name[3] = 't';
  users[10].name[4] = 'i';
  users[10].name[5] = 'n';
  users[10].name[6] = 'g';
  users[10].name[7] = '\0';

  users[10].minTime[0] = 12;
  users[10].minTime[1] = 0;
  users[10].maxTime[0] = 12;
  users[10].maxTime[1] = 59;
  users[10].minStay = 100;

  users[10].status = IN;

  users[3].uid[0] = 0x12;
  users[3].uid[1] = 0x23;
  users[3].uid[2] = 0x34;
  users[3].uid[3] = 0x45;
  users[3].uid[4] = 0x56;

  users[3].name[0] = 'T';
  users[3].name[1] = 'e';
  users[3].name[2] = 't';
  users[3].name[3] = 'e';
  users[3].name[4] = 's';
  users[3].name[5] = 'i';
  users[3].name[6] = 'k';
  users[3].name[7] = 'o';
  users[3].name[8] = '\0';

  users[3].minTime[0] = 9;
  users[3].minTime[1] = 0;
  users[3].maxTime[0] = 17;
  users[3].maxTime[1] = 30;
  users[3].minStay = 350;

  users[3].status = OUT;


  i = 0;
}

User* UsGetUser(void) {
  User* aux = &users[i];
  if (i == MAX_USERS - 1) i = 0;
  else i++;
  return aux;
}
