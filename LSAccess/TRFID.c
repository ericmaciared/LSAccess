//---------------------------------------------------------
// @File: TRFID*
// @Purpose: RFID Connection for arduino implemented cooperatively
// @See: https://simplesoftmx.blogspot.com/2014/11/libreria-para-usar-lector-
//rfid-rc522.html
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TRFID.h"

//------------------------ VARIABLES ----------------------

static unsigned char i, ucAddr;
static unsigned char ucResult = 0;

//------------------------ FUNCTIONS ----------------------


void initTRFID(void){
  pinMode(SDA, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(RST, OUTPUT);

  digitalWrite(SDA, HIGH);
  digitalWrite(RST, 1);

  RFIDReset();
  RFIDWrite(TMODEREG, 0x8D);
  RFIDWrite(TPRESCALERREG, 0x3E);
  RFIDWrite(TRELOADREGL, 30);
  RFIDWrite(TRELOADREGH, 0);
  RFIDWrite(TXAUTOREG, 0x40);
  RFIDWrite(MODEREG, 0x3D);

  RFIDAntennaOff() ;
  RFIDAntennaOn();
}

unsigned char RFIDRead(unsigned char address) {
  ucResult = 0;
  digitalWrite(SCK, LOW);
  digitalWrite(SDA, LOW);
  ucAddr = ((Address<<1)&0x7E)|0x80;

  for (i = 8; i > 0; i--) {
    digitalWrite(MOSI, ((ucAddr&0x80) == 0x80));
    digitalWrite(SCK, HIGH);
    ucAddr <<= 1;
    digitalWrite(SCK, LOW);
  }

  for (i = 8; i > 0; i--) {
    digitalWrite(SCK, HIGH);
    ucResult <<= 1;
    ucResult|= (char) digitalRead(MISO);
    digitalWrite(SCK, LOW);
  }

  digitalWrite(SDA, HIGH);
  digitalWrite(SCK, HIGH);
  return (char)ucResult;
}

void RFIDWrite(unsigned char address, unsigned char value){
  unsigned char i, ucAddr;

  digitalWrite(SCK, LOW);

  digitalWrite(SDA, LOW);
  ucAddr = ((address<<1)&0x7E);
  for (i = 8; i > 0; i--) {
    digitalWrite(MOSI, ((ucAddr&0x80) == 0x80));
    digitalWrite(SCK, HIGH);
    ucAddr <<= 1;
    digitalWrite(SCK, LOW);
  }

  for (i = 8; i > 0; i--){
    //output_bit (MFRC522_SI, ( (value&0x80) == 0x80));
    digitalWrite(MOSI, ((value&0x80) == 0x80));
    digitalWrite(SCK, HIGH);
    value <<= 1;
    digitalWrite(SCK, LOW);
  }

  digitalWrite(SDA, HIGH);
  digitalWrite(SCK, HIGH);
}

void RFIDAntennaOn(void){
  unsigned char stt;
  stt = RFIDRead(XCONTROLREG);
  RFIDSetBit(TXCONTROLREG, 0x03);
}

void RFIDAntennaOff(void){
  RFIDClearBit(TXCONTROLREG, 0x03);
}

void RFIDReset(void){
  digitalWrite(RST, HIGH);
  delayMicroseconds(1);
  digitalWrite(RST, LOW);
  delayMicroseconds(1);
  digitalWrite(RST, HIGH);
  delayMicroseconds(1);
  RFIDWrite(COMMANDREG, PCD_RESETPHASE);
}

static void RFIDClearBit(char addr, char mask){
  unsigned char tmp = 0x0;
  tmp = RFIDRead(addr);
  RFIDWrite(addr, tmp&~mask);
}

static void RFIDSetBit(char addr, char mask){
  unsigned char tmp =0x0;
  tmp = MFRC522_Rd(addr);
  MFRC522_Wr(addr, tmp|mask);
}
