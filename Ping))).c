#include <stdio.h>
#include <msp430.h> 

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= BIT4;
	P1OUT |= BIT4;

	UCSCTL1 = DCORSEL_5;                      // Select DCO range 24MHz operation
	UCSCTL2 = 1;
	UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
	UCSCTL4 |= SELS_2;
	UCSCTL6 |= XT2DRIVE_2;

	TA0CCR0 = 1;
	TA0CTL = TASSEL_2 + MC_1 + TACLR  ;
	TA0CCTL0 = CCIE;


	while (1)
	{
		__bis_SR_register(LPM0_bits + GIE);
		__no_operation();
	}
	return 0;
}

// Timer0 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
  P1OUT = 0x0;                            // Toggle P1.0
}

