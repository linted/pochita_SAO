#include <msp430g2121.h>

static void __attribute__((naked, section(".crt_0042"), used))
disable_watchdog (void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= BIT0 | BIT1; //1.0 and 1.1 to output 
    PM5CTL0 &= ~LOCKLPM5;
}

__attribute__ ( ( interrupt( TIMER1_A0_VECTOR ) ) )
void TIMER1_A0_ISR( void )
{
    //Toggle P1.0
    P1OUT ^= 0x01;
}


int main(void) {
    // WDTCTL = WDTPW | WDTHOLD;

    P1OUT |= BIT1; // turn on 1.1

    for (;;) {
        P1OUT ^= BIT1; // swap 1.1's state

        __delay_cycles(200000); // sleep for 200000 cycles
    }

}
