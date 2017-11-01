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

void TWI_start(void); //Function to send I2C start command

void TWI_repeated_start(void); // Function to send I2C repeated start command. Scarcely used

void TWI_write_address_mt(unsigned char data);//Function for Master side to send slave address for I2C for master transmitter

void TWI_write_address_mr(unsigned char data);//Function for Master side to send slave address for I2C for master receiver

void TWI_read_address(unsigned char data); //Function for slave side to read address sent by Master

void TWI_write_data(unsigned char data);//Function to write data on I2C data line

uint8_t TWI_read_data(void); //Function to read data from I2C data line

void TWI_stop(void);//Function to stop data transmission




#endif /* I2C_H_ */