#ifndef __Code_setting_H
#define __Code_setting_H

//---����ͷ�ļ�---//
#include<reg52.h>

void Code_setting(void);
void Tix_init(void);
void Code_SET(void);
void Code_Input(void);
void Delay(unsigned int  x) ;

sbit Hot_f=P2^1;         //����
sbit motor=P2^3;         //������
sbit led=P2^0;           //��
sbit Vioce=P2^4;         //������������
sbit Code_set=P3^3;      //������������״̬������,�ж�1
sbit Vioce_lasting=P2^5; //������������

#endif