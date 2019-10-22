// main.c
// @description Sonar Project - Analog Electronics (Fall 2019)
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 10.22.19
//

#include <p30f3013.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"
/*
#include <stdio.h> //to resolve printf error
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
*/

int main() {
  initializeUART();
  setupPins();
  LCD_Init();
  pause(2000);
  printf("Writing to display...\n");

  //LCD_Clear();
  char const * TEXT = "hello world";
  LCD_Write_XY(1, 0, TEXT);
  TEXT = "line 2";
  LCD_Write_XY(2, 0, TEXT);
  TEXT = "line 3 ";
  LCD_Write_XY(3, 0, TEXT);
  TEXT = "line 4";
  LCD_Write_XY(4, 0, TEXT);
 
  halt();
  return (0);
}

void setupPins() {
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
