//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"


#define SW1 BIT3/* switch1 is p1.3 */

#define SWITCHES SW1/* only 1 switch on this board */


int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
  
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */

  P1REN |= SWITCHES;/* enables resistors for switches */

  P1IE |= SWITCHES;/* enable interrupts from switches */

  P1OUT |= SWITCHES;/* pull-ups for switches */

  P1DIR &= ~SWITCHES;/* set switches' bits for input */
  
  enableWDTInterrupts();/* enable periodic interrupt */

  or_sr(0x18);		/* CPU off, GIE on */
}

// global state var to count time
vwitch_interrupt_handler()

{

  char p1val = P1IN;/* switch is in P1 */



  /* update switch interrupt sense to detect changes from current buttons */

  P1IES |= (p1val & SWITCHES);/* if switch up, sense down */

  P1IES &= (p1val | ~SWITCHES);/* if switch down, sense up */



  /* up=red, down=green */

  if (p1val & SW1) {

    P1OUT |= LED_RED;

    P1OUT &= ~LED_GREEN;

  } else {

    P1OUT |= LED_GREEN;

    P1OUT &= ~LED_RED;

  }

}

int secondCount = 0;
int firstCount = 0;
int blinkLimit =5;
int thirdCount = 0;
void

__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{
  firstCount++;
 

  if (firstCount >= 250 && firstCount < 1250) { /* once each sec... */
    secondCount++;   
    //secondCount = 0;/* reset count */
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;/* toggle green LED */

    if(secondCount >= blinkLimit){
      secondCount = 0;
      P1OUT |= LED_RED;
    }else{
      P1OUT &= ~LED_RED;
    }
  }
  if (firstCount >= 1250){

    firstCount = 0;
    P1OUT &= ~LED_RED;
    P1OUT ^= LED_GREEN;   //Toogle red every 500 interupts/sec

      
  }
  thirdCount ++;

  if (thirdCount >= 250) {  // once each second

    thirdCount = 0;

    blinkLimit ++;     // reduce duty cycle

    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.

      blinkLimit = 0;

  }


} 
