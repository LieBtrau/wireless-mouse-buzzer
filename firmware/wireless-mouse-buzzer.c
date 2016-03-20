#ifdef F_CPU
#undef F_CPU
#endif
#define F_CPU 1000000                   //default: 8MHz internal oscillator with /8 prescaler


#include <avr/io.h>                     //needed for port definitions of MCU
#include <avr/interrupt.h>              //needed for interrupts
volatile uint16_t timer=0;

ISR(TIM0_COMPA_vect)                    //working with software delay loops didn't work satisfactorily.  Interrupts do the job well.
{
    if(timer)
    {
        timer--;
    }
}

//It's not really half of a millisecond for waiting, but the interrupt runs at 1.9kHz
void delay(uint16_t halfms)
{
    timer=halfms;
    while(timer);
}

void enableOutputs(void)
{
    //Configure GPIOs connected to the piezo buzzer as GPIO
    DDRB |= _BV(DDB1) | _BV(DDB0);
}

void disableOutputs(void)
{
    DDRB &= (~(_BV(DDB1) | _BV(DDB0)));
}

void setup(void)
{
    OCR0A = OCR0B = 510;                //950Hz output frequency on OCR0A & OCR0B
                                        //theoretical value = 525 -> 923Hz
                                        //manual calibrated = 510
    TCCR0A |= _BV(COM0A0) | _BV(COM0B0);//toggle outputs on compare match
    TCCR0B |= _BV(WGM02) | _BV(CS00);   //Timer mode 4, no prescaling
    TCCR0C |= _BV(FOC0A);               //invert OCA with respect to OCB
    TIMSK0 |= _BV(OCIE0A);
    sei();
}

void loop(void)
{
    enableOutputs();
    delay(500);
    disableOutputs();
    delay(500);
}

int main(void)
{
    setup();
    while(1)
    {
        loop();
    }
    return 0;
}

