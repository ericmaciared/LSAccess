//---------------------------------------------------------
// @File: TEUSART*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TEUSART.h"

//------------------------ VARIABLES ----------------------

static char* bufferTX[BUFFER_TX_SIZE];
static unsigned char initTX, endTX;
static unsigned char howManyTX;

//------------------------ FUNCTIONS ----------------------

void initTEUSART(void){
  Serial.begin(9600, SERIAL_8N1); //Initializes pins for Serial transmission
  //in channel 0 (default)
  //TX: PIN 1
  //RX: PIN 0
  howManyTX = 0;
  initTX = 0;
  endTX = 0;  
}

void motorTEUSART(void){
  static char state = 0;
  static char *temporal;

  switch(state){
        case 0:
            if (howManyTX > 0){
                state = 1;
            }
            break;
        case 1:
            temporal = SioGetTX();
            state = 2;
            break;
        case 2:
            if (*temporal)
                state = 3;
            else
                state = 0;
            break;
        case 3:
            if (Serial.availableForWrite()){
                Serial.write(*temporal++);
                state=2;
            }
            break;
    }
}

int SioCharAvailable(void){
  return Serial.available();
}

char SioGetChar(void){
  return Serial.read();
}

void SioSendChar(char c){
  Serial.write(c);
}

void SioPutsCooperative(char *s){
  bufferTX[initTX++] = s;
	if (initTX == BUFFER_TX_SIZE) initTX = 0;
	howManyTX++;
}

static char* SioGetTX(void) {
	char *tmp;
	tmp = bufferTX[endTX++];
	if (endTX == BUFFER_TX_SIZE) endTX = 0;
	howManyTX --;
	return tmp;
}
