// Sonar Project - Analog Electronics (Fall 2019)
// main.c
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 10.12.19
//

#include <p30f3013.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"

#include "lcd.h"

int main() {
   initializeUART();
   setupPins();

  // initialize the LCD
   LCD_Initialize();

   LCDPutStr("  Hello World!");  //Display String "Hello World"
   LCDGoto(8,1);                 //Go to column 8 of second line
   LCDPutChar('1');              //Display character '1'
   Delay_Seconds(1);    // 1 second delay
   LCDGoto(8,1);        //Go to column 8 of second line
   LCDPutChar('2');     //Display character '2'
   Delay_Seconds(1);    // 1 second delay
   LCDGoto(8,1);        //Go to column 8 of second line
   LCDPutChar('3');     //Display character '3'
   Delay_Seconds(1);    // 1 second delay
   DisplayClr();        // Clear the display                 
  
   halt();
   return(0);
}

void setupPins() {
    
}

// This function creates seconds delay. 
// The argument specifies the delay time in seconds
void Delay_Seconds(unsigned char z) {
    unsigned char x,y;
    for (y = 0; y < z; y++) {
        for (x = 0; x < 100; x++)__delay_ms(10);
    }
}
