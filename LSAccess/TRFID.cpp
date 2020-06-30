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
static char state;
static unsigned char ucResult = 0;
static unsigned char UID[16];
static char tagType;

//------------------------ FUNCTIONS ----------------------

void initTRFID(void) {
  state = 0;

  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCK, OUTPUT);
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_MISO, INPUT);
  pinMode(PIN_RST, OUTPUT);

  digitalWrite(PIN_SDA, HIGH);
  digitalWrite(PIN_RST, 1);

  RFIDReset();
  RFIDWrite(TMODEREG, 0x8D);
  RFIDWrite(TPRESCALERREG, 0x3E);
  RFIDWrite(TRELOADREGL, 30);
  RFIDWrite(TRELOADREGH, 0);
  RFIDWrite(TXAUTOREG, 0x40);
  RFIDWrite(MODEREG, 0x3D);

  RFIDAntennaOff();
  RFIDAntennaOn();
}

void motorTRFID() {
  switch (state) {
    case 0:
      if (RFIDIsCard(&tagType)) {
        AuRFID();
        state = 1;
      }
      break;
    case 1:
      if (RFIDReadCardSerial(UID)) {
        Serial.print ("UID:");
        for (i = 0; i < 5; i++) {
          Serial.print (UID[i], HEX);
        }
        Serial.println();
        RFIDHalt();
        state = 0;
      }
      else {
        RFIDHalt();
        state = 0;
      }
      break;
  }
}


unsigned char RFIDRead(unsigned char address) {
  ucResult = 0;
  digitalWrite(PIN_SCK, LOW);
  digitalWrite(PIN_SDA, LOW);
  ucAddr = ((address << 1) & 0x7E) | 0x80;

  for (i = 8; i > 0; i--) {
    digitalWrite(PIN_MOSI, ((ucAddr & 0x80) == 0x80));
    digitalWrite(PIN_SCK, HIGH);
    ucAddr <<= 1;
    digitalWrite(PIN_SCK, LOW);
  }

  for (i = 8; i > 0; i--) {
    digitalWrite(PIN_SCK, HIGH);
    ucResult <<= 1;
    ucResult |= (char) digitalRead(PIN_MISO);
    digitalWrite(PIN_SCK, LOW);
  }

  digitalWrite(PIN_SDA, HIGH);
  digitalWrite(PIN_SCK, HIGH);
  return (char)ucResult;
}

void RFIDWrite(unsigned char address, unsigned char value) {
  unsigned char i, ucAddr;

  digitalWrite(PIN_SCK, LOW);

  digitalWrite(PIN_SDA, LOW);
  ucAddr = ((address << 1) & 0x7E);
  for (i = 8; i > 0; i--) {
    digitalWrite(PIN_MOSI, ((ucAddr & 0x80) == 0x80));
    digitalWrite(PIN_SCK, HIGH);
    ucAddr <<= 1;
    digitalWrite(PIN_SCK, LOW);
  }

  for (i = 8; i > 0; i--) {
    //output_bit (MFRC522_SI, ( (value&0x80) == 0x80));
    digitalWrite(PIN_MOSI, ((value & 0x80) == 0x80));
    digitalWrite(PIN_SCK, HIGH);
    value <<= 1;
    digitalWrite(PIN_SCK, LOW);
  }

  digitalWrite(PIN_SDA, HIGH);
  digitalWrite(PIN_SCK, HIGH);
}

void RFIDAntennaOn(void) {
  unsigned char stt;
  stt = RFIDRead(TXCONTROLREG);
  RFIDSetBit(TXCONTROLREG, 0x03);
}

void RFIDAntennaOff(void) {
  RFIDClearBit(TXCONTROLREG, 0x03);
}

void RFIDReset(void) {
  digitalWrite(PIN_RST, HIGH);
  delayMicroseconds(1);
  digitalWrite(PIN_RST, LOW);
  delayMicroseconds(1);
  digitalWrite(PIN_RST, HIGH);
  delayMicroseconds(1);
  RFIDWrite(COMMANDREG, PCD_RESETPHASE);
}

