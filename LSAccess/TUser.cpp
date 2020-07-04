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

  users[0].status = OUT;

  i = 0;
}

User* UsGetUser(void) {
//  User* aux = &users[i++];
//  if (i == MAX_USERS) i = 0;
//  return aux;
return &users[0];
}
