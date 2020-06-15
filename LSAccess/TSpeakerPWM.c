/*//---------------------------------------------------------
// @File: TTimer*
// @Purpose:
// @Author: eric.macia
//          guillermo.sabate
// @Data: 05/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------
#include "TDoorPWM.h"
#include <arduino.h>

//------------------------ DEFINES ------------------------
#define TIME_PWM 500

//------------------------ VARIABLES ----------------------
static char state;
static char timer;
static char period;

//------------------------ FUNCTIONS ----------------------

void initTSpeakerPWM(void) {
  SET_AUDIO_DIR; //Set SPEAKER pin as OUTPUT
  AUDIO_OFF; //Initialize SPEAKER to LOW
  state = 0;
  period = 1;
  timer = TiGetTimer();
}

char getAudioPeriod(void){
    return period;
}

void setAudioPeriod(char newPeriod){
    period= newPeriod;

}

char getAudioStatus(void){
    return state != 2;
}

void motorTSpeakerPWM(void){
	static char state = 0;
	switch(state){
		case 0:
			if (tHigh != 0) state = 1;
			break;
		case 1:
			if (TiGetTics(timer) >= tHigh){
        AUDIO_OFF;
				state = 2;
			}
			break;
    case 2:
      if (TiGetTics(timer) >= TIME_PWM) {
        TiResetTics(timer);
          AUDIO_ON;
      }
      break;
	}
}

char changeAudioStatus(){
    //Post: Changes the audio status.
    if (state == 2){
        //I am quiet, speak!
        state = 0;
    }else{
        //I am speaking, shut up!
        state = 2;
        AUDIO_OFF();
    }
    return state == 0;
}*/
