// definitions.h
// @description A convenient place for all program definitions.
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 11.15.19
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

/* LCD Pins */
#define LCD_RS digOutput22  //_LATF4
#define LCD_RW digOutput16  //_LATF6
#define LCD_EN digOutput21  //_LATF5
#define LCD_DB4 digOutput23 //_LATB9
#define LCD_DB5 digOutput24 //_LATB8
#define LCD_DB6 digOutput25 //_LATB7
#define LCD_DB7 digOutput26 //_LATB6

/* Function Definitions */
void setupPins();
void displayBootScreen();
void displayIdleScreen();
void displaySensingScreen();
char const * getPotValue();

#endif /* DEFINITIONS_H_ */
