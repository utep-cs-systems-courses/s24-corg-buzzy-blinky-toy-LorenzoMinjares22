//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"


#define SW1 BIT3/* switch1 is p1.3 */

#define SW2 BIT0
#define SW3 BIT1
#define SW4 BIT2
#define SW5 BIT3

#define SWITCH_P1 SW1/* button on msp430 board */


/*buttons on display mod*/

#define SWITCH_2 SW2

#define SWITCH_3 SW3

#define SWITCH_4 SW4

#define SWITCH_5 SW5



#define SWITCH_P2 (SWITCH_2 | SWITCH_3 | SWITCH_4 | SWITCH_5)
int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;


  
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */

  
  enableWDTInterrupts();/* enable periodic interrupt */



  P1REN |= SWITCH_P1;

  P1IE |= SWITCH_P1;

  P1OUT |= SWITCH_P1;

  P1DIR &= ~SWITCH_P1;





  P2REN |= SWITCH_P2;

  P2IE |= SWITCH_P2;

  P2IES |= SWITCH_P2;

  P2OUT |= SWITCH_P2;
  
  or_sr(0x18);		/* CPU off, GIE on */
}

/* red board side swich*/
void switch_interrupt_handler_P1() {

  char p1val = P1IN;



  P1IES |= (p1val & SWITCH_P1);

  P1IES &= (p1val | ~SWITCH_P1);
}



void __interrupt_vec(PORT1_VECTOR) Port_1() {

  if(P1IFG & SWITCH_P1) {

    P1IFG &= ~SWITCH_P1;
    P1OUT |= LED_GREEN;
    // switch_interrupt_handler_P1();

  }

}


void __interrupt_vec(PORT2_VECTOR) Port_2() {

  if (P2IFG & SWITCH_2) {

    P2IFG &= ~SWITCH_2;

    

  }

  if (P2IFG & SWITCH_3) {

    P2IFG &= ~SWITCH_3;

    

  }

  if (P2IFG & SWITCH_4) {

    P2IFG &= ~SWITCH_4;

    

  }

  if(P2IFG & SWITCH_5) {

    P2IFG &= ~SWITCH_5;

   

 

  }

}
void

__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{
  
} 
