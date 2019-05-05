#ifndef _ADC1_H
#define _ADC1_H

#include <stdbool.h>
#include <stdint.h>

typedef enum 
{
    // MUX channels
    A = 0x0080, // RB7 MUX PORT A, enable ADC periphrials
    B = 0x0100, // RB8 MUX PORT B, AD1CON2bits.PVCFG
    C = 0x0200, // RB9 MUX PORT C, AD1CON2bits.NVCFG
    ADC1_LITE = 0x9,
    ADC1_TEMP = 0xA,
    ADC1_SOIL = 0xB,
                   
} ADC1_CHANNEL;

extern void ADC1_init(void);
extern void ADC1_channelSelect( ADC1_CHANNEL channel );
extern uint16_t ADC1_getConversion( ADC1_CHANNEL channel );

#endif //_ADC1_H
