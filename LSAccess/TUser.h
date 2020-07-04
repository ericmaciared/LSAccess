//---------------------------------------------------------
// @File: TUser*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TUSER_H_
#define _TUSER_H_

#define MAX_USERS 20
#define MAX_NAME_SIZE 10

#define IN 1
#define OUT 0
#define KILL -1

typedef struct{
  char name[MAX_NAME_SIZE];
  unsigned char uid[5];
  int minStay;
  int minInside;
  char maxTime[2];
  char minTime[2];
  char status;
}User;

//------------------------ INCLUDES -----------------------

#include <Arduino.h>

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
#endif

void initTUser(void);
//Pre: --
//Post: --

User* UsGetUser(void);
//Pre: --
//Post: return pointer to user.

#ifdef __cplusplus
} // extern "C"
#endif

#endif
