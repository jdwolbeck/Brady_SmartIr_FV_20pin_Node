#include <xc.h>
#include "SPI.h"
#include "app.h"


void spi_init(void);
void spi_start(void);
void spi_transmit(uint8_t);
bool spi_ready(void);
void spi_stop(void);
void set_pot(uint8_t);

void spi_init(void){

    TRISB &= ~(0xF000);
    ANSB  &= ~(0x7000);
    LATB  |= (0x7000);    
    SPI1CON1bits.SMP = 0;
    SPI1CON1bits.CKP = 1;
    SPI1CON1bits.CKE = 1;
    SPI1CON1bits.MSTEN = 1;  
    SPI1STATbits.SPIROV =0;
    SPI1STATbits.SPIEN = 1;
}

void spi_start(void){
    LATBbits.LATB14 = 0;
}

void spi_transmit(uint8_t value)
{
SPI1BUF = value;
}
bool spi_ready(void){
    while(SPI1STATbits.SPITBF != 0)
    {}
    return true;
}
void spi_stop(void){
    LATBbits.LATB14 = 1;
}

void set_pot(uint8_t value)
{
    // first send the command to write
    spi_start();
    spi_transmit(0x11);
    spi_ready();
    spi_stop();
    // send the desired value
    spi_start();
    spi_transmit(value);
    spi_ready();
    spi_stop();    
    
}