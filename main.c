// main.c
// @description Sonar Project - Analog Electronics (Fall 2019)
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 11.5.19
//

#include <p30f3013.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"

int main() {
  pause(1000);
  initializeUART();
  setupPins();
  LCD_Init();
  pause(1000);
  printf("Writing to display...\n");

  char const * TEXT;  
  while(1) {
    if (runState)
      TEXT = "Program Run";
     else
      TEXT = "Idle State";  
    LCD_Clear();
    LCD_Write_XY(2, 0, TEXT);
    pause(1000);
  }
  
  //halt();
  return (0);
}

void setupPins() {
  pin3Direction = INPUT; //Switch
  pin3Type = DIGITAL;
    
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
