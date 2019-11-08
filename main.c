// main.c
// @description Sonar Project - Analog Electronics (Fall 2019)
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 11.8.19
//

#include <p30f3013.h>
#include <string.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"

int main() {
  pause(1000);
  initializeUART();
  setupPins();
  LCD_Init();
  pause(50);
  displayBootScreen();
  pause(3000);
  
  char const * TEXT;
  while(1) {
    int a = getAnalogValue(3);
    printf("%i\n", a);
    LCD_Clear();
    if (runState) {
      TEXT = "*SENSING*";
      LCD_Write_XY(1, 3, TEXT);
      TEXT = "Distance:"; 
      LCD_Write_XY(2, 0, TEXT);
      TEXT = "Averaging:"; 
      LCD_Write_XY(4, 0, TEXT);
    }
     else {
      TEXT = "*IDLE*"; 
      LCD_Write_XY(1, 5, TEXT);
      TEXT = "Toggle State"; 
      LCD_Write_XY(2, 2, TEXT);
      TEXT = "Switch to Begin"; 
      LCD_Write_XY(3, 0, TEXT);
      TEXT = "Sensing"; 
      LCD_Write_XY(4, 4, TEXT);
     }
    pause(1000);
  }

  return (0);
}

void displayBootScreen() {
  char const * TEXT;
  LCD_Clear();
  TEXT = "Sonar";
  LCD_Write_XY(2, 5, TEXT);
  TEXT = "Ranging";
  LCD_Write_XY(3, 4, TEXT);
  TEXT = "...";
  LCD_Write_XY(4, 13, TEXT);
}

void setupPins() {
  /* State Switch */
  pin3Direction = INPUT; 
  pin3Type = DIGITAL;
  
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
