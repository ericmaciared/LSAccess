/*
 * File:   main.c
 * Author: Eric Macià (eric.macia)
 *         Guillermo Sabaté (guillermo.sabate)
 *
 * Created on 24/04/2020
 */

//C INCLUDES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//LOCAL INCLUDES
#include "TTimer.h"
/*
 *
 */

// Configuration Bits - 24.1 del Datasheet
/*_CONFIG2(		IESO_OFF				// Two Speed Start-up               DISABLED
			&	SOSCSEL_LPSOSC       		// Low Power Secondary Oscillator   ENABLE
			&	WUTSEL_LEG           		// Legacy Wake-up timer selected
		 	&	FNOSC_FRCPLL        		// Fast RC oscillator w/ divide and PLL
		 	& 	FCKSM_CSDCMD			// Clock switching and clock monitor
			&	OSCIOFNC_ON			// OSCO/RC15 function               RC15
			&	IOL1WAY_OFF			// Una configuraci� per I/O remapejables deshabilitat
			&	POSCMOD_NONE			// Primary disabled
			& 	I2C1SEL_SEC
);


_CONFIG1(		JTAGEN_OFF                              // JTAG                             DISABLED
			&	GCP_OFF				// Code Protect                     DISABLED
			&	GWRP_OFF			// Write Protect                    DISABLED
			&	BKBUG_OFF			// Background Debugger              DISABLED
			&	ICS_PGx1			// ICD pins select share            PGC1/PGD1
			&	FWDTEN_OFF			// Watchdog Timer                   DISABLED
			&	WINDIS_OFF			// Windowed WDT                     DISABLED
			&	FWPSA_PR128			// Watchdog prescaler	1:128
			&	WDTPS_PS2048			// Watchdog postscale	1:2048      Pre=128 i Post=2048 --> WatchDog Timer = 8seg
);*/



void initCPU(){
    //CLKDIV=0x0000;          // clock division of the timer and CPU by 1.
    //OSCCON=0x0020;
    //RCONbits.SWDTEN = 0;    // Desactivate the Watchdog.
}

int main(void){
    initCPU();
    initTimer();

    /*TiInit();
    LeInit();
    LcInit(2,16);
    AuInit();
    SwInit();
    PbInit();
    AdInit();
    BlInit();
    SiInit();
    LcClear();
    LcCursorOff();
    LcGotoXY(0,0);
    LcPutString("Booting...");
    initMotorLCD();
    initPropaganda();*/
    while(1){
        /*MotorPushbutton();
        BlMotor();
        MotorLed();
        MotorLCD();
        MotorAudio();
        MotorPropaganda();
        MotorSIO();*/

    }
}