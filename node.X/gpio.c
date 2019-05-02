#include <xc.h> 
#include <stdbool.h>
#include <stdint.h>
#include "app.h"
#include "gpio.h"

/**********************************************************
 * 
 * masks
 * 
*************************************************************/

#define ADC1_ENABLE 0x0010     // PORTB4
#define LED1        0x8000     // PORTB15

void GPIO_enable( uint16_t );
void GPIO_lo( uint16_t );
void GPIO_hi( uint16_t );

void GPIO_enable( uint16_t portSelect )
{   
    switch( portSelect )
    {
        case LED1 :
            ANSB &= ~(LED1);
            TRISB &= ~(LED1);
            LATB &= ~(LED1);
            break;
        case ADC1_ENABLE :
            ANSB &= ~(ADC1_ENABLE);
            TRISB &= ~(ADC1_ENABLE);
            LATB |= (ADC1_ENABLE);
            break;
            
        default:
            ANSB &= ~(portSelect);
            TRISB &= ~(portSelect);
            LATB |= (portSelect);            
            break;
    }
    
}

void GPIO_lo( uint16_t portSelect)
{
    LATB &= ~(portSelect);
}


void GPIO_hi( uint16_t portSelect )
{
    LATB |= (portSelect);    
}




