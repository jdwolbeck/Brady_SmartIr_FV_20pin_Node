#include<xc.h>
#include "app.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MAX 40

char U2RxBuffer[MAX];
char U2TxBuffer[MAX];

void uart_init(void);    
void uart_write_byte(char);
void uart_write_string(char[]);
bool clearBuffer(void);


void uart_init(void){
/************************************************************
 * Configure UART 1 SFR's 
 ************************************************************/    
    // set pin direction 
    TRISBbits.TRISB0 = 0;   // TX
    TRISBbits.TRISB1 = 1;   // RX
    
    // set pins to digital
    ANSBbits.ANSB0 = 0;
    ANSBbits.ANSB1 = 0;
    LATBbits.LATB0 = 1;
    
    // disable UART
    U2MODE = 0x0000;

    // Baudrate = 9600;    clock 4MHz; U1BRG 103
    // Baudrate = 115200;  clock 4MHz; U1BRG 8
    U2MODEbits.BRGH = 1;
    U2STA = 0x0000;
    U2BRG = 103;
    IPC7bits.U2RXIP = 1;
    IEC1bits.U2RXIE = 1;         // Enable UART RX interrupt
    IFS1bits.U2RXIF = 0;        // clear flag  
    U2MODEbits.UARTEN = 1;       // Enable UART and wait to enable the TX
    U2STAbits.UTXEN = 1;         // enable Transmission

}

void uart_write_byte(char ch )
{
    U2TXREG  = ch;
}

void uart_print(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        while(!U1STAbits.TRMT);
        U1TXREG = str[i++];
    }
}

void uart_write_string(char buf[])
{
    int i = 0;
    
    while(buf[i] != '\0')
    {
     
        while(U2STAbits.UTXBF == 0)
        {
            uart_write_byte( buf[i] );
            i++;
        }
    }
    clearBuffer();
}

bool clearBuffer(void)
{
   int i = 0;
   
   for(i=0; i<MAX; i++) 
   {
       U2TxBuffer[i]='\0';
   }
    return 1;
    
} 


/* UART2 U2RX interrupt routine code */
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt( void )
{
    
    IFS1bits.U2RXIF = 0; // clear U12X flag 
    appData.U2RxByte = U2RXREG;
}
