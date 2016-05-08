#ifndef __Code_setting_H
#define __Code_setting_H

//---包含头文件---//
#include<reg52.h>

void Code_setting(void);
void Tix_init(void);
void Code_SET(void);
void Code_Input(void);
void Delay(unsigned int  x) ;

sbit Hot_f=P2^1;         //热释
sbit motor=P2^3;         //蜂鸣器
sbit led=P2^0;           //灯
sbit Vioce=P2^4;         //语音操作引脚
sbit Code_set=P3^3;      //进入密码设置状态的引脚,中断1
sbit Vioce_lasting=P2^5; //持续语音播放

#endif