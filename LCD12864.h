#ifndef __LCD12864_H
#define __LCD12864_H

//---包含头文件---//
#include<reg52.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif


//---定义使用的IO口---//

#define LCD12864_DATAPORT P0	  //数据IO口

sbit LCD12864_RS  =  P3^5;             //（数据命令）寄存器选择输入 
sbit LCD12864_RW  =  P3^6;             //液晶读/写控制
sbit LCD12864_EN  =  P3^4;             //液晶使能控制
sbit LCD12864_PSB =  P3^7;             //串/并方式控制
sbit LCD12864_RST =  P3^4;			   //复位端


//---声明全局函数---//
void LCD12864_Delay1ms(uint c);
uchar LCD12864_Busy(void);
void LCD12864_WriteCmd(uchar cmd);
void LCD12864_WriteData(uchar dat);
void LCD12864_Init();
void LCD12864_ClearScreen(void);
void LCD12864_SetWindow(uchar x, uchar y);
void LCD_Play(int Status,int input_warming );
void DIS_Default(void);
void Dis_Number(uint Num);

#endif
