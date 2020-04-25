//---------------------------------------------------------
// @File: TRFID
// @Purpose:
// @Author: ericm
// @Data: 25/04/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include <SPI.h>
#include <MFRC522.h>

#include "TRFID.h"

//------------------------ VARIABLES ----------------------

MFRC522 mfrc522(SS_PIN, RST_PIN);


//------------------------ FUNCTIONS ----------------------

void initTRFID(void) {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID reading UID");
}

void motorTRFID(void){
  if(mfrc522.PICC_IsNewCardPresent()){
    if(mfrc522.PICC_ReadCardSerial()){
      Serial.print("Tag UID:");
      for(byte i = 0; i < mfrc522.uid.size; i++){
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
      }

      Serial.println();
      mfrc522.PICC_HaltA();
    }
  }
}
