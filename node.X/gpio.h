#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include <stdbool.h>

void GPIO_enable(uint16_t);
void GPIO_lo( uint16_t );
void GPIO_hi( uint16_t );

#endif //_GPIO_H
