#include <avr/io.h>
#include <string.h>
#include "main.h"
#include "usart.h"

//USART, for Transmit, Recieve, and Init

volatile char messageIn[MAX_MESSAGE];
volatile unsigned int counterIn = 0;

volatile char messageOut[MAX_MESSAGE];
int stringLength = 0;
volatile unsigned int counterOut = 0;
volatile char transmitterBusy = 0;
char str1[]="Sample string";


void USART_Init( unsigned int ubrr)
{
 /*Set baud rate */
 UBRR0H = (unsigned char)(ubrr>>8);
 UBRR0L = (unsigned char)ubrr;
 /*Enable receiver and transmitter*/
 UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
 /* Set frame format: 8data, 2stop bit */
 UCSR0C = (3<<UCSZ00);
 UCSR0A &= ~(1<<U2X0);
 
}

void printUART(char* str){
	if(!transmitterBusy){
		counterOut = 0;
		stringLength = strlen(str1);
		if(stringLength > MAX_MESSAGE){
			strncpy(messageOut, str, MAX_MESSAGE);		
		}
		else{
			strcpy(messageOut, str1);
		}
			UDR0 = messageOut[counterOut++];
			transmitterBusy = 1;
	}
}

// void USART_Transmit( unsigned char data )
// {
//  /* Wait for empty transmit buffer */
//  while ( !( UCSR0A & (1<<UDRE0)) );
//  /* Put data into buffer, sends the data */
//  UDR0 = data;
// }

// unsigned char USART_Receive( void )
// {
//  /* Wait for data to be received */
//  while ( !(UCSR0A & (1<<RXC0)) );
//  /* Get and return received data from buffer */
//  return UDR0;
// }

