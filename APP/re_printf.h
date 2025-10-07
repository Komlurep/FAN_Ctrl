#ifndef __RE_PRINTF_H
#define __RE_PRINTF_H

#include "usart.h"
#include <stdio.h>

#ifdef __GNUC__
     #define PUTCHAR_PROTOTYPE int _io_putchar(int ch)
 #else
     #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
 #endif /* __GNUC__*/
 

int fputc(int ch, FILE *f);

#endif /* __RE_PRINTF_H */
