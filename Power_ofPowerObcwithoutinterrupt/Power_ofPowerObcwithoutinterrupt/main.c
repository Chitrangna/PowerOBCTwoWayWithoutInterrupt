/*
 * Power--OBCm-Power.c
 *
 * Created: 01-08-2017 21:46:08
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
    init_UART();
	TWI_init_slave();
    // Variables
    
    //sei();
		
    while (1) 
    {
		uint8_t data= TWI_read_data_slave();
		transmit_UART(data);
		_delay_ms(100);	
		TWI_write_data_slave(data);	//contains checking of whether it is being addressed
    }
}

