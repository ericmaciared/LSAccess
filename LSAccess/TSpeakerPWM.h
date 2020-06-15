/*//---------------------------------------------------------
// @File: TTimer*
// @Purpose:
// @Author: eric.macia
//          guillermo.sabate
// @Date: 05/05/2020
//---------------------------------------------------------

#ifndef AUTAUDIO_H
#define	AUTAUDIO_H

//------------------------ INCLUDES -----------------------
#include <arduino.h>
#include "time.h"

//------------------------ DEFINES ------------------------
#define SET_AUDIO_DIR()     pinMode(SPEAKER, OUTPUT);
#define AUDIO_ON()          digitalWrite(SPEAKER, HIGH);
#define AUDIO_OFF()         digitalWrite(SPEAKER, LOW);

//------------------------ VARIABLES ----------------------
static char tHigh;
static char timer;
static char speaker;

//------------------------ FUNCTIONS ----------------------
*/
