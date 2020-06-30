//
//#include "TTimer.h"
//#include "LcTLCD.h"
//#include "TLCD.h"
//#include "Arduino.h"
//#define END_OF_MSG '\n'
//#define SIZE_INPUT_MSG 7
//static char stateLCD;
//static unsigned char timerLCD, displayed, left_to_display;
//static char row_num, new_msg, mode, curr_char, finished;
//static char *rcvd_msg = NULL;
//
//void displayMsg(char msg[]) {
//  rcvd_msg = msg;
//  Serial.println(rcvd_msg);
//  new_msg = 1;
//  //row_num = 1;
//}
//
//void initMotorLCD(void) {
//  timerLCD = TiGetTimer();
//  LcClear();
//  LcGotoXY(0, 0);
//  displayed = left_to_display = 0;
//  row_num = 0;
//  new_msg = 0;
//  mode = DISPLAY_MSG;
//  stateLCD = curr_char = finished = 0;
//  LcCursorOff();
//}
//
//void MotorLCD () {
//  switch (stateLCD) {
//    case 0:
//      if (mode == DISPLAY_MSG) {
//        stateLCD = 1;
//      }
//      else if (mode == DISPLAY_INPUT) {
//        LcPutChar(pgm_read_word_near(INPUT_MSG_ + displayed));
//        ++displayed;
//        stateLCD = 5;
//      }
//      break;
//    case 1:
//      if (new_msg) {
//        LcGotoXY(0, row_num - 1);
//        new_msg = 0;
//        stateLCD = 2;
//      }
//      break;
//    case 5:
//      if (displayed + 1 > SIZE_INPUT_MSG) {
//        displayed = 0;
//        stateLCD = 6;
//      }
//      else if (displayed + 1 <= SIZE_INPUT_MSG) {
//        LcPutChar(pgm_read_word_near(INPUT_MSG_ + displayed));
//        ++displayed;
//      }
//      break;
//    case 2:
//      if (*rcvd_msg != END_OF_MSG && displayed <= 16) {
//        LcPutChar(*rcvd_msg);
//        ++rcvd_msg;
//        ++displayed;
//      }
//      else if (displayed > 16) {
//        TiResetTics(timerLCD);
//        stateLCD = 3;
//      }
//      else if (*rcvd_msg == END_OF_MSG) {
//        TiResetTics(timerLCD);
//        stateLCD = 4;
//      }
//      else if (new_msg == 1) {
//        stateLCD = 1;
//      }
//      else if (mode != DISPLAY_MSG) {
//        stateLCD = 0;
//      }
//      break;
//    case 3:
//      if (TiGetTics(timerLCD) > MOVE_TIME) {
//        LcGotoXY(0, row_num - 1);
//        rcvd_msg -= (displayed - 1);
//        left_to_display++;
//        displayed = 0;
//        stateLCD = 2;
//      }
//      break;
//    case 4:
//      if (TiGetTics(timerLCD) > FINISH_TIME) {
//        LcGotoXY(0, row_num - 1);
//        rcvd_msg -= (displayed + left_to_display);
//        displayed = 0;
//        left_to_display = 0;
//        stateLCD = 2;
//      }
//      break;
//    case 6:
//      if (mode != DISPLAY_INPUT) {
//        stateLCD = 0;
//      }
//      else if (mode == DISPLAY_INPUT && curr_char > 0) {
//        LcGotoXY(SIZE_INPUT_MSG + displayed, 0);
//        LcPutChar(curr_char);
//        displayed += finished;
//        finished = 0;
//        curr_char = 0;
//      }
//      break;
//  }
//}
//
//void setMode(char _mode) {
//  mode = _mode;
//}
//
//void setCharInput(char c) {
//  curr_char = c;
//}
//
//void setDisplayMsgMode(void) {
//  setMode(DISPLAY_MSG);
//}
//
//void setDisplayInputMode(void) {
//  setMode(DISPLAY_INPUT);
//}
//
//void finishInput(void) {
//  displayed++;
//  finished = 0;
//  curr_char = 0;
//  Serial.println("finished");
//}
