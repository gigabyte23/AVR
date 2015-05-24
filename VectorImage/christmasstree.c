//Osciloscope Vector Picture
//Version for Attiny13/25/45 MCU family
//Łukasz Skwarszczow 2015
//
//MCU - ATTINY13V 1K ROM
//MAX FREQ for 13V version @ 5.0V 4MHz
#define F_CPU 4000000	

#include <avr/io.h>
#include <util/delay.h>

#define XR		OCR0A
#define YR 		OCR0B

#define X_PIN		PB0
#define Y_PIN		PB1

#define X_DDR		DDRB
#define Y_DDR		DDRB

#define TRACE_DELAY_TIME_MS	1900

#define DOTS_POINTS_TRACE	19


unsigned char x_points[DOTS_POINTS_TRACE] = {	110, 110, 50, 80, 65, 95, 80, 110, 95, 125,
	155, 140, 170, 155, 185, 170, 200, 140, 140};
unsigned char y_points[DOTS_POINTS_TRACE] = {	15, 35, 35, 85, 85, 135, 135, 185, 185, 235,
	185, 185, 135, 135, 85, 85, 35, 35, 15};

void init()
{
	X_DDR = (1<<X_PIN);
	Y_DDR = (1<<Y_PIN);
	DDRB = 0xFF;
    DDRB = 0xFF;

	TCCR0A = (	1<<COM0A1 | 0<<COM0A0 |		
			1<<COM0B1 | 0<<COM0B0 |		
			1<<WGM01  | 1<<WGM00);		

	TCCR0B = (	0<<FOC0A | 0<<FOC0B |		
			0<<WGM02 |			
			0<<CS02	 | 0<<CS01 |		
			1<<CS00 );

	TIMSK0 = (	0<<OCIE0B | 0<<TOIE0 |
			0<<OCIE0A );

	TCNT0 = 0;					

	OCR0A = 0;					
	OCR0B = 0;
}


int main()
{
	unsigned char t;

	init();						
	while (1)					
	{
		for(t = 0; t < DOTS_POINTS_TRACE; t++)
		{
			XR = x_points[t];
			YR = y_points[t];
			_delay_us(TRACE_DELAY_TIME_MS);
		}
	}
}
