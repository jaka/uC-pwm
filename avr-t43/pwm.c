#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

volatile uint8_t i = 0;
volatile uint8_t d = 0;  /* Direction */

ISR (TIMER0_OVF_vect) {

  if (d)
    i++;
  else
    i--;

  if (!i)
    d = !d;
  else
    OCR1B = i;
}

void setup(void)
{
  /* Timer 0 for changing duty cycle. */
  TCCR0B |= _BV(CS02);

  TCNT0 = 0;
  TIMSK0 = _BV(TOIE0);

  /* Timer 1 for PWM. */
  TCCR1A = _BV(COM1B1) | _BV(COM1B0) | _BV(WGM10); /* Inverting mode for OC1B, mode 1 PWM. */
  TCCR1B = _BV(CS10); /* No prescaling. */

  TCNT1 = 0;
  OCR1B = 25;

  sei();
}

int main(void)
{
  DDRB = _BV(PB2); /* pin 2 port B - OC1B. */

  setup();

  for (;;)
    sleep_mode();

  return 0;
}
