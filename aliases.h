// aliases.h
// @description Definitions to simplify programming the dsPIC30F3013.
//
// @author Steven Bell <steven.bell@student.oc.edu>
// @version 12.18.2008
//
// -------------------------------------------------------------------------
// @history
// 01.14.2009 - SB
// 05.28.2009 - Pat Smith, updated for actual pin numbers
// 11.6.2019 - Andrew Siemer, refactor
// -------------------------------------------------------------------------
//

#include <p30f3013.h>

//Aliases to refer to the pins when setting them as inputs or outputs
//The TRISx registers control the pin direction (1 makes it an input)
#define pin2Direction TRISBbits.TRISB0 //pin 2
#define pin3Direction TRISBbits.TRISB1 //pin 3
#define pin4Direction TRISBbits.TRISB2 //pin 4
#define pin5Direction TRISBbits.TRISB3 //pin 5
#define pin6Direction TRISBbits.TRISB4 //pin 6
#define pin7Direction TRISBbits.TRISB5 //pin 7

#define pin10Direction TRISCbits.TRISC15 //pin 10
#define pin11Direction TRISCbits.TRISC13 //pin 11
#define pin12Direction TRISCbits.TRISC14 //pin 12

#define pin14Direction TRISDbits.TRISD9 //pin 14
#define pin15Direction TRISDbits.TRISD8 //pin 15

#define pin16Direction TRISFbits.TRISF6 //pin 16
#define pin21Direction TRISFbits.TRISF5 //pin 21
#define pin22Direction TRISFbits.TRISF4 //pin 22

#define pin23Direction TRISBbits.TRISB9 //pin 23
#define pin24Direction TRISBbits.TRISB8 //pin 24
#define pin25Direction TRISBbits.TRISB7 //pin 25
#define pin26Direction TRISBbits.TRISB6 //pin 26

//Aliases for setting the TRISx bits above
#define INPUT 1
#define OUTPUT 0

//Aliases to set the pins as analog or digital
#define pin2Type ADPCFGbits.PCFG0 //pin 2
#define pin3Type ADPCFGbits.PCFG1 //pin 3
#define pin4Type ADPCFGbits.PCFG2 //pin 4
#define pin5Type ADPCFGbits.PCFG3 //pin 5
#define pin6Type ADPCFGbits.PCFG4 //pin 6
#define pin7Type ADPCFGbits.PCFG5 //pin 7
#include <stdio.h> //to resolve printf error
#include <p30f3013.h>

//Aliases to refer to the pins when setting them as inputs or outputs
//The TRISx registers control the pin direction (1 makes it an input)
#define pin2Direction TRISBbits.TRISB0 //pin 2
#define pin3Direction TRISBbits.TRISB1 //pin 3
#define pin4Direction TRISBbits.TRISB2 //pin 4
#define pin5Direction TRISBbits.TRISB3 //pin 5
#define pin6Direction TRISBbits.TRISB4 //pin 6
#define pin7Direction TRISBbits.TRISB5 //pin 7

#define pin10Direction TRISCbits.TRISC15 //pin 10
#define pin11Direction TRISCbits.TRISC13 //pin 11
#define pin12Direction TRISCbits.TRISC14 //pin 12

#define pin14Direction TRISDbits.TRISD9 //pin 14
#define pin15Direction TRISDbits.TRISD8 //pin 15

#define pin16Direction TRISFbits.TRISF6 //pin 16
#define pin21Direction TRISFbits.TRISF5 //pin 21
#define pin22Direction TRISFbits.TRISF4 //pin 22

#define pin23Direction TRISBbits.TRISB9 //pin 23
#define pin24Direction TRISBbits.TRISB8 //pin 24
#define pin25Direction TRISBbits.TRISB7 //pin 25
#define pin26Direction TRISBbits.TRISB6 //pin 26

//Aliases for setting the TRISx bits above
#define INPUT 1
#define OUTPUT 0

