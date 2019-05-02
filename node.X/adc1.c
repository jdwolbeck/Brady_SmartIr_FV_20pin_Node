#include <xc.h>
#include "app.h"
#include "adc1.h"
#include <stdbool.h>
#include <stdint.h>

#define ADC1_INPUTS 0xE000  // PORTB 13, 14, 15
#define MUX_BITS 0x0380 // PORTB 7, 8, 9 
#define MUX_PORT PORTB
/**********************************************************
 * 
 * ADC Driver functions
 * 
 *************************************************************/

void ADC1_init(void);
void ADC1_start(void);
void ADC1_stop(void);
bool ADC1_conversionComplete(void);
void ADC1_channelSelect(ADC1_CHANNEL);
uint16_t ADC1_getConversion(ADC1_CHANNEL);
void ADC1_vRefSelect(ADC1_CHANNEL);

uint16_t ctr = 0;

/****************************************************************
 * 
 * ADC1_Initialize must be call before all other ADC functions
 *  
 ***************************************************************/
void ADC1_init(void) {
    ANSB |= ADC1_INPUTS;
    TRISB |= ADC1_INPUTS;
    ANSB &= ~(MUX_BITS);
    TRISB |= ~(MUX_BITS);
    AD1CON3bits.ADCS = 0xFF;
    AD1CON3bits.SAMC = 0xF;
    AD1CON1bits.SSRC = 0x0;
    AD1CON1bits.FORM = 0;
    AD1CON2bits.SMPI = 0x0;
    
}

void ADC1_start(void) {
    AD1CON1bits.SAMP = 1;
    for (ctr = 1000; ctr > 0; ctr--);

}

void ADC1_stop(void) {
    AD1CON1bits.SAMP = 0;
}

bool ADC1_conversionComplete(void) {
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}

void ADC1_channelSelect(ADC1_CHANNEL channel) {
    AD1CHS = channel;
}

void ADC1_vRefSelect(ADC1_CHANNEL channel) {

    AD1CON1bits.ADON = 0;
    switch (channel) {

        case ADC1_LITE:
            AD1CON2bits.PVCFG = 0;
            AD1CON2bits.NVCFG = 0;
            break;

        case ADC1_TEMP:
            AD1CON2bits.PVCFG = 0b1;
            AD1CON2bits.NVCFG = 0b1;
            MUX_PORT |= (~B | ~C); // 1.75 - 0.1 volts per the MCP9700 data sheet
            break;

        case ADC1_SOIL:
            AD1CON2bits.PVCFG = 0b1;
            AD1CON2bits.NVCFG = 0b1;
            MUX_PORT |= (~B | C); //  1.75 - something via testing
            break;

        default:
            AD1CON2bits.PVCFG = 0b0;
            AD1CON2bits.NVCFG = 0b0;
            break;
    }


    AD1CON1bits.ADON = 1;
}

uint16_t ADC1_getConversion(ADC1_CHANNEL channel) {

    ADC1_vRefSelect(channel);

    ADC1_channelSelect(channel);

    ADC1_start();

    ADC1_stop();

    while (!ADC1_conversionComplete()) {
    }

    return ADC1BUF0;
}


/**
  End of File
 */
