// utilities.c
// @description Useful functions for programming the dsPIC30F3013
// 
// @authors Andrew Siemer <andrew.siemer@eagles.oc.edu>,
// @version 10.22.19 
//
// Based on a version from Engineering Fundamentals [ENGR-1242]
// @credit Steven Bell <steven.bell@student.oc.edu>,
//         Nick Little <nicklaus.little@alum.oc.edu>
//

#include <uart.h>
#include <stdarg.h>
#include <adc12.h>
#include <stdio.h>
#include <p30f3013.h>
#include "definitions.h"
#include "aliases.h"
#include "utilities.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>

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

/* Grabs a value from the Analog-to-Digital converter.  It initializes the ADC hardware,
 * gets a sample, converts it and returns the value.  It assumes that no other code
 * is running which requires the ADC hardware.
 * Returns an int with a maximum value of 2^12 = 4096.
 */
int getAnalogValue(unsigned int channel) {
  int result;

  // Turn off the ADC before we start setting the registers
  ADCON1bits.ADON = 0;

  IFS0bits.ADIF = 0; // Clear the ADC interrupt flag
  IPC2bits.ADIP = 0; // Clear the interrupt priority
  IEC0bits.ADIE = 0; // Disable ADC interrupt

  // Start by setting each of the six 16-bit registers for desired operation
  // The constants used to set the registers are defined in adc12.h
  // See the dsPIC30F family manual, section 18, for more information on the ADC registers.

  // A/D Input Select Register (ADCHS)
    // CH0NA - Negative reference; can be either internal or analog channel 0.
    // CH0SA - Positive value to measure; a number between 0 and 7 (since we have 8 analog inputs)
  ADCHSbits.CH0NA = 0; // Use internal negative reference
  ADCHSbits.CH0SA = channel; // Use the given pin as the positive value

  // A/D Port Configuration Register (ADPCFG)
  // We don't change any Analog/Digital pin settings here, because
  // they should have been setup earlier using the pinXType aliases.

  // A/D Input Scan Selection Register (ADCSSL)
  // This function only grabs one value, so we'll turn it off
  ADCSSL = SCAN_NONE;

  // A/D Control Register 3 (ADCON3)
    // SAMC - Sample time delay (not used with manual sampling)
    // ADRC - Clock source select
    // ADCS - Conversion clock speed
  ADCON3 = ADC_SAMPLE_TIME_0 & ADC_CONV_CLK_SYSTEM & ADC_CONV_CLK_5Tcy;

  // A/D Control Register 2 (ADCON2)
    // VCFG - Voltage reference configuration
    // SMPI - Samples between interrupts (up to 16; in the mean time, the values will
    //        be placed in the buffer
    // ALTS - Alternate input sample mode - switches between the mux inputs on each sample
    // BUFM - Buffer mode; 2 8-word buffers or one 16-bit one
    // CSCNA - Scan input selections?
    // BUFS - Buffer fill status (read-only)
  ADCON2 = ADC_VREF_AVDD_AVSS & ADC_SAMPLES_PER_INT_1 & ADC_ALT_BUF_OFF & ADC_ALT_INPUT_OFF & ADC_SCAN_OFF;

  // A/D Control Register 1 (ADCON1)
    // ADON - Module on/off
    // ADSIDL - Idle mode operation
    // FORM - Output format
    // SSRC - Conversion trigger selection
    //        When SSRC<2:0> = 000, the conversion trigger is under software control.
    //        Clearing the SAMP bit will cause the conversion trigger.
    // ASAM - Auto sampling; begin a new conversion as soon as one ends
    // SAMP - Enable sampling
    // DONE - Conversion complete (read-only)
  ADCON1 = ADC_MODULE_ON & ADC_FORMAT_INTG & ADC_CLK_MANUAL & ADC_AUTO_SAMPLING_OFF & ADC_SAMP_OFF;

  //Let the ADC turn on and stabilize at least 20us.
  __delay32(300);

  // Begin sampling and wait
  ADCON1bits.SAMP = 1;
  __delay32(300);

  // End sampling and start the conversion
  ADCON1bits.SAMP = 0;

  // Wait for the conversion to finish
  while(ADCON1bits.DONE == 0);

  // Get the value from the buffer
  result = ADCBUF0;

  // Turn off the ADC
  ADCON1bits.ADON = 0;

  return(result);
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
  LCD_RS = LOW;
  LCD_RW = LOW;
  LCD_Pulse_Char(0x80 | (address + COLUMN));
  
}

void LCD_Init(void) {
  __delay32(100);
  LCD_RS = LOW;
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
  LCD_Pulse_Char(0x01); // clear display
  __delay32(6);
  
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
  LCD_RS = HIGH;
  LCD_RW = LOW;

  for (loop = 0; TEXT[loop] != '\0'; loop++) {
    LCD_Pulse_Char(TEXT[loop]);
  }
}
  
void LCD_Write_XY (uint8_t const ROW, uint8_t const COLUMN, char const * TEXT) {
  LCD_GotoXY(ROW, COLUMN);
  LCD_Write_String(TEXT);
}

void LCD_Clear (void) {
  LCD_Pulse_Char(0x01);
  __delay32(6);
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
