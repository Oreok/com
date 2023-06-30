#ifndef COM_H
#define COM_H

#include <stdint.h> // Int-Typen bestimmter Größe (z.B. uint8_t)
#include <avr/io.h> // I/O-Register
#include <util/delay.h>


void sendOutput(char text[], uint32_t value);

void putChar(unsigned char data);

void putString(unsigned char* data);

void putDec(int32_t value);

void putDecT(int32_t number);

void USART_init();

#endif 
