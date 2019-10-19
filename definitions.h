// Sonar Project - Analog Electronics (Fall 2019)
// main.c
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 10.19.19
//

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/**
 * constants
 *  -- NOTICE - DO NOT END THESE STATEMENTS WITH SEMICOLONS
 */
#define ON 1
#define OFF 0
#define LOW 0
#define HIGH 1

#define LCD_RS _LATF4
#define LCD_RW _LATF6
#define LCD_EN _LATF5
#define LCD_DB4 _LATB9
#define LCD_DB5 _LATB8
#define LCD_DB6 _LATB7
#define LCD_DB7 _LATB6

/*
#define LCD_RS digOutput22  //_LATF4
#define LCD_RW digOutput16  //_LATF6
#define LCD_EN digOutput21  //_LATF5
#define LCD_DB4 digOutput23 //_LATB9
#define LCD_DB5 digOutput24 //_LATB8
#define LCD_DB6 digOutput25 //_LATB7
#define LCD_DB7 digOutput26 //_LATB6
*/

/*
 * function definitions
 */
void setupPins();

#endif /* DEFINITIONS_H_ */
