// utilities.c
// @description Useful functions for programming the dsPIC30F3013
// 
// @authors Andrew Siemer <andrew.siemer@eagles.oc.edu>,
// @version 11.1.19 
//

#include <uart.h>
#include "definitions.h"
#include "aliases.h"
#include "utilities.h"

_FOSC(0xC100); // Required for the clock to operate properly
_FWDT(0x003F); // Disable the watchdog

/* Initializes the UART hardware for printf() debugging
 * It is recommended to call this function only once, at the beginning of the program.
 */
void initializeUART(void) {
  ConfigIntUART1(UART_RX_INT_DIS & UART_TX_INT_DIS);
  OpenUART1(UART_DIS_LOOPBACK & UART_NO_PAR_8BIT & UART_1STOPBIT & 0xA0FF, UART_TX_PIN_NORMAL & UART_TX_ENABLE & UART_ADR_DETECT_DIS, DEBUG_BRG);
}

/* Pauses execution for a specified amount of time
 * Time is specified in milliseconds
 * Maximum time that can be specified is ~65.5 seconds */
void pause(unsigned int time){
  long instructions; //instruction cycles to wait, which is what __delay32 needs

  /* 7.37 MHz clock with 4 clock cycles per instruction
   * => 1.843 MHz instruction speed
   * => 1,843 instructions/ms */

  instructions = (unsigned long)time * 1843;
  __delay32(instructions);
}

/* 
 * Begin LCD library functions
 */
void LCD_GotoXY(uint8_t const ROW, uint8_t const COLUMN) {
  uint8_t address;
  switch (ROW) {
    case 1: address = 0x00; break;
    case 2: address = 0x40; break;
    case 3: address = 0x10; break;
    case 4: address = 0x50; break;
    default: address = 0x00; break;
  }
  LCD_RS = 0;
  LCD_RW = 0;
  LCD_Pulse_Char(0x80 | (address + COLUMN));
}

void LCD_Init(void) {
  __delay32(100);
  LCD_RS = 0;
  LCD_Pulse_Nibble(0x03);
  __delay32(80);
  LCD_Pulse_Nibble(0x03); 
  __delay32(80);
  LCD_Pulse_Nibble(0x03); 
  __delay32(80);
  LCD_Pulse_Nibble(0x02); 
  __delay32(80);
  LCD_Pulse_Char(0x28); 
  LCD_Pulse_Char(0x04); 
  LCD_Pulse_Char(0x85);
  LCD_Pulse_Char(0x06);
  LCD_Pulse_Char(0x02);
  __delay32(3);
  LCD_Pulse_Char(0x0C);
  LCD_Pulse_Char(0x01);
  __delay32(6);
  
  LCD_Clear();
}

void LCD_Pulse_Char(uint8_t const CHARACTER) {
  LCD_Pulse_Nibble((CHARACTER & 0xF0) >> 4);
  LCD_Pulse_Nibble(CHARACTER & 0x0F);
  __delay32(50);
}

void LCD_Pulse_Nibble(uint8_t const NIBBLE) {
  LCD_DB7 = (NIBBLE & 0x08) > 0;
  LCD_DB6 = (NIBBLE & 0x04) > 0;
  LCD_DB5 = (NIBBLE & 0x02) > 0;
  LCD_DB4 = (NIBBLE & 0x01) > 0;
  LCD_EN = 1;
  __delay32(50);
  LCD_EN = 0;
  __delay32(50);
}

void LCD_Write_String (char const * TEXT) {
  uint16_t loop = 0;
  LCD_RS = 1;
  LCD_RW = 0;

  for (loop = 0; TEXT[loop] != '\0'; loop++) {
    LCD_Pulse_Char(TEXT[loop]);
  }
}
  
void LCD_Write_XY (uint8_t const ROW, uint8_t const COLUMN, char const * TEXT) {
  LCD_GotoXY(ROW, COLUMN);
  LCD_Write_String(TEXT);
}

void LCD_Clear (void) {
     printf("Clear display.\n");
    char const * TEXT = "       ";
    LCD_Write_XY(1, 0, TEXT);
    LCD_Write_XY(2, 0, TEXT);
    LCD_Write_XY(3, 0, TEXT);
    LCD_Write_XY(4, 0, TEXT);
}

/* simulate a halt by providing a
 * function that never returns..
 *
 * not really a 'halt'... but the program won't
 * reset either!
 */
void halt(void) {
  while(1)
    ;
}
