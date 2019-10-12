/* utilities.c - Useful functions for programming the
 * dsPIC30F3013.
 * Author: Steven Bell <steven.bell@student.oc.edu>
 * Based on work by Nick Little <nicklaus.little@alum.oc.edu>
 * Date: 19 December 2008
 * Last revision: 1 January 2009, SB
 * Revised: 16 December 2009, PS to add Halt function
 */

#include <uart.h>
#include <stdarg.h>
#include <adc12.h>
#include <p30fxxxx.h> //?
#include <libpic30.h>

#include "utilities.h"
#include "stdio.h"

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
int getAnalogValue(unsigned int channel)
{
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

/* simulate a halt by providing a
 * function that never returns..
 *
 * not really a 'halt'... but the program won't
 * reset either!
 */
void halt()
{
	while(1)
		;
}


/* To use this function and readPinTimer, connect an input to pin 9.  After
 * calling startPinTimer, Timer 1 will count on each instruction cycle that
 * pin 9 is high.
 */
void startPinTimer12(void)
{
  // Reset Timer 1
  TMR1 = 0;

  // Set up the timer to use "gated accumulation mode"
  // See section 12.4.5 of the dsPIC30F manual for more info.
  T1CONbits.TGATE = 1;

  // Use internal clock as the timer source
  T1CONbits.TCS = 0;

  // Turn on the timer
  T1CONbits.TON = 1;

}

void stopPinTimer12(void)
{
	T1CONbits.TON = 0;
}

/* Use this function to read the the number of instruction clock cycles in the
 * Timer 1 register.  When called after startPinTimer, it will return the number
 * of cycles that pin 9 was high.
 */
int readPinTimer12(void)
{
  return(TMR1);
}
/* To use this function and readPinTimer, connect an input to pin 9.  After
 * calling startPinTimer, Timer 1 will count on each instruction cycle that
 * pin 9 is high.
 */

void startPinTimer11(void)
{
  // Reset Timer 1
  TMR2 = 0;

  // Set up the timer to use "gated accumulation mode"
  // See section 12.4.5 of the dsPIC30F manual for more info.
  T2CONbits.TGATE = 1;

  // Use internal clock as the timer source
  T2CONbits.TCS = 0;

  // Turn on the timer
  T2CONbits.TON = 1;

}

void stopPinTimer11(void)
{
	T2CONbits.TON = 0;
}

int readPinTimer11(void)
{
  return(TMR2);
}



/* Use this function to read the the number of instruction clock cycles in the
 * Timer 1 register.  When called after startPinTimer, it will return the number
 * of cycles that pin 9 was high.
 */
