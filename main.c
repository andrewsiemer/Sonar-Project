// Sonar Project - Analog Electronics (Fall 2019)
// main.c
// 
// @author Andrew Siemer <andrew.siemer@eagles.oc.edu>
// @version 10.16.19
//

#include <p30f3013.h>
#include "aliases.h"
#include "utilities.h"
#include "definitions.h"

#include "lcd.h"

int main() {
    initializeUART();
    setupPins();
    LCD_Init();
    pause(1000);
    printf("I'm in the main!\n");
    char const * TEXT2 = "Hello World!";
    LCD_Write_XY(1, 0, TEXT2);
    
    while(1) {
      ; //Infinite loop
    }
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