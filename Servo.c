#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;               // Stop WDT
  P1DIR |= BIT4;                       		// P1.4 output
  P1SEL |= BIT4;                       		// P1.4 options select
  TA0CCR0 = 640;                         	// PWM Period
  TA0CCTL3 = OUTMOD_7;                    // CCR3 reset/set
  TA0CCR3 = 60;                           // CCR3 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;       // ACLK, up mode, clear TAR

  __bis_SR_register(LPM3_bits);           // Enter LPM3
  __no_operation();                       // For debugger
}
