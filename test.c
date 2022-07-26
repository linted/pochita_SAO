#include <msp430.h>
#include <msp430g2121.h>
// #include <legacymsp430.h>

typedef void (*SCallback_t)();
typedef void (*TCallback_t)(unsigned char volatile *value);
typedef void (*RCallback_t)(unsigned char value);

void start_i2c_callback() {
    
}

void transmit_i2c_callback(unsigned char volatile *value) {

}

void recv_i2c_callback(unsigned char value) {

}

static void __attribute__((naked, section(".crt_0042"), used))
disable_watchdog (void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= BIT1 | BIT4; //1.1 and 1.4 to output
    P2DIR |= BIT6 | BIT7; //2.6 and 2.7 to output
    // PM5CTL0 &= ~LOCKLPM5;
    P1SEL |= BIT6 | BIT7; // I2C

    P1OUT = BIT6 | BIT7;        // P1.6 & P1.7 Pullups
    P1REN |= BIT6 | BIT7;       // P1.6 & P1.7 Pullups

}

__attribute__ ( ( interrupt( TIMER0_A0_VECTOR ) ) )
void TIMER1_A0_ISR( void )
{
    //Toggle P1.1
    P1OUT ^= BIT1;

}


int main(void) {
    // WDTCTL = WDTPW | WDTHOLD;

    P1OUT |= BIT1; // turn on 1.1

    for (;;) {
        P1OUT ^= BIT4; // swap 1.4's state
        P2OUT ^= BIT6 | BIT7; // swap 2.6 and 2.7S

        __delay_cycles(200000); // sleep for 200000 cycles
    }

}
