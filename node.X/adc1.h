#ifndef _ADC1_H
#define _ADC1_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/*
//   ADC1_SOIL_SENSOR = AN12, 0xB, RB13, pin 16
//   ADC1_TEMPERATURE = AN11, 0xA, RB14  pin 17
//   ADC1_PHOTORESISTOR = AN9, 0x9, RB15  pin 18
 */

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

/**
  Driver functions
*/

void ADC1_init(void);
void ADC1_start(void);
void ADC1_stop(void);
bool ADC1_conversionComplete(void);
void ADC1_Tasks(void);

void ADC1_channelSelect( ADC1_CHANNEL channel );
uint16_t ADC1_getConversion( ADC1_CHANNEL channel );

#ifdef	__cplusplus
}
#endif

#endif //_ADC1_H
    
/**
 End of File
*/
