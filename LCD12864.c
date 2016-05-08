#include "lcd12864.h"
#include "18B20.h"

 unsigned char code LCD_Init_word[]="初始化：";
 unsigned char code status_safety[]="正常";
 unsigned char code status_warming[]="危险！";
 unsigned char code Input_Tix[]="请输入密码：";
 unsigned char code Tix_warming[]="密码输入错误！";
 unsigned char code Enter_Key_tix[]="进入密码设置状态请按按键SW7";
 unsigned char code success[]="密码设置成功！";
 unsigned char code warming_t[]="请离开！";
  unsigned char code tpm[]="温度值：";
	
/*******************************************************************************
* 函 数 名         : LCD12864_Delay1ms
* 函数功能		   : 延时1MS
* 输    入         : c
* 输    出         : 无
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
* 函 数 名         : LCD12864_Busy
* 函数功能		   : 检测LCD是否忙
* 输    入         : 无
* 输    出         : 1或0（1表示不忙，0表示忙）
*******************************************************************************/

uchar LCD12864_Busy(void)
{
	uchar i = 0;

	LCD12864_RS = 0;   	//选择命令
	LCD12864_RW = 1;	//选择读取

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);

	while((LCD12864_DATAPORT & 0x80) == 0x80)	//检测读取到的值
	{
		i++;
		if(i > 100)
		{
			LCD12864_EN = 0;
			return 0;	   //超过等待时间返回0表示失败
		}
	}

	LCD12864_EN = 0;

	return 1;
}

/*******************************************************************************
* 函 数 名         : LCD12864_WriteCmd
* 函数功能		   : 写命令
* 输    入         : cmd
* 输    出         : 无
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
			return;	   //超过等待退出
		}	
	}
	
	LCD12864_RS = 0;     //选择命令
	LCD12864_RW = 0;     //选择写入
	LCD12864_EN = 0;     //初始化使能端

	LCD12864_DATAPORT = cmd;   //放置数据

	LCD12864_EN = 1;		   //写时序
	LCD12864_Delay1ms(5);
	LCD12864_EN = 0;    					
}

/*******************************************************************************
* 函 数 名         : LCD12864_WriteData
* 函数功能		   : 写数据
* 输    入         : dat
* 输    出         : 无
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
			return;	   //超过等待退出
		}	
	}

	LCD12864_RS = 1;     //选择数据
	LCD12864_RW = 0;     //选择写入
	LCD12864_EN = 0;     //初始化使能端

	LCD12864_DATAPORT = dat;   //放置数据

	LCD12864_EN = 1;		   //写时序
	LCD12864_Delay1ms(5);
	LCD12864_EN = 0;    								
}

/*******************************************************************************
* 函 数 名         : LCD12864_ReadData
* 函数功能		   : 读取数据
* 输    入         : 无
* 输    出         : 读取到的8位数据
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
			return 0;	   //超过等待退出
		}	
	}

	LCD12864_RS = 1;       //选择命令
	LCD12864_RW = 1;
	LCD12864_EN = 0;
	LCD12864_Delay1ms(1);  //等待

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);
	readValue = LCD12864_DATAPORT;
	LCD12864_EN = 0;

	return readValue;
}

#endif

/*******************************************************************************
* 函 数 名         : LCD12864_Init
* 函数功能		   : 初始化LCD12864
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void LCD12864_Init()
{
	LCD12864_PSB = 1;	  //选择并行输入
	LCD12864_RST = 1;	  //复位

	LCD12864_WriteCmd(0x30);  //选择基本指令操作
	LCD12864_WriteCmd(0x0c);  //显示开，关光标
	LCD12864_WriteCmd(0x01);  //清除LCD12864的显示内容
}

/*******************************************************************************
* 函 数 名         : LCD12864_SetWindow
* 函数功能		   : 设置在基本指令模式下设置显示坐标。注意：x是设置行，y是设置列
* 输    入         : x, y
* 输    出         : 无
*******************************************************************************/

void LCD12864_SetWindow(uchar x, uchar y)
{
	uchar pos;

	if(x == 0)	   // 第一行的地址是80H
	{
		x = 0x80;
	}
		
	else if(x == 1)  //第二行的地址是90H
	{
		x = 0x90;	
	}
	
	else if(x == 2)  //第三行的地址是88H
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
	LCD12864_WriteCmd(0x01);       //清屏初始化
	LCD12864_SetWindow(0, 0);      //显示在第一行：欢迎使用本系统
	while(tpm[i]!='\0')       
	{
		LCD12864_WriteData(tpm[i]);
		i++;
	}
	LCD12864_SetWindow(1, 0);      //显示在第二行：当前状态：
	i=0;                           //标志位置位
	while(LCD_Init_word[i]!='\0')
	{
		LCD12864_WriteData(LCD_Init_word[i]);
		i++;
	}
	i=0;
	while(status_safety[i]!='\0')   //状态：安全
	{
		LCD12864_WriteData(status_safety[i]);
		i++;
	}
	
	LCD12864_SetWindow(2, 0);
	i=0;
	while(Enter_Key_tix[i]!='\0')//按键提示：进入密码设置状态请按按键1
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
	TEN=Num/100;                    //十位
	BITS=Num%100/10;                //个位
	LCD12864_WriteCmd(0x84);				//显示位置
	LCD12864_WriteData(TEN+0x30);   //显示个位
	LCD12864_WriteData(BITS+0x30);  //显示十位
	
}



