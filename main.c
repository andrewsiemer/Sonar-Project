// main.c
// @description Sonar Project - Analog Electronics (Fall 2019)
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 12.6.19
//

#include <p30f3013.h>
#include <string.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"

void setupPins() {
   /* State Switch */
   pin3Direction = INPUT; 
   pin3Type = DIGITAL;
   
   /* Transmitter State */
   pin4Direction = OUTPUT;
   pin4Type = DIGITAL;

   /* Timer State */
   pin12Direction = INPUT;   
  
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

int main() {
   float data[50] = {0},
         distance;
   int countBadValues = 0;
   char const * OUT;
   char onesBuf[3], 
        tensBuf[4];
   
   initializeUART();
   setupPins();
   initializeLCD();
   displayBootScreen();
   delay(2500);
   
   while(1) { //forever
      if (sensingState) {
         displaySensingScreen();
        
         while(sensingState) {
            writeToLCDXY(4, 11, getPotValue());
            
            resetRecieverTrigger();
            transmitterState = 1; //turn on transmitter
            startDelayTimer();
            while (readRecieverTrigger() == 0)
                if (readDelayTimer() > 25500) break; //reset if timer overflow
            stopDelayTimer();
            transmitterState = 0;
            
            distance = ((float)readDelayTimer() * 0.00353 ) - 1.27;

            if (distance > 1 && distance < 30) {
                countBadValues = 0;
                pushBack(data, distance);
                
                distance = getAveragedValue(data);
                
                distance = ((float)((int)(distance * 10 + 0.5))) / 10; //round distance to nearest tenth of an inch
                
                if (distance >= 10) {
                    sprintf(tensBuf,"%0.1f", distance);
                    OUT = tensBuf;

                    writeToLCDXY(2, 6, OUT);
                } else {
                    sprintf(onesBuf,"%0.1f", distance);
                    OUT = onesBuf;

                    writeToLCDXY(2, 6, " "); //account or less digits when number is less than 10
                    writeToLCDXY(2, 7, OUT);
                }
            }
            else {
                if (countBadValues > 3) {
                    writeToLCDXY(2, 6, "----");
                } else {
                    countBadValues++;
                }
            }    
            
            delay(10); //slow down the samples 
         }
      }
      else {
         transmitterState = 0; //turn off transmitter
         displayIdleScreen();
      
         while (!sensingState); //wait for sensing switch to change
      }
   }
   return (0);
}

float getAveragedValue(float *data){
   int numAverageValues, index;
    
   if (getPotValue() == "HIGH")
      numAverageValues = 45;
   else if (getPotValue() == "LOW ") 
      numAverageValues = 15;
   else 
      numAverageValues = 1; //only use current sample
   

   float distance = 0;
   for (index = 0; index < numAverageValues; index++)
      distance += data[index]; //add up values to be averaged
 
   distance = distance/numAverageValues; //divide total distance by number of indexes to get average
   
   return distance;
}

char const * getPotValue() {
   int i = getAnalogValue(0); //get ADC value on Pin 2 (AN0)
   static char const * AVERAGING;
  
   if (i > 3200)
      AVERAGING = "HIGH";
   else if (i > 1600)
      AVERAGING = "LOW ";
   else
      AVERAGING = "OFF ";
    
   return AVERAGING;
}

void pushBack(float *data, float value) {
    int i;
    for(i = 49; i > 0; i--) {
        data[i] = data[i-1];
    }
    
    data[0] = value;
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
   TEXT = "Dist:      (IN)"; 
   writeToLCDXY(2, 0, TEXT);
   TEXT = "Averaging:"; 
   writeToLCDXY(4, 0, TEXT);
}
