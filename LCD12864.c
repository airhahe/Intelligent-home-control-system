#include "lcd12864.h"
#include "18B20.h"

 unsigned char code LCD_Init_word[]="��ʼ����";
 unsigned char code status_safety[]="����";
 unsigned char code status_warming[]="Σ�գ�";
 unsigned char code Input_Tix[]="���������룺";
 unsigned char code Tix_warming[]="�����������";
 unsigned char code Enter_Key_tix[]="������������״̬�밴����SW7";
 unsigned char code success[]="�������óɹ���";
 unsigned char code warming_t[]="���뿪��";
  unsigned char code tpm[]="�¶�ֵ��";
	
/*******************************************************************************
* �� �� ��         : LCD12864_Delay1ms
* ��������		   : ��ʱ1MS
* ��    ��         : c
* ��    ��         : ��
*******************************************************************************/

void LCD12864_Delay1ms(uint c)
{
    uchar a,b;
	for(; c>0; c--)
	{
	    for(b=199; b>0; b--)
		{
	        for(a=1; a>0; a--);
		}
	}
}

/*******************************************************************************
* �� �� ��         : LCD12864_Busy
* ��������		   : ���LCD�Ƿ�æ
* ��    ��         : ��
* ��    ��         : 1��0��1��ʾ��æ��0��ʾæ��
*******************************************************************************/

uchar LCD12864_Busy(void)
{
	uchar i = 0;

	LCD12864_RS = 0;   	//ѡ������
	LCD12864_RW = 1;	//ѡ���ȡ

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);

	while((LCD12864_DATAPORT & 0x80) == 0x80)	//����ȡ����ֵ
	{
		i++;
		if(i > 100)
		{
			LCD12864_EN = 0;
			return 0;	   //�����ȴ�ʱ�䷵��0��ʾʧ��
		}
	}

	LCD12864_EN = 0;

	return 1;
}

/*******************************************************************************
* �� �� ��         : LCD12864_WriteCmd
* ��������		   : д����
* ��    ��         : cmd
* ��    ��         : ��
*******************************************************************************/

void LCD12864_WriteCmd(uchar cmd)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if( i>100)
		{
			return;	   //�����ȴ��˳�
		}	
	}
	
	LCD12864_RS = 0;     //ѡ������
	LCD12864_RW = 0;     //ѡ��д��
	LCD12864_EN = 0;     //��ʼ��ʹ�ܶ�

	LCD12864_DATAPORT = cmd;   //��������

	LCD12864_EN = 1;		   //дʱ��
	LCD12864_Delay1ms(5);
	LCD12864_EN = 0;    					
}

/*******************************************************************************
* �� �� ��         : LCD12864_WriteData
* ��������		   : д����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/

void LCD12864_WriteData(uchar dat)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if( i>100)
		{
			return;	   //�����ȴ��˳�
		}	
	}

	LCD12864_RS = 1;     //ѡ������
	LCD12864_RW = 0;     //ѡ��д��
	LCD12864_EN = 0;     //��ʼ��ʹ�ܶ�

	LCD12864_DATAPORT = dat;   //��������

	LCD12864_EN = 1;		   //дʱ��
	LCD12864_Delay1ms(5);
	LCD12864_EN = 0;    								
}

/*******************************************************************************
* �� �� ��         : LCD12864_ReadData
* ��������		   : ��ȡ����
* ��    ��         : ��
* ��    ��         : ��ȡ����8λ����
*******************************************************************************/
#ifdef LCD12864_PICTURE

uchar LCD12864_ReadData(void)
{
	uchar i, readValue;

	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if( i>100)
		{
			return 0;	   //�����ȴ��˳�
		}	
	}

	LCD12864_RS = 1;       //ѡ������
	LCD12864_RW = 1;
	LCD12864_EN = 0;
	LCD12864_Delay1ms(1);  //�ȴ�

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);
	readValue = LCD12864_DATAPORT;
	LCD12864_EN = 0;

	return readValue;
}

#endif

/*******************************************************************************
* �� �� ��         : LCD12864_Init
* ��������		   : ��ʼ��LCD12864
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void LCD12864_Init()
{
	LCD12864_PSB = 1;	  //ѡ��������
	LCD12864_RST = 1;	  //��λ

	LCD12864_WriteCmd(0x30);  //ѡ�����ָ�����
	LCD12864_WriteCmd(0x0c);  //��ʾ�����ع��
	LCD12864_WriteCmd(0x01);  //���LCD12864����ʾ����
}

/*******************************************************************************
* �� �� ��         : LCD12864_SetWindow
* ��������		   : �����ڻ���ָ��ģʽ��������ʾ���ꡣע�⣺x�������У�y��������
* ��    ��         : x, y
* ��    ��         : ��
*******************************************************************************/

void LCD12864_SetWindow(uchar x, uchar y)
{
	uchar pos;

	if(x == 0)	   // ��һ�еĵ�ַ��80H
	{
		x = 0x80;
	}
		
	else if(x == 1)  //�ڶ��еĵ�ַ��90H
	{
		x = 0x90;	
	}
	
	else if(x == 2)  //�����еĵ�ַ��88H
	{
		x = 0x88;
	}
	
	else if(x == 3)
	{
		x = 0x98;
	}
	
	pos = x + y;
	LCD12864_WriteCmd(pos);
}


/*******************
*funtion:The default display of lcd12864
*parm@
*name:DIS_Default
********************/
void DIS_Default(void)
{
	int i=0;
	LCD12864_WriteCmd(0x01);       //������ʼ��
	LCD12864_SetWindow(0, 0);      //��ʾ�ڵ�һ�У���ӭʹ�ñ�ϵͳ
	while(tpm[i]!='\0')       
	{
		LCD12864_WriteData(tpm[i]);
		i++;
	}
	LCD12864_SetWindow(1, 0);      //��ʾ�ڵڶ��У���ǰ״̬��
	i=0;                           //��־λ��λ
	while(LCD_Init_word[i]!='\0')
	{
		LCD12864_WriteData(LCD_Init_word[i]);
		i++;
	}
	i=0;
	while(status_safety[i]!='\0')   //״̬����ȫ
	{
		LCD12864_WriteData(status_safety[i]);
		i++;
	}
	
	LCD12864_SetWindow(2, 0);
	i=0;
	while(Enter_Key_tix[i]!='\0')//������ʾ��������������״̬�밴����1
	{
		
		LCD12864_WriteData(Enter_Key_tix[i]);
		i++;
		if(i==16)
		LCD12864_WriteCmd(0X98);
	}
}
/********************
*function:Number display
*parm@      uint Num:number display parm
*name:Dis_Number
*********************/

void Dis_Number(uint Num)
{
	int TEN=0,BITS=0;
	TEN=Num/100;                    //ʮλ
	BITS=Num%100/10;                //��λ
	LCD12864_WriteCmd(0x84);				//��ʾλ��
	LCD12864_WriteData(TEN+0x30);   //��ʾ��λ
	LCD12864_WriteData(BITS+0x30);  //��ʾʮλ
	
}



