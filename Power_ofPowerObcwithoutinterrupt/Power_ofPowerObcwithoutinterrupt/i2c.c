/*
 * i2c.c
 *
 * Created: 15-07-2017 21:31:43
 *  Author: Chitrangna Bhatt
 */ 
#include <avr/io.h>
#include "i2c.h"
#include "common.h"


void TWI_init_master(void) // Function to initialize master for I2C
{
	//sei();

	TWSR = 0;
	TWCR = 0;
	TWBR = (F_CPU / 200000UL - 16) / 2; // Bit rate
	//TWSR=(0<<TWPS1)|(0<<TWPS0); // Setting prescalar bits
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)

}

void TWI_init_slave(void)
{
	TWAR = 0x20;		//initialised the address of the slave as 0x20//last bit is for recognition of general call address- has nothing to do with writing or reading- otherwise both wouldn't be possible together
	TWCR = (1<<TWEA)|(1<<TWEN)|(0<<TWSTO)|(0<<TWSTA);
}


void TWI_start(void) //Function to send I2C start command
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
	while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement
}

void TWI_repeated_start(void) // Function to send I2C repeated start command. Scarcely used
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // wait till restart condition is transmitted
	while((TWSR & 0xF8)!= 0x10); // Check for the acknoledgement
}

void TWI_write_address(unsigned char data)//Function for Master side to send slave address for I2C
{

	TWDR=data; // Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)))// Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8)!= 0x18);  // Check for the acknowledgement

}

void TWI_read_address(unsigned char data) //Function for slave side to read address sent by Master
{
	TWDR=data; // Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement
}

void TWI_write_data(unsigned char data)//Function to write data on I2C data line
{
	TWDR=data; // put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0xC0); // Check for the acknoledgement//0X28 INITIALLY
}

void TWI_read_data(void) //Function to read data from I2C data line
{
	char recv_data;
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
	recv_data=TWDR;//PORTA=recv_data;
	//if(UniversalCycles % CyclesToCollectData == 0){transmit_UART0(recv_data);}
	
}

//slave receiver code
uint8_t TWI_read_data_slave(void)
{
	begin:
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
		while (!(TWCR &(1<<TWINT)));
		switch(TWSR & 0xF8)	//check for whether it is being addressed
		{
			case 0x60 :
			break;

			default:
			goto begin;
		}
		
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN); 
		while (!(TWCR &(1<<TWINT)));

		switch(TWSR & 0xF8)				//checking for whether ack for data has been sent 
		{
		case 0x80 :
		break;
		
		default:
		goto begin;
		}
		uint8_t send;			 //data comes in twdr after twsr&o0f8 become 0x80
		send=TWDR;
		return send;
}



void TWI_write_data_slave(uint8_t data)		//being ST
{
	begin:
	//TWDR=0x21;//Dont know why??????????????
	//TWDR=0x21;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);//check with twea removed from here!!!!!!!!!!!!!
	while (!(TWCR &(1<<TWINT)));
	
	switch(TWSR & 0xF8)	//check for whether it is being addressed//doesnt need to check because repeatstart so master hasnt lost control over the line
	{			//working with right output isko comment out kare ya nahi
		case 0xA8 :
		case 0xB0 :
		break;

		default:
		goto begin;
	}
	TWDR=data;//before we enable twi bus twdr should be ready with the data// as soon as we enable data in twdr gets transferred
	TWCR = (1<<TWINT)|(1<<TWEN);//st so doesnt have to send ack//If the TWCR.TWEA bit is written to zero during a transfer, the TWI will transmit the last byte of the transfer.
	while (!(TWCR &(1<<TWINT)));
	
	switch(TWSR & 0xF8)				//checking for whether ack for data has been sent
	{			//works right when not commented out- comment out karne pe master gives the o/p as 21
		case 0xC0 :
		break;
		
		default:
		goto begin;
	}
	
	/*TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while (!(TWCR &(1<<TWINT)));
	TWDR=data;*/
}

void TWI_stop(void)//Function to stop data transmission
{
	// Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
}
