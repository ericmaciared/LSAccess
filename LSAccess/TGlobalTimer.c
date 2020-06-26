//---------------------------------------------------------
// @File: TGlobalTimer*
// @Purpose:
// @Author: guillermo.sabate
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TTimer.h"
#include "TGlobalTimer.h"

//------------------------ VARIABLES ----------------------

static char timer;
static char hour;
static char min;
static char state;

//------------------------ FUNCTIONS ----------------------

void initTGlobalTimer(void) {
	state = 0;
  hour = 0;
  min = 0;
  timer = TiGetTimer();
}

void motorTGlobalTimer(void){
	switch(state){
    case 0:
      if (TiGetTics(timer) >= T_MIN) state = 1;
			break;
    case 1:
      TiResetTics(timer);
      min++;
      if (min >= ONEHOUR) state = 2;
      else state = 0;
      break;
    case 2:
      min = 0;
      hour++;
      if (hour >= ONEDAY) state = 3;
      else state = 0;
      break;
    case 3:
      hour = 0;
      state = 0;
      break;
	}
}

char GlGetHour(void){
	return hour;
}

char GlGetMin(void){
	return min;
}

void GlSetTime(char hour_in, char min_in){
	hour = hour_in;
	min = min_in;
}

/*
char * getTime(void){
  char * time;
  unsigned char hour_minute[2];
  time[0] = hour;
  time[1] = min;
  time[2] = '/0';
  time = &hour_minute;
  return time;
}
*/
