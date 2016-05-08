#include"Key.h"
int KeyDown(void)
{
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//读取按键是否按下
	{
		Delay10ms();//延时10ms进行消抖
		if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
		{
		//	GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=1;break;
				case(0X0b):	KeyValue=2;break;
				case(0X0d): KeyValue=3;break;
				case(0X0e):	KeyValue=4;break;
			}
			//测试行
			GPIO_KEY=0xf0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+3;break;
				case(0Xd0): KeyValue=KeyValue+6;break;
				case(0Xe0):	KeyValue=0;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
			{
				Delay10ms();
				a++;
			}
		}
	}
	return KeyValue;
}

void Delay10ms(void)   //简单的延时
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}