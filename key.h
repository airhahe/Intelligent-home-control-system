#ifndef __KEY_H
#define __KEY_H

#include <reg52.h>  
#define GPIO_KEY P1

int KeyDown(void);
void Delay10ms(void) ;   //—” ±10ms
extern  unsigned char KeyValue;

#endif
