/*
 * uart.c
 *
 * Created: 31-03-2012 14:38:46
 *  Author: Hussain
 */ 

#include "common.h"
#include "uart.h"
#include <avr/io.h>


void init_UART(void )
{

  UCSRA = 0;
  UCSRB = 0;
  UCSRC = 0;
  
  ///Double Baud Rate
  UCSRA |= _BV(U2X);
  ///Enable Reception
  UCSRB |= _BV(RXEN) | _BV(TXEN);
  ///8-bit Data Byte, 2 Stop bits
  UCSRC |= _BV(USBS) | _BV(UCSZ1) | _BV(UCSZ0);
  ///Set Baud Rate to 9600
  UBRRL = 103;
  UBRRH = 0;
}

void transmit_UART(uint8_t data)
{
  //* Wait for empty transmit buffer 
  while ( !(UCSRA & (_BV(UDRE))) );
  //* Start transmission
  UDR = data;
}

uint8_t receive_UART(void)
{
  while ((UCSRA & (1 << RXC)) == 0);
  return UDR;
}

void transmit_string_UART(char *buffer)
{
  	uint16_t i = 0;
  	///Loop through the data
  	while(buffer[i] != '\0')
  	{
    	///* Wait for empty transmit buffer 
    	while ( !(UCSRA & (_BV(UDRE))) );
    	///* Start transmission
    	UDR = buffer[i];
		i++;	
	}
}

