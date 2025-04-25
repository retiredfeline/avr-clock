#include "clock.h"
#include "at90s8515.h"

#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
	tickdiv--;		// timer 1 will reset to 0 on reaching count
}

void ports_init(void)
{
	DDRC = 0xFF;		// all output
	PORTC = 0xFF;		// all segment outputs high
	DDRA = 0xFF;		// all output
	PORTA = 0xFF;		// all digit outputs high
	DDRD = 0x00;		// all input
	PORTD = 0xFF;		// input pullup activated
	DDRB = 0xFF;		// all output, to start
}

void timer_init(void)
{
	TCCR1B = 0x00;		// stop counter
	TCCR1A = 0x00;		// disconnected from output pin, no PWM
	OCR1AH = COUNTDIV >> 8;
	OCR1AL = COUNTDIV & 0xFF;
	TCNT1H = 0x00;		// start at 0
	TCNT1L = 0x00;
	TCCR1B = (1 << CTC1) | 0x02;	// clear counter on match, CK/8
	TIMSK |= (1 << OCIE1A);	// enable timer interrupt
	sei();			// enable global interrupt
}

void delay5us(void)
{
	TCNT0 = (256 - 5);	// 5µs -> 200 kHz -> 5 counts @ 1 MHz
	TCCR0 = 0x02;		// CK/8
	while ((TIFR & (1 << TOV0)) == 0)
		;
	TIFR |= (1 << TOV0);
	TCCR0 = 0x00;		// stop counter
}
