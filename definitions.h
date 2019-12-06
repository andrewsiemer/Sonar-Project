// definitions.h
// @description A convenient place for all program definitions.
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 12.6.19
//

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* Constants */
#define ON 1
#define OFF 0

/* State Switch */
#define sensingState digInput3

/* Transmitter State */
#define transmitterState digOutput4

/* Timer State */
#define timerState digInput12

/* LCD Pins */
#define LCD_RS digOutput16  //_LATF4
#define LCD_RW digOutput26  //_LATF6
#define LCD_EN digOutput25  //_LATF5
#define LCD_DB4 digOutput24 //_LATB9
#define LCD_DB5 digOutput23 //_LATB8
#define LCD_DB6 digOutput22 //_LATB7
#define LCD_DB7 digOutput21 //_LATB6

/* Function Definitions */
void setupPins();
float getAveragedValue(float *);
char const * getPotValue();
void pushBack(float*, float);
void displayBootScreen();
void displayIdleScreen();
void displaySensingScreen();

#endif /* DEFINITIONS_H_ */
