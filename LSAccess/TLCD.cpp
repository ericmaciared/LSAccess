//---------------------------------------------------------
// @File: TDoor*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TLCD.h"

//------------------------ VARIABLES ----------------------

static char state;
static unsigned char timer, displayed1, leftDisplay1, displayed2, leftDisplay2;
static char newMsg, mode, current, finished;
static char *rcMsg1 = NULL;
static char *rcMsg2 = NULL;

//------------------------ FUNCTIONS ----------------------

void initLCD(void) {
  timer = TiGetTimer();
  LcClear();
  LcGotoXY(0, 0);
  displayed1 = leftDisplay1 = displayed2 = leftDisplay2 = 0;
  newMsg = 0;
  mode = DISPLAY_MSG;
  state = current = finished = 0;
  LcCursorOff();
}

void LCDDisplay(char msg[], char row) {
  if (row == 1){
    rcMsg1 = msg;
    displayed1 = leftDisplay1 = 0;
  }
  if (row == 2){
    rcMsg2 = msg;
    displayed2 = leftDisplay2 = 0;
  }
  newMsg = 1;
}

void printFirst() {
  if (rcMsg1 == NULL) return;
  LcGotoXY(displayed1, 0);
  LcPutChar(*rcMsg1);
  ++rcMsg1;
  ++displayed1;
}

void printSecond(void) {
  if (rcMsg2 == NULL || *rcMsg2 == END_OF_MSG) return;
  LcGotoXY(displayed2, 1);
  LcPutChar(*rcMsg2);
  ++rcMsg2;
  ++displayed2;
}

void updateFirst(void) {
  rcMsg1 -= (displayed1 - 1);
  leftDisplay1++;
  displayed1 = 0;
}

void updateSecond(void) {
  rcMsg2 -= (displayed2 - 1);
  leftDisplay2++;
  displayed2 = 0;
}

void updateRows(void) {
  if (displayed1 > 16) updateFirst();
  if (displayed2 > 16) updateSecond();
}

void resetFirst(void) {
  rcMsg1 -= (displayed1 + leftDisplay1);
  displayed1 = 0;
  leftDisplay1 = 0;
}

void resetSecond(void) {
  rcMsg2 -= (displayed2 + leftDisplay2);
  displayed2 = 0;
  leftDisplay2 = 0;
}

void resetRows(void) {
  if (*rcMsg1 == END_OF_MSG){
    resetFirst();
  }
  if (*rcMsg2 == END_OF_MSG) resetSecond();
}

char ableToPrint() {
  return (*rcMsg1 != END_OF_MSG && displayed1 <= 16) ;//|| (*rcMsg2 != END_OF_MSG && displayed2 <= 16);
}

void setMode(char _mode) {
  mode = _mode;
}

void setCharInput(char c) {
  current = c;
}

void setDisplayMsgMode(void) {
  setMode(DISPLAY_MSG);
}

void setDisplayInputMode(void) {
  setMode(DISPLAY_INPUT);
}

void finishInput(void) {
  displayed1++;
  finished = 0;
  current = 0;
}

void motorLCD () {
  switch (state) {
    case 0:
      if (mode == DISPLAY_MSG) {
        state = 1;
      }
      else if (mode == DISPLAY_INPUT) {
        LcPutChar(pgm_read_word_near(INPUT_MSG_ + displayed1));
        ++displayed1;
        state = 5;
      }
      break;
    case 1:
      if (newMsg) {
        LcClear();
        newMsg = 0;
        state = 2;
      }
      break;
    case 5:
      if (displayed1 + 1 > SIZE_INPUT_MSG) {
        displayed1 = 0;
        state = 6;
      }
      else if (displayed1 + 1 <= SIZE_INPUT_MSG) {
        LcPutChar(pgm_read_word_near(INPUT_MSG_ + displayed1));
        ++displayed1;
      }
      break;
    case 2:
      if (newMsg == 1) {
        resetFirst();
        resetSecond();
        state = 1;
      }
      else if (mode != DISPLAY_MSG) {
        state = 0;
      }
      else if (ableToPrint()) {
        printFirst();
        printSecond();
      }
      else if (displayed1 > 16) {
        TiResetTics(timer);
        state = 3;
      }
      else if (*rcMsg1 == END_OF_MSG) {
        TiResetTics(timer);
        state = 4;
      }
      break;
    case 3:
      if (TiGetTics(timer) > MOVE_TIME) {
        updateRows();
        //resetRows();
        state = 2;
      }
      break;
    case 4:
      if (TiGetTics(timer) > FINISH_TIME) {
        resetRows();
        state = 2;
      }
      break;
    case 6:
      if (mode != DISPLAY_INPUT) {
        state = 0;
      }
      else if (mode == DISPLAY_INPUT && current > 0) {
        LcGotoXY(SIZE_INPUT_MSG + displayed1, 0);
        LcPutChar(current);
        displayed1 += finished;
        finished = 0;
        current = 0;
      }
      break;
  }
}
