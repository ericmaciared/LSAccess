//---------------------------------------------------------
// @File: TGlobalTimer*
// @Purpose:
// @Author: guillermo.sabate
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TGlobalTimer.h"

//------------------------ VARIABLES ----------------------

static char timer;
static char hour;
static char mins;
static char state;
static char counterMins;

//------------------------ FUNCTIONS ----------------------

void initTGlobalTimer(void) {
  state = 0;
  hour = 0;
  mins = 0;
  counterMins = 0;
  timer = TiGetTimer();
}

void motorTGlobalTimer(void) {
  switch (state) {
    case 0:
      if (TiGetTics(timer) >= ONEMINUTE) {
        TiResetTics(timer);
        mins++;
        counterMins++;
        state = 1;
      }
      break;
    case 1:
      if (mins >= ONEHOUR) state = 2;
      else state = 0;
      break;
    case 2:
      mins = 0;
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

char GlCountMins(void) {
  return counterMins;
}

void GlCountMinus(void) {
  counterMins--;
}

char GlGetHour(void) {
  return hour;
}

char GlGetMin(void) {
  return mins;
}

void GlSetTime(char hour_in1, char hour_in2, char min_in1, char min_in2) {
  hour = (hour_in1 - '0') * 10 + hour_in2 - '0';
  mins = (min_in1 - '0') * 10 + min_in2 - '0';
}
