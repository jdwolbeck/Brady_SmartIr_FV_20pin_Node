 #include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app.h"
#include "system.h"
#include "adc1.h"
#include "uart.h"
#include "gpio.h"

/************************************************************
 * 
 * APP functions
 * 
*************************************************************/
void application_init(void);
bool getConversions(void);
void ms_delay(uint16_t);

/************************************************************
 * 
 * APP variables
 * 
*************************************************************/
APP_DATA appData;


void application_init(void)
{
    ADC1_init();
    uart_init();          
    GPIO_enable(0x0380);
    appData.ms = 0;
    appData.seconds = 0;
    appData.U2RxByte = 0x30;
}


bool getConversions(void)
{
    uint16_t i;
    GPIO_hi(A);
    for( i = 100 ; i > 0 ; i-- );
    // soil moisture conversion
    appData.soilConversion = ADC1_getConversion(ADC1_SOIL);

    // photo sensor conversion
    appData.liteConversion = ADC1_getConversion(ADC1_LITE);           

    // temperature conversion
    appData.tempConversion = ADC1_getConversion(ADC1_TEMP);

    sprintf(U2TxBuffer,"%i,",(uint16_t)appData.soilConversion);
    uart_write_string(U2TxBuffer); 

    sprintf(U2TxBuffer,"%i,",(uint16_t)appData.liteConversion);   
    uart_write_string(U2TxBuffer);              

    sprintf(U2TxBuffer,"%i,",(uint16_t)appData.tempConversion);
    uart_write_string(U2TxBuffer);
    GPIO_lo(A);
   
    return true;
}

void ms_delay(uint16_t msVal)
{
    int i,j;
    for(i = msVal; i>0 ; i-- ){
        for( j=4000; j>0 ; j-- ); 
    }
}


