//---------------------------------------------------------
// @File: TRFID*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

#ifndef _TRFID_H_
#define _TRFID_H_

#define PCD_IDLE              0x00               //NO action; Cancel the current command
#define PCD_AUTHENT           0x0E               //Authentication Key
#define PCD_RECEIVE           0x08               //Receive Data
#define PCD_TRANSMIT          0x04               //Transmit data
#define PCD_TRANSCEIVE        0x0C               //Transmit and receive data,
#define PCD_RESETPHASE        0x0F               //Reset
#define PCD_CALCCRC           0x03               //CRC Calculate

#define PICC_REQIDL          0x26               // find the antenna area does not enter hibernation
#define PICC_REQALL          0x52               // find all the cards antenna area
#define PICC_ANTICOLL        0x93               // anti-collision
#define PICC_SElECTTAG       0x93               // election card
#define PICC_AUTHENT1A       0x60               // authentication key A
#define PICC_AUTHENT1B       0x61               // authentication key B
#define PICC_READ            0x30               // Read Block
#define PICC_WRITE           0xA0               // write block
#define PICC_DECREMENT       0xC0               // debit
#define PICC_INCREMENT       0xC1               // recharge
#define PICC_RESTORE         0xC2               // transfer block data to the buffer
#define PICC_TRANSFER        0xB0               // save the data in the buffer
#define PICC_HALT            0x50               // Sleep

#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2
//------------------MFRC522 Register---------------

#define     RESERVED00            0x00
#define     COMMANDREG            0x01
#define     COMMIENREG            0x02
#define     DIVLENREG             0x03
#define     COMMIRQREG            0x04
#define     DIVIRQREG             0x05
#define     ERRORREG              0x06
#define     STATUS1REG            0x07
#define     STATUS2REG            0x08
#define     FIFODATAREG           0x09
#define     FIFOLEVELREG          0x0A
#define     WATERLEVELREG         0x0B
#define     CONTROLREG            0x0C
#define     BITFRAMINGREG         0x0D
#define     COLLREG               0x0E
#define     RESERVED01            0x0F
//PAGE 1:Command
#define     RESERVED10            0x10
#define     MODEREG               0x11
#define     TXMODEREG             0x12
#define     RXMODEREG             0x13
#define     TXCONTROLREG          0x14
#define     TXAUTOREG             0x15
#define     TXSELREG              0x16
#define     RXSELREG              0x17
#define     RXTHRESHOLDREG        0x18
#define     DEMODREG              0x19
#define     RESERVED11            0x1A
#define     RESERVED12            0x1B
#define     MIFAREREG             0x1C
#define     RESERVED13            0x1D
#define     RESERVED14            0x1E
#define     SERIALSPEEDREG        0x1F
//PAGE 2:CFG
#define     RESERVED20            0x20
#define     CRCRESULTREGM         0x21
#define     CRCRESULTREGL         0x22
#define     RESERVED21            0x23
#define     MODWIDTHREG           0x24
#define     RESERVED22            0x25
#define     RFCFGREG              0x26
#define     GSNREG                0x27
#define     CWGSPREG              0x28
#define     MODGSPREG             0x29
#define     TMODEREG              0x2A
#define     TPRESCALERREG         0x2B
#define     TRELOADREGH           0x2C
#define     TRELOADREGL           0x2D
#define     TCOUNTERVALUEREGH     0x2E
#define     TCOUNTERVALUEREGL     0x2F
//PAGE 3:TEST REGISTER
#define     RESERVED30            0x30
#define     TESTSEL1REG           0x31
#define     TESTSEL2REG           0x32
#define     TESTPINENREG          0x33
#define     TESTPINVALUEREG       0x34
#define     TESTBUSREG            0x35
#define     AUTOTESTREG           0x36
#define     VERSIONREG            0x37
#define     ANALOGTESTREG         0x38
#define     TESTDAC1REG           0x39
#define     TESTDAC2REG           0x3A
#define     TESTADCREG            0x3B
#define     RESERVED31            0x3C
#define     RESERVED32            0x3D
#define     RESERVED33            0x3E
#define     RESERVED34            0x3F

#define SDA 9
#define SCK 52
#define MOSI 51
#define MISO 50
#define RST 8

//------------------------ INCLUDES -----------------------

#include <Arduino.h>

//------------------------ FUNCTIONS ----------------------

#ifdef __cplusplus
extern "C" {
  #endif

  void initTRFID(void);
  //Pre: --
  //Post: sets initial ports and sets initial variables.

  unsigned char RFIDRead(unsigned char address)

  void RFIDWrite(unsigned char address, unsigned char value);

  void RFIDAntennaOn(void);

  void RFIDAntennaOff(void);

  void RFIDReset(void);

  static void RFIDClearBit(char addr, char mask);

  static void RFIDSetBit(char addr, char mask);

  char RFIDToCard(char command, char *sendData, char sendLen, char *backData, unsigned *backLen);

  char RFIDRequest(char reqMode, char *TagType);

  void RFIDCRC(char *dataIn, char length, char *dataOut);

  char RFIDSelectTag(char *serNum);

  void RFIDHalt(void);

  char RFIDAntiColl(char *serNum);

  char RFIDIsCard(char *TagType);

  char RFIDReadCardSerial(char *str);

  void motorTRFID(void);

  #ifdef __cplusplus
} //extern C
#endif

#endif
