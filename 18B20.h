#ifndef __18B20_H
#define __18B20_H

#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
	
sbit DS=P2^2;           //define interface

uint tmp(void) ;
void tmpchange(void);
void tmpwritebyte(uchar dat);
uchar tmpread(void) ;
bit tmpreadbit(void) ;
void dsreset(void) ;
void DELA(uint count) ;

#endif
