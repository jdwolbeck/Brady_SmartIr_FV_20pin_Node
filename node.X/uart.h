
#ifndef _UART_H
#define _UART_H

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

#define MAX 40

extern char U2RxBuffer[MAX];
extern char U2TxBuffer[MAX];

extern void uart_init(void);
extern void uart_write_string(char[]);
void uart_print(char[]);

#ifdef	__cplusplus
}
#endif
#endif //_UART_H
    
