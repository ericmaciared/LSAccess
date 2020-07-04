#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#define     MAX_LENGTH 30
#define DISPLAY_MSG 0
#define DISPLAY_INPUT 1
#define MOVE_TIME 450
#define FINISH_TIME 1500

#ifdef __cplusplus
extern "C" {
#endif
const PROGMEM char INPUT_MSG_[] = "INPUT: "; // or this one

void initMotorLCD(void);
void MotorLCD (void);
void displayMsg(char msg[]);
void displayInput(void);
void setCharInput(char c);
void finishInput();
void setDisplayMsgMode();
void setDisplayInputMode();

#ifdef __cplusplus
}
#endif
#endif //LCD_H
