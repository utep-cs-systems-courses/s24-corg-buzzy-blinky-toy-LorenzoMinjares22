//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include <stdbool.h>

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

bool a_press = false;
bool b_press = false;
bool c_press = false;
bool d_press = false;
bool off = false;

const int A = 4400;

const int B = 4930.883;

const int C4 = 2610.626;

const int E = 3290.628;

int  song[] = {A,B,A,B,A,B,B,B};


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
void clear_press(){
  a_press = false;
  b_press = false;
  c_press = false;
  d_press = false;

}


void turn_green(){
  P1OUT |= LED_RED;
  P1OUT &= ~LED_GREEN;
}

void turn_red(){
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;
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
    clear_press();
    off = ~off;
    // switch_interrupt_handler_P1();

  }

}


void __interrupt_vec(PORT2_VECTOR) Port_2() {

  if (P2IFG & SWITCH_2) {

    P2IFG &= ~SWITCH_2;
    clear_press();
    a_press = true;
    

  }

  if (P2IFG & SWITCH_3) {
    clear_press();
    P2IFG &= ~SWITCH_3;
    b_press = true;
    

  }

  if (P2IFG & SWITCH_4) {

    P2IFG &= ~SWITCH_4;

    

  }

  if(P2IFG & SWITCH_5) {

    P2IFG &= ~SWITCH_5;

   

 

  }

}
int secondCount =0;
int secondLimit = sizeof(song) / sizeof(song[0]);

int interrupCount = 0;

void

__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{
  while(~off){

    
    interrupCount ++;
    
    
    
    if (interrupCount == 125){

      secondCount ++;

      interrupCount = 0;

    }
    
    if (secondCount < secondLimit) { /* once each sec... */
      
      
      /*could't use swiched stament becuase of constant*/
      
      if(song[secondCount] == A){
	turn_green();
	if(interrupCount > 120 && a_press) off = true;
      }
      if(song[secondCount] == B){
	turn_red();
	if(interrupCount > 120 && b_press) off = true;
      }
   



    }



    if (secondCount == secondLimit){
      
      
      
      
      
      interrupCount = 0;
      
      secondCount = 0;
      
      
      
      // buzzer_set_period(0);
      
      
      
      
      
      
      
      
      
    }
  }//end of off if
} 
