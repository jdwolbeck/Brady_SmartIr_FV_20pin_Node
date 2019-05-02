 #include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app.h"
#include "system.h"
#include "adc1.h"
#include "uart.h"
#include "gpio.h"

/**********************************************************
 * 
 * APP Macros
 * 
*************************************************************/

// SAMPLE_FRQ = 1, = 1 SECOND; 
#define SAMPLE_FRQ 5
#define SAMPLES_PER 1

/**********************************************************
 * 
 * APP functions
 * 
*************************************************************/
void application_init(void);
bool getConversions(void);
void timer_init(void);
void ms_delay(uint16_t);

/**********************************************************
 * 
 * APP variables
 * 
*************************************************************/
APP_VARS app_vars;
APP_DATA appData;
uint16_t ticker = 0;
uint16_t num_samples_taken =0;


void application_init(void)
{
    timer_init();
    ADC1_init();
    uart_init();          
    GPIO_enable(0x0380);
    TRISAbits.TRISA2 = 0;
    ANSAbits.ANSA2 = 0;
    appData.ms = 0;
    appData.seconds = 0;
    appData.sampleFlag = false;
    appData.U2RxByte = 0x30;
}


bool getConversions(void)
{
    GPIO_hi(A);
        
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

void timer_init(void)
{

    TMR1 = 0x0000;     
    T1CON = 0x8000;
    PR1 = 0x0185;
    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;     
    T1CONbits.TON = 0;     
}

/* Timer 1 ISR */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    
    IFS0bits.T1IF = 0;
    TMR1 = 0x0000;    
    ticker++;
    
    // counts seconds
    if ( ticker%10000 == 0 )       
    {  
        (appData.seconds == 59)? (appData.seconds=0): (appData.seconds++);
        appData.ms = 0;
        ticker = 0;  
        appData.sampleFlag = true;      
    }
    
    // counts milliseconds
    if ( ticker%10 == 0 )
    {
        (appData.ms==999)? appData.ms=0: appData.ms++;        
    }
    
}

void ms_delay(uint16_t msVal)
{
    int i =0, j = 0;
    for(i = msVal; i>0 ; i-- ){
   for( j=4000; j>0 ; j-- ); 
    }
}


