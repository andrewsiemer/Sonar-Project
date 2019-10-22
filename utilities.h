// utilities.h
// @description Useful functions for programming the dsPIC30F3013.
// 
// @authors Andrew Siemer <andrew.siemer@eagles.oc.edu>,
// @version 10.22.19 
//
// Based on a version from Engineering Fundamentals [ENGR-1242]
// @credit Steven Bell <steven.bell@student.oc.edu>,
//         Nick Little <nicklaus.little@alum.oc.edu>
//

#include <stdint.h>

#ifndef UTILITIES_H
#define UTILITIES_H

/* Serial port settings for debugging */
#define DEBUG_BRG 2          // Set the baud at 38400
#define DEBUG_MAX_CHARS 150  //Maximum length of the debug string

/* Debugging functions */
void initializeUART(void);  //Initializes the UART for serial communication

/* ADC functions */
int getAnalogValue(unsigned int channel);


/* Timer functions */
void pause(unsigned int);
void LCD_GotoXY(uint8_t const ROW, uint8_t const COLUMN);
void LCD_Init(void);
void LCD_Pulse_Char(uint8_t const CHARACTER);
void LCD_Pulse_Nibble(uint8_t const NIBBLE);
void LCD_Write_String (char const * TEXT);
void LCD_Write_XY (uint8_t const ROW, uint8_t const COLUMN, char const * TEXT);
void LCD_Clear(void);
void halt(void);

#endif
