#include <stdint.h> 
#include <avr/io.h> 
#include <stdio.h>

void putChar(unsigned char data) {
    while (( UCSR0A & (1<<UDRE0)) == 0) {}; 

    // load data into transmit register
    UDR0 = data;
}

void putString(unsigned char* data){
    int i = 0;
    while(data[i] != 0) {
        putChar(data[i]);
        i++;
    }
}

void putNewline() {
    putString("\n");
}

void putDecT(int32_t data) {
    char buffer[12]; 
    sprintf(buffer, "%ld", data); 
    
    for (int i = 0; buffer[i] != '\0'; i++) {
        putChar(buffer[i]);
    }
}

void putDec(uint32_t value) {
    uint32_t absValue = (value < 0) ? -value : value;  

    if (value < 0)
        putChar('-');  

    // Count the number of digits in the value
    uint8_t numDigits = 1;
    uint32_t temp = absValue;
    while (temp >= 10) {
        numDigits++;
        temp /= 10;
    }

    // Transmit each digit by extracting them from the value
    uint32_t divisor = 1;
    for (uint8_t i = 1; i < numDigits; ++i) {
        divisor *= 10;
    }

    for (uint8_t i = 0; i < numDigits; ++i) {
        uint8_t digit = absValue / divisor;
        putChar(digit + '0');
        absValue %= divisor;
        divisor /= 10;
    }
}

void USART_init() {
    //51 for 19200 BAUDRATE
    //set low bit
    UBRR0L = 51;
    //Set high bit
    UBRR0H = 51 >> 8;

    //Enable the Receiver and Transmitter 
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

