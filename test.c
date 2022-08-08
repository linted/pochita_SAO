#include <msp430.h>
#include <msp430g2121.h>

// static void __attribute__((naked, section(".crt_0042"), used))
// disable_watchdog (void)
// {
//     /* Disable the GPIO power-on default high-impedance mode to activate
//     // previously configured port settings
//     // PM5CTL0 &= ~LOCKLPM5;

//     // idk what this does*/
//     WDTCTL = WDTPW | WDTHOLD;

// }

// __attribute__ ( ( interrupt( TIMER0_A0_VECTOR ) ) )
// void TIMER1_A0_ISR( void )
// {
//     //Toggle P1.4
//     P1OUT ^= BIT4;
// }


int main(void) {
    // WDTCTL = WDTPW | WDTHOLD;

    // P1OUT ^= BIT1 | BIT4; // turn on 1.
    BCSCTL3 |= LFXT1S_2;
    IFG1 &= ~OFIFG;
    _bis_SR_register(SCG1+SCG0);
    BCSCTL2 |= SELM_3 + DIVM_3;


    // Set LED directions
    P1DIR |= BIT1 | BIT4;       //1.1 and 1.4 to output
    P2DIR |= BIT6 | BIT7;       //2.6 and 2.7 to output

    // Allow for I2C 
    P1SEL |= BIT6 | BIT7;
    P2SEL &= ~(BIT6 | BIT7); //pwm
    //P1OUT |= BIT1 | BIT4 | BIT6 | BIT7;        // P1.6 & P1.7 
    //P2OUT |= BIT6 | BIT7;
    P1REN |= BIT6 | BIT7;       // P1.6 & P1.7 Pullups
    // P2REN |= BIT6 | BIT7;

    for (;;) {
        P1OUT ^= BIT1 | BIT4;
        P2OUT ^= BIT7 | BIT6; // swap 2.7

        __delay_cycles(1000); // sleep for 1000 cycles
    }

}


// #include <msp430g2121.h>

// int main(void)
// {
//   volatile unsigned int i;                  // Volatile to prevent removal
//   WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
//   BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
//   IFG1 &= ~OFIFG;                           // Clear OSCFault flag
//   __bis_SR_register(SCG1 + SCG0);           // Stop DCO
//   BCSCTL2 |= SELM_3 + DIVM_3;               // MCLK = LFXT1/8
//   P2SEL&=~(BIT6|BIT7);
//   P1DIR = 0xFF;                             // All P1.x outputs
//   P1OUT = 0xff;                                // All P1.x reset
//   P2DIR = 0xFF;                             // All P2.x outputs
//   P2OUT = 0xff;                                // All P2.x reset

//   for (;;)
//   {
//     P1OUT ^= BIT4;                          // P1.0 set
//     P2OUT ^= BIT6 | BIT7;
//     for (i = 0; i < 10; i++);               // Delay 1x
//     // P1OUT = 0;                         // P1.0 reset
//     // P2OUT = 0;
//     // for (i = 100; i > 0; i--);             // Delay 100x
//   }
// }