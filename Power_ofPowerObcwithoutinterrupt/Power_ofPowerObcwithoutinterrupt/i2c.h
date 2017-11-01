/*
 * i2c.h
 *
 * Created: 15-07-2017 21:32:06
 *  Author: Chitrangna Bhatt
 */ 

#include "common.h"


#ifndef I2C_H_
#define I2C_H_

void TWI_init_master(void); // Function to initialize master for I2C

void TWI_init_slave(void);//Function to initialize slave for I2C

void TWI_start(void); //Function to send I2C start command

void TWI_repeated_start(void); // Function to send I2C repeated start command. Scarcely used

void TWI_write_address(unsigned char data);//Function for Master side to send slave address for I2C

void TWI_read_address(unsigned char data); //Function for slave side to read address sent by Master

void TWI__slave_read_address(unsigned char data);//ST reading address on the line and confirming whether it is being addressed

void TWI_write_data(unsigned char data);//Function to write data on I2C data line

void TWI_write_data_slave(unsigned char data);//Function to check whether the slave is being addressed and send data on the line

void TWI_read_data(void); //Function to read data from I2C data line

uint8_t TWI_read_data_slave(void);//Function to make slave read the data when it is being addressed//address here is defined as 0x20

void TWI_stop(void);//Function to stop data transmission




#endif /* I2C_H_ */