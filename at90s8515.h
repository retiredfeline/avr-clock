#ifndef	AT90C8515_H
#define	AT90C8515_H

#define __AVR_AT90S8515__       1

// Crystal frequency

#ifdef	X8_000_000
#define	COUNTDIV	250			// 8 MHz / 8 -> 4000 Hz
#define	TICKDIV		16			// 4000 Hz -> 250 Hz
#define	TICKSINSEC	250
#endif

typedef unsigned char	tick_t;

#include        <avr/io.h>

#define	SEGMENTS	PORTC
#define	DIGITS		PORTA
#define	SWITCHES	PIND
#define	I2C_ADDR	0x68U
#define	SCL_L()		PORTB &= ~0x04
#define	SCL_H()		PORTB |= 0x04
#define	SDA_L()		PORTB &= ~0x08
#define	SDA_H()		PORTB |= 0x08

extern uchar volatile tickdiv;
extern void ports_init(void);
extern void timer_init(void);
extern void delay5us(void);

static inline void pullup_init(void)
{
	// pullup for SDA activated when reading
}

static inline uchar READ_SDA(void)
{
	uchar d;

	DDRB ^= 0x08;
	PORTB |= 0x08;		// turn on pullup
	d = PINB & 0x08;
	PORTB &= ~0x08;		// disable pullup
	DDRB ^= 0x08;
	return d;
}

#define	__naked
#define	__code
#define	__interrupt(x)

#define	ASMRET()

#endif
