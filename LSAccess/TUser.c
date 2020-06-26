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
    users[i].status = -1;
  }

  //General Director Declaration
  users[0].name[0] = 'M';
  users[0].name[1] = 'a';
  /*users[0].uid = {0xCA, 0xFE, 0x69, 0xCA, 0xFE};
  users[0].minStay = 0;
  users[0].minInside = 0;
  users[0].maxTime = {23, 59};
  users[0].minTime = {0, 0};
  users[0].status = 0;*/

  i = 0;
}

User* UsGetUser(void) {

  User* aux = &users[i++];
  if (i == MAX_USERS) i = 0;
  return aux;
}