//Aliases to set the pins as analog or digital
#define pin2Type ADPCFGbits.PCFG0 //pin 2
#define pin3Type ADPCFGbits.PCFG1 //pin 3
#define pin4Type ADPCFGbits.PCFG2 //pin 4
#define pin5Type ADPCFGbits.PCFG3 //pin 5
#define pin6Type ADPCFGbits.PCFG4 //pin 6
#define pin7Type ADPCFGbits.PCFG5 //pin 7

#define pin23Type ADPCFGbits.PCFG9 //pin 23
#define pin24Type ADPCFGbits.PCFG8 //pin 24
#define pin25Type ADPCFGbits.PCFG7 //pin 25
#define pin26Type ADPCFGbits.PCFG6 //pin 26
//The rest of the pins are digital only

//Aliases for setting the pin type bits above
#define DIGITAL 1
#define ANALOG 0

/* Digital outputs */
//The LATx registers control the output value
//Note that these only work when the corresponding pin is set as an output
#define digOutput2 LATBbits.LATB0 //pin 2
#define digOutput3 LATBbits.LATB1 //pin 3
#define digOutput4 LATBbits.LATB2 //pin 4
#define digOutput5 LATBbits.LATB3 //pin 5
#define digOutput6 LATBbits.LATB4 //pin 6
#define digOutput7 LATBbits.LATB5 //pin 7

#define digOutput10 LATCbits.LATC15 //pin 10
#define digOutput11 LATCbits.LATC13 //pin 11
#define digOutput12 LATCbits.LATC14 //pin 12

#define digOutput14 LATDbits.LATD9 //pin 14
#define digOutput15 LATDbits.LATD8 //pin 15

#define digOutput16 LATFbits.LATF6 //pin 16
#define digOutput21 LATFbits.LATF5 //pin 21
#define digOutput22 LATFbits.LATF4 //pin 22

#define digOutput23 LATBbits.LATB9 //pin 23
#define digOutput24 LATBbits.LATB8 //pin 24
#define digOutput25 LATBbits.LATB7 //pin 25
#define digOutput26 LATBbits.LATB6 //pin 26

/* Digital inputs */
//The PORTx registers are used to read the pin input values
//Note that these only work when the corresponding pin is set as an input
#define digInput2 PORTBbits.RB0 //pin 2
#define digInput3 PORTBbits.RB1 //pin 3
#define digInput4 PORTBbits.RB2 //pin 4
#define digInput5 PORTBbits.RB3 //pin 5
#define digInput6 PORTBbits.RB4 //pin 6
#define digInput7 PORTBbits.RB5 //pin 7

#define digInput10 PORTCbits.RC15 //pin 10
#define digInput11 PORTCbits.RC13 //pin 11
#define digInput12 PORTCbits.RC14 //pin 12

#define digInput14 PORTDbits.RD9 //pin 14
#define digInput15 PORTDbits.RD8 //pin 15

#define digInput16 PORTFbits.RF6 //pin 16
#define digInput21 PORTFbits.RF5 //pin 21
#define digInput22 PORTFbits.RF4 //pin 22

#define digInput23 PORTBbits.RB9 //pin 23
#define digInput24 PORTBbits.RB8 //pin 24
#define digInput25 PORTBbits.RB7 //pin 25
#define digInput26 PORTBbits.RB6 //pin 26

/* Analog inputs */
//These are pin aliases for the ADC channels
#define analogInput2 0 //pin 2
#define analogInput3 1 //pin 3
#define analogInput4 2 //pin 4
#define analogInput5 3 //pin 5
#define analogInput6 4 //pin 6
#define analogInput7 5 //pin 7
//Intermediate pins are digital only
#define analogInput23 9 //pin 23
#define analogInput24 8 //pin 24
#define analogInput25 7 //pin 25
#define analogInput26 6 //pin 26
