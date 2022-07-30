#include <msp430.h>
#include <msp430g2121.h>

static void __attribute__((naked, section(".crt_0042"), used))
disable_watchdog (void)
{
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    // PM5CTL0 &= ~LOCKLPM5;
    // Unused pins as outputs
    P1DIR = 0xff;
    P2DIR = 0xff;

    // idk what this does
    WDTCTL = WDTPW | WDTHOLD;

    // Set LED directions
    P1DIR |= BIT1 | BIT4;       //1.1 and 1.4 to output
    P2DIR |= BIT6 | BIT7;       //2.6 and 2.7 to output

    // Allow for I2C 
    P1SEL |= BIT1 | BIT4 | BIT6 | BIT7;
    P2SEL |= BIT6 | BIT7;
    // P1OUT = BIT6 | BIT7;        // P1.6 & P1.7 Pullups
    P1REN |= BIT1 | BIT4 | BIT6 | BIT7;       // P1.6 & P1.7 Pullups
    P2REN |= BIT6 | BIT7;

}

__attribute__ ( ( interrupt( TIMER0_A0_VECTOR ) ) )
void TIMER1_A0_ISR( void )
{
    //Toggle P1.4
    P1OUT ^= BIT4;
}


int main(void) {
    // WDTCTL = WDTPW | WDTHOLD;

    P1OUT ^= BIT1 | BIT4; // turn on 1.1

    for (;;) {
        P1OUT ^= BIT1 | BIT4;
        P2OUT ^= BIT7 | BIT6; // swap 2.7

        __delay_cycles(900000); // sleep for 200000 cycles
    }

}


// int main(void)
// {
//   WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
//   P1DIR |= BIT1 | BIT4;                     // P1.2 and P1.3 output
//   P1SEL |= BIT1 | BIT4;                            // P1.2 and P1.3 TA1/2 options
//   P2DIR |= BIT6 | BIT7;
//   P2SEL |= BIT6 | BIT7;
//   CCR0 = 512-1;                             // PWM Period
//   CCTL1 = OUTMOD_7;                         // CCR1 reset/set
//   CCR1 = 384;                               // CCR1 PWM duty cycle
//   TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

//   __bis_SR_register(LPM3_bits);             // Enter LPM3
// }