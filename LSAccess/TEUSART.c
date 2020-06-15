/*//---------------------------------------------------------
// @File: TEUSART
// @Purpose:
// @Author: ericm
// @Data: 04/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TEUSART.h"

//------------------------ VARIABLES ----------------------

const char menu [SIZE_MENU];

/*
static char BufferRX[BUFFER_RX_SIZE];
static char* BufferTX[BUFFER_TX_SIZE];
static unsigned char InitTx, InitRx, EndTx, EndRx;
static unsigned char  HowManyRX, HowManyTX;


static char state;

static void PutRX(char);
static char GetRX(void);
static void PutTX(char*);
static char* GetTX(void);

static char *temporal;*/

//------------------------ FUNCTIONS ----------------------
/*
void initTEUSART(void) {
  //Post: Initialize the SIO at the pins RP2 (Tx) and RP4(Rx) & ask for a timer.
  // Unlock registers
/*  __builtin_write_OSCCONL(OSCCON & 0xBF);  //Datasheet dixit (pag 110)

  RPOR1bits.RP2R= 3; //Table 10-3 del datasheet (pag 109)

  RPINR18bits.U1RXR= 4; //Set RP4 as an input

  //Lock registers
  __builtin_write_OSCCONL(OSCCON | 0x40);  //Datasheet digit (page 110)

  //Configurate the SIO

  U1BRG=103; //9600 bauds
  U1MODEbits.UARTEN = 1;
  U1MODEbits.UEN=0; //Without flow control
  U1MODEbits.BRGH=0;
  U1MODEbits.PDSEL = 0; //8 bits of data without parity.
  U1MODEbits.STSEL = 0;  // 1 Stop bit;
  U1STAbits.UTXEN = 1;
  state = 0;
  // Interruptions activated
  IEC0bits.U1RXIE = 1;
  HowManyTX = HowManyRX = InitRx = InitTx = EndRx = EndTx = 0;*/
/*}
/*
void motorTEUSART(void){
    /*switch(state){
        case 0:
            if (HowManyTX > 0){
                state = 1;
            }
            break;
        case 1:
            temporal=GetTX();
            state = 2;
            break;
        case 2:
            if (*temporal)
                state = 3;
            else
                state = 0;
            break;
        case 3:
            if (U1STAbits.TRMT != 0){
                U1TXREG = *temporal++;
                U1STAbits.UTXEN = 1;
                state=2;
            }
            break;
    }*/
/*}

void SioPutsCooperatiu(char *s) {
    //Pre: The reference to the char *s is a const char or I can guaranty that
    //     it won't be overwritten until it has been send.
    //Post: Add *s at the queue of chains to send...
    /*PutTX(s);*/
/*}

int SioCharAvail(void) {
// Pre: returns the number of characters received that haven't been picked by the GetChar function yet.
	/*return HowManyRX;*/
/*}

char SioGetChar(void) {
// Pre: SiCharAvail() Is greater than 0.
// Post: Extracts and returns the first characters to the reception queue.
	/*return GetRX();*/
/*}

void SioSendChar(char c) {
// Post: Wait until the previous character is send and sends this one.
	/*while(U1STAbits.TRMT == 0) ClrWdt();
	U1TXREG = c;
	U1STAbits.UTXEN = 1;*/
/*}

static void PutTX(char *c) {
	/*BufferTX[InitTx++] = c;
	if (InitTx == BUFFER_TX_SIZE) InitTx = 0;
	HowManyTX++;*/
/*}

static char* GetTX(void) {
	/*char *tmp;
	tmp = BufferTX[EndTx++];
	if (EndTx == BUFFER_TX_SIZE) EndTx = 0;
	HowManyTX --;
	return tmp;*/
/*}

static void PutRX(char c) {
	/*BufferRX[InitRx++] = c;
	if (InitRx == BUFFER_RX_SIZE) InitRx = 0;
	HowManyRX++;*/
/*}

static char GetRX(void) {
	/*char tmp;
	tmp = BufferRX[EndRx++];
	if (EndRx == BUFFER_RX_SIZE) EndRx = 0;
	HowManyRX --;
	return tmp;*/
/*}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
  /*
        IFS0bits.U1RXIF = 0;
	if (U1STAbits.OERR == 1) U1STAbits.OERR = 0;
	PutRX(U1RXREG);*/
/*} */