char RFIDToCard(char command, char *sendData, char sendLen, char *backData, unsigned *backLen) {
  static char _status = MI_ERR;
  static char irqEn = 0x00;
  static char waitIRq = 0x00;
  static char lastBits;
  static char n;
  static unsigned i;

  switch (command) {
    case PCD_AUTHENT:
      irqEn = 0x12;
      waitIRq = 0x10;
      break;
    case PCD_TRANSCEIVE:
      irqEn = 0x77;
      waitIRq = 0x30;
      break;
    default:
      break;
  }

  RFIDWrite(COMMIENREG, irqEn | 0x80);
  RFIDClearBit(COMMIRQREG, 0x80);
  RFIDSetBit(FIFOLEVELREG, 0x80);
  RFIDWrite(COMMANDREG, PCD_IDLE);

  for ( i = 0; i < sendLen; i++ ) {
    RFIDWrite(FIFODATAREG, sendData[i]);
  }

  RFIDWrite(COMMANDREG, command);
  if (command == PCD_TRANSCEIVE) RFIDSetBit(BITFRAMINGREG, 0x80);

  i = 0xFFFF;
  do {
    n = RFIDRead(COMMIRQREG);
    i--;
  }
  while (i && !(n & 0x01) && !(n & waitIRq));
  RFIDClearBit(BITFRAMINGREG, 0x80);

  if (i != 0) {
    if ( !(RFIDRead(ERRORREG) & 0x1B)) {
      _status = MI_OK;
      if (n & irqEn & 0x01) {
        _status = MI_NOTAGERR;
      }
      if (command == PCD_TRANSCEIVE) {
        n = RFIDRead(FIFOLEVELREG);
        lastBits = RFIDRead(CONTROLREG) & 0x07;
        if (lastBits) *backLen = (n - 1) * 8 + lastBits;
        else *backLen = n * 8;
        if (n == 0) n = 1;
        if (n > 16) n = 16;

        for (i = 0; i < n; i++) {
          backData[i] = RFIDRead( FIFODATAREG );
        }
        backData[i] = 0;
      }
    }
    else _status = MI_ERR;
  }
  return _status;
}

char RFIDRequest(char reqMode, char *TagType) {
  char _status;
  unsigned backBits;
  RFIDWrite(BITFRAMINGREG, 0x07);
  TagType[0] = reqMode;
  _status = RFIDToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
  if ((_status != MI_OK) || (backBits != 0x10)) _status = MI_ERR;
  return _status;
}

void RFIDCRC(char *dataIn, char length, char *dataOut) {
  char i, n;
  RFIDClearBit(DIVIRQREG, 0x04);
  RFIDSetBit(FIFOLEVELREG, 0x80);

  for ( i = 0; i < length; i++ ) {
    RFIDWrite(FIFODATAREG, *dataIn++);
  }

  RFIDWrite(COMMANDREG, PCD_CALCCRC);

  i = 0xFF;

  do {
    n = RFIDRead(DIVIRQREG);
    i--;
  }
  while (i && !(n & 0x04));

  dataOut[0] = RFIDRead(CRCRESULTREGL);
  dataOut[1] = RFIDRead(CRCRESULTREGM);
}

char RFIDSelectTag(char *serNum) {
  char i;
  char _status;
  char size;
  unsigned recvBits;
  char buffer[9];

  buffer[0] = PICC_SElECTTAG;
  buffer[1] = 0x70;

  for ( i = 2; i < 7; i++ ) {
    buffer[i] = *serNum++;
  }

  RFIDCRC(buffer, 7, &buffer[7]);

  _status = RFIDToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
  if ((_status == MI_OK) && (recvBits == 0x18)) size = buffer[0];
  else size = 0;
  return size;
}

void RFIDHalt(void) {
  unsigned unLen;
  char buff[4];

  buff[0] = PICC_HALT;
  buff[1] = 0;
  RFIDCRC(buff, 2, &buff[2]);
  RFIDClearBit(STATUS2REG, 0x80);
  RFIDToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
  RFIDClearBit(STATUS2REG, 0x08);
}

char RFIDAntiColl(char *serNum) {
  char _status;
  char i;
  char serNumCheck = 0;
  unsigned unLen;

  RFIDWrite(BITFRAMINGREG, 0x00);
  serNum[0] = PICC_ANTICOLL;
  serNum[1] = 0x20;
  RFIDClearBit(STATUS2REG, 0x08);
  _status = RFIDToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
  if (_status == MI_OK) {
    for (i = 0; i < 4; i++) {
      serNumCheck ^= serNum[i];
    }
    if (serNumCheck != serNum[4]) _status = MI_ERR;
  }
  return _status;
}

char RFIDIsCard(char *TagType) {
  if (RFIDRequest(PICC_REQIDL, TagType) == MI_OK) return 1;
  else return 0;
}

char RFIDReadCardSerial(char *str) {
  char _status;
  _status = RFIDAntiColl(str);
  str[5] = 0;
  if (_status == MI_OK) return 1;
  else return 0;
}

static void RFIDClearBit(char addr, char mask) {
  unsigned char tmp = 0x0;
  tmp = RFIDRead(addr);
  RFIDWrite(addr, tmp & ~mask);
}

static void RFIDSetBit(char addr, char mask) {
  unsigned char tmp = 0x0;
  tmp = RFIDRead(addr);
  RFIDWrite(addr, tmp | mask);
}
