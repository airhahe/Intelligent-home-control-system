#include <reg52.h>  
#include "lcd12864.h"
#include "Code_Setting.h"
#include "18B20.h"


#define uchar unsigned char //变量重定义
#define uint  unsigned int 
#define ulong unsigned long 

uint flag_set=0;        //用于进入密码设置状态的标志位
int flag=0,flag_1=0;    //按键密码设置flag_1和报警标志flag
sbit SMOKE = P2^6;
sbit LED0 = P3^2;


void INT1_Init(void);   //中断初始化


void main()
{
	LCD12864_Init();       //液晶屏初始化
	INT1_Init();           //中断1开启，用于设置进入密码设置状态	
	DIS_Default();         //液晶屏初始化显示


	while(1)
	{
		if(flag_set==1)
		{
				Code_setting();  //进入中断密码设置
				flag_set=0;			 //清除密码设置标志位
		}
		if(SMOKE == 1)
		{
			LED0 = 1;
		}else{
			LED0 = 0;
}
		if(Hot_f==1)
		{
		  led=1;							//开灯
			motor=0;						//蜂鸣器报警
			Vioce=1;           //播放语音报警	
		}
		else
		{
		led=0;      				//关灯
		motor=1;						//蜂鸣器关闭
		Vioce=0;            //进入报警状态，播放语音报警	
			//GSM
		Vioce_lasting=0;    //持续播放语音关闭
		}
		tmpchange();				//开启温度转换
  	Dis_Number(tmp());	//显示温度
}
}

/*******
*function:Init of interrupt 1
*parm@
*
********/
void INT1_Init(void)
{
	EA=1;      //开总中断
	EX1=1;     //打开中断1
	IT1=1;     //下降沿触发方式
}

