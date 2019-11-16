// utilities.h
// @description Useful functions for programming the dsPIC30F3013.
// 
// @authors Andrew Siemer <andrew.siemer@eagles.oc.edu>,
// @version 11.15.19 
//

#include <stdint.h>

#ifndef UTILITIES_H
#define UTILITIES_H

/* Serial port settings for debugging */
#define DEBUG_BRG 2          // Set the baud at 38400
#define DEBUG_MAX_CHARS 150  //Maximum length of the debug string

/* Debugging functions */
void initializeUART(void);  //Initializes the UART for serial communication

/* Timer functions */
void delay(unsigned int);
void startPinTimer12(void);
int readPinTimer12(void);
void stopPinTimer12(void);

/* LCD functions */
void goToLCDXY(uint8_t const ROW, uint8_t const COLUMN);
void initializeLCD(void);
void pulseCharLCD(uint8_t const CHARACTER);
void pulseNibbleLCD(uint8_t const NIBBLE);
void writeStringToLCD (char const * TEXT);
void writeToLCDXY (uint8_t const ROW, uint8_t const COLUMN, char const * TEXT);
void clearLCD(void);

/* ADC functions */
int getAnalogValue(unsigned int channel);

#endif
