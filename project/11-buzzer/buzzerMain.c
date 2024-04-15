#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"




int main() {
    configureClocks();
    
    buzzer_init();
    buzzer_set_period(392);
    buzzer_set_period(440);
    // buzzer_set_period(0);
      
    enableWDTInterrupts();	/* start buzzing!!! 2MHz/1000 = 2kHz*/


    or_sr(0x18);          // CPU off, GIE on
}

const int G = 3910.995;
const int A = 4400;
const int B = 4930.883;
const int C4 = 2610.626;
const int E = 3290.628;
const int D = 2930.665;

int secondCount = 0;
int  rickroll[] = {G,A,C4,A,E,E,0,E,D,D,G,A,C4,A,D,D,0,D,C4,C4,B,A,0,G,A,C4,A,C4,C4,D,B,B,B,A,G,G};
int secondLimit = sizeof(rickroll) / sizeof(rickroll[0]);
int interrupCount = 0;
void

__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */
{

  interrupCount ++;

  if (interrupCount == 125){
    secondCount ++;
    interrupCount = 0;
  }



  if (secondCount < secondLimit) { /* once each sec... */

    buzzer_set_period(rickroll[secondCount]);

  }

  if (secondCount == secondLimit){


    interrupCount = 0;
    secondCount = 0;

    // buzzer_set_period(0);




  }



} 
