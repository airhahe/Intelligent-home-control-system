#ifndef __LCD12864_H
#define __LCD12864_H

//---����ͷ�ļ�---//
#include<reg52.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif


//---����ʹ�õ�IO��---//

#define LCD12864_DATAPORT P0	  //����IO��

sbit LCD12864_RS  =  P3^5;             //����������Ĵ���ѡ������ 
sbit LCD12864_RW  =  P3^6;             //Һ����/д����
sbit LCD12864_EN  =  P3^4;             //Һ��ʹ�ܿ���
sbit LCD12864_PSB =  P3^7;             //��/����ʽ����
sbit LCD12864_RST =  P3^4;			   //��λ��


//---����ȫ�ֺ���---//
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
