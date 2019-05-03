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

void GPIO_enable( uint16_t );
void GPIO_lo( uint16_t );
void GPIO_hi( uint16_t );

void GPIO_enable( uint16_t portSelect )
{   
            ANSB &= ~(portSelect);
            TRISB &= ~(portSelect);
    
}

void GPIO_lo( uint16_t portSelect)
{
    LATB &= ~(portSelect);
}


void GPIO_hi( uint16_t portSelect )
{
    LATB |= (portSelect);    
}




