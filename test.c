#include <msp430.h>
#include <msp430g2121.h>
// #include <legacymsp430.h>

static void __attribute__((naked, section(".crt_0042"), used))
disable_watchdog (void)
{
    // Unused pins as outputs
    P1DIR = 0xFF;
    P2DIR = 0xFF;

    // IDK what this line is supposed to do, but it doesn't compile
    // PM5CTL0 &= ~LOCKLPM5;

    // idk what this does
    WDTCTL = WDTPW | WDTHOLD;

    // Set LED directions
    P1DIR |= BIT1 | BIT4;       //1.1 and 1.4 to output
    P2DIR |= BIT6 | BIT7;       //2.6 and 2.7 to output

    // Allow for I2C 
    P1SEL |= BIT6 | BIT7;
    P1OUT = BIT6 | BIT7;        // P1.6 & P1.7 Pullups
    P1REN |= BIT6 | BIT7;       // P1.6 & P1.7 Pullups

}

__attribute__ ( ( interrupt( TIMER0_A0_VECTOR ) ) )
void TIMER1_A0_ISR( void )
{
    //Toggle P1.4
    P1OUT ^= BIT4;

}


int main(void) {
    // WDTCTL = WDTPW | WDTHOLD;

    P1OUT |= BIT1; // turn on 1.1

    for (;;) {
        P2OUT ^= BIT7; // swap 2.7

        __delay_cycles(200000); // sleep for 200000 cycles
    }

}
