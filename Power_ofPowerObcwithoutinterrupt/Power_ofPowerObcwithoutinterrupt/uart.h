/*
 * uart.h
 *
 * Created: 31-03-2012 14:39:20
 *  Author: Hussain
 */ 

/**
 * @file uart.h
 * @brief Contains the various pin/port definitions and procedures for uart.
 */

#ifndef UART_H_
#define UART_H_

#include "common.h"

void init_UART(void );

void transmit_UART(uint8_t data);

uint8_t receive_UART(void);

void transmit_string_UART(char *buffer);

#endif /* UART_H_ */