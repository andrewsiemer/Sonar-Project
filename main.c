// main.c
// @description Sonar Project - Analog Electronics (Fall 2019)
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 11.15.19
//

#include <p30f3013.h>
#include <string.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"

int main() {
   initializeUART();
   setupPins();
   initializeLCD();
   displayBootScreen();
   delay(2500);
  
   //startPinTimer12();
   while(1) {
      //printf("%d\r\n", readPinTimer12());
    
      //static char str[1];
      //sprintf(str, "%d", num);
     
      if (sensingState) {
         transmitterState = 1; //turn on transmitter
         displaySensingScreen();
        
         while(sensingState) {
            writeToLCDXY(4, 11, getPotValue());
            delay(100); //display refresh delay
         }
      }
      else {
         transmitterState = 0; //turn off transmitter
         displayIdleScreen();
      
         while (!sensingState) {
            ;
         }
      }
      delay(10);
   }

   return (0);
}

void displayBootScreen() {
   clearLCD();
  
   char const * TEXT = "Sonar";
   writeToLCDXY(2, 5, TEXT);
   TEXT = "Ranging";
   writeToLCDXY(3, 4, TEXT);
   TEXT = "...";
   writeToLCDXY(4, 13, TEXT);
}

void displayIdleScreen() {
   clearLCD();
  
   char const * TEXT = "*IDLE*"; 
   writeToLCDXY(1, 5, TEXT);
   TEXT = "Toggle State"; 
   writeToLCDXY(2, 2, TEXT);
   TEXT = "Switch to Begin"; 
   writeToLCDXY(3, 0, TEXT);
   TEXT = "Sensing"; 
   writeToLCDXY(4, 4, TEXT);
}

void displaySensingScreen() {
   clearLCD();
  
   char const * TEXT = "*SENSING*";
   writeToLCDXY(1, 3, TEXT);
   TEXT = "Distance:"; 
   writeToLCDXY(2, 0, TEXT);
   TEXT = "Averaging:"; 
   writeToLCDXY(4, 0, TEXT);
}

char const * getPotValue() {
   int i = getAnalogValue(0); //get ADC value on Pin 2 (AN0)
   static char const * AVERAGING;
  
   if (i > 2800)
      AVERAGING = "HIGH";
   else if (i > 1400)
      AVERAGING = "LOW ";
   else
      AVERAGING = "OFF ";
    
   return AVERAGING;
}

void setupPins() {
   /* State Switch */
   pin3Direction = INPUT; 
   pin3Type = DIGITAL;
   
   /* Transmitter State */
   pin4Direction = OUTPUT;
   pin4Type = DIGITAL;
  
   /* LCD Display */
   pin23Type = DIGITAL; 
   pin24Type = DIGITAL; 
   pin25Type = DIGITAL; 
   pin26Type = DIGITAL;
   pin16Direction = OUTPUT;
   pin21Direction = OUTPUT; 
   pin22Direction = OUTPUT; 
   pin23Direction = OUTPUT; 
   pin24Direction = OUTPUT; 
   pin25Direction = OUTPUT; 
   pin26Direction = OUTPUT; 
}
