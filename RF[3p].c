/* 
 * Management rangefinder
 * Date: 21.03.13
 */
#include <stdio.h>
#include <msp430.h>

int Result = 0;

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= BIT4;
	P1OUT |= BIT4;

	UCSCTL1 = DCORSEL_7;

	TA0CCR0 = 1;
	TA0CTL = TASSEL_2 + MC_1 + TACLR;
	TA0CCTL0 = CCIE;
	
	P1IE |= 0x10;
	P1IES &= BIT4; // LOW->HIGH
	P1IFG &= ~0x10;

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
	// P1OUT = 0x0;
	P1DIR ^= BIT4;
	TA0CTL = MC_0;
	//
}

//Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	if (!(P1IE))
	{
		//first state
		TA0CCR0 = 65000;
		TA0CTL = TASSEL_2 + MC_1 + TACLR;
		//TA0CCTL0 = 0x0;

		P1IES |= BIT4; // HIGH->LOW
		P1IFG &= ~0x10;
	}
	else
	{
		//second state
		TA0CTL = MC_0;
		Result = TA0R;
	}
}


