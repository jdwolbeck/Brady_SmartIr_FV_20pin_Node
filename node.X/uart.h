#ifndef _UART_H
#define _UART_H

#include <stdbool.h>
#include <stdint.h>

#define MAX 40

extern char U2RxBuffer[MAX];
extern char U2TxBuffer[MAX];

extern void uart_init(void);
extern void uart_write_string(char[]);
extern void uart_print(char[]);

#endif //_UART_H  
