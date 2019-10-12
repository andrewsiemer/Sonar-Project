/* utilities.h - Header file for utilities.c
 * Author: Steven Bell <steven.bell@student.oc.edu>
 * Based on work by Nick Little <nicklaus.little@alum.oc.edu>
 * Date: 19 December 2008
 * Last revision: 14 January 2009, SB
 * Revised: 16 December 2009, PS to add Halt function
 */

#ifndef UTILITIES_H
#define UTILITIES_H

/* Serial port settings for debugging */
// Set the baud at 38400
#define DEBUG_BRG 2
 //Maximum length of the debug string
#define DEBUG_MAX_CHARS 150

/* Debugging functions */
//Initializes the UART for serial communication
void initializeUART(void);


/* ADC functions */
int getAnalogValue(unsigned int channel);


/* Timer settings */

/* Timer functions */
void pause(unsigned int);
void startPinTimer11(void);
void startPinTimer12(void);
int readPinTimer11(void);
int readPinTimer12(void);
void stopPinTimer12(void);
void stopPinTimer11(void);
void halt();

#endif
