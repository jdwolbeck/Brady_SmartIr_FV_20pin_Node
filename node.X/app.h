#ifndef _APP_H
#define _APP_H


#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

        
        typedef enum
        {
            LED1 = 0x8000,
            ADC1_EN = 0x0010, // mux control RB4
                    
        }APP_VARS;
        
        
typedef struct //
{
    uint16_t tempConversion; 
    uint16_t liteConversion; 
    uint16_t soilConversion; 
    uint16_t timer; 
    uint16_t ms; 
    uint16_t seconds;
    uint8_t U2RxByte;
    bool sampleFlag;
    
} APP_DATA;

extern APP_DATA appData;

    void application_init(void);
    extern bool getConversions(void);
    extern void set_vREFplus(uint8_t);
    extern void set_vREFmins(uint8_t);   
    void ms_delay(uint16_t);
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */