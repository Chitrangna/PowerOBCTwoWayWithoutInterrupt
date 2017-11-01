/*
 * OBCm--OBCm-Power.c
 *
 * Created: 01-08-2017 21:45:03
 * Author : Chitrangna Bhatt
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include "common.h"
#include "uart.h"
#include "i2c.h"

int main(void)
{
	// Initializations 
	init_UART0();
	TWI_init_master();
	// Variables 
	DDRA = 0xF0;//defining these pins as output//four msb are on the master's side
	
	//sei();
	
    while (1) 
    {
		
		//uint8_t data=receive_UART0();
		uint8_t data='5';
		//uint8_t final;
		TWI_start();
		TWI_write_address_mt(0x20);
		TWI_write_data(data);
		_delay_ms(100);
		//TWI_stop();//could try repeat start condition
		//TWI_start();
		TWI_repeated_start();
		PORTA=0x10;
		TWI_write_address_mr(0x21);
		PORTA=0x20;
		uint8_t final = TWI_read_data();
		PORTA=0x40;
		_delay_ms(100);
		TWI_stop();
		PORTA=0xF0;
		transmit_UART0(final);
		
    }
}

