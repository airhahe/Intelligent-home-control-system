#include "Code_Setting.h"
#include "lcd12864.h"
#include "Key.h"
#include "18B20.h"

 extern unsigned char code LCD_Init_word[];
 extern unsigned char code status_safety[];
 extern unsigned char code status_warming[];
 extern unsigned char code Input_Tix[];
 extern unsigned char code Tix_warming[];
 extern unsigned char code Enter_Key_tix[];
 extern unsigned char code success[];
 extern unsigned char code warming_t[];
 extern unsigned char code tpm[];
 
 extern int flag,flag_1;
 int default_code1 =1,default_code2= 2,default_code3= 3,default_code4 =4;//Ĭ�����룺1��2��3�,4
 unsigned char KeyValue=1;                                               //����ֵ
 
 /**************
 *function:init  of enter code
 *parm@
 *name:Code_setting
 **************/
 
void Code_setting(void)
{
	Tix_init();				//������ʾ��Ϣ
	Code_Input();			//�����������ж�
}

/****************
*function:the tix of input
*parm@
*name:Tix_init
*****************/

void Tix_init(void)
{
	int j=0,i=0;
	LCD12864_WriteCmd(0x01);       //������ʼ��
	
	LCD12864_SetWindow(0, 0);      //��ʾ�ڵ�һ�У���ӭʹ�ñ�ϵͳ
	while(tpm[i]!='\0')       
	{
		LCD12864_WriteData(tpm[i]);
		i++;
	}
		tmpchange();
  	Dis_Number(tmp());
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
	LCD12864_SetWindow(2, 0);//��ʾ�ڵ����У���ʾ�������룺
	while(Input_Tix[j]!='\0')
	{
		LCD12864_WriteData(Input_Tix[j]);
		j++;
	}
}

/********
*function:code input and judge
*parm@
*name:Code_Input
********/

void Code_Input(void)
{
	int Key1=0,Key2=0,Key3=0,Key4=0,i=0;//����ֵ��ʼ��
	flag_1=1;                           //��־��1������������
	while(1)
			{	
				LCD12864_WriteCmd(0x98);
				Key1=	KeyDown();                //��һ������ֵ
				LCD12864_WriteData(Key1+0x30);
				if(flag==1)  break;             //�ж��޸ģ�������һ�����������
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x99);
				Key2=	KeyDown();               //�ڶ�������ֵ
				LCD12864_WriteData(Key2+0x30);
				if(flag==1)  break;											//�ж��޸ģ�������һ�����������
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x9a);
				Key3=	KeyDown();
				LCD12864_WriteData(Key3+0x30);
				if(flag==1)   break;
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x9b);
				Key4=	KeyDown();
				LCD12864_WriteData(Key4+0x30);
				if(flag==1)   break;
			}
			flag=0;
		if((Key1==default_code1)&&(Key2==default_code2)&&(Key3==default_code3)&&(Key4==default_code4))	//��������ͳ�ʼ�����루1234��һ����������������״̬
		{
			Code_SET();													//������������״̬
			LCD12864_WriteCmd(0x01);    
		  LCD12864_WriteCmd(0x91);
			
			while(success[i]!='\0')							//��ʾ�������óɹ�
			{
				LCD12864_WriteData(success[i]);
				i++;
			}
			Delay(50);	
			DIS_Default(); 										//�ָ���ʼ����ʾ
		}
			else
		{
				Vioce_lasting=1;//����������󣬳�������
				led=1;
				LCD12864_WriteCmd(0x01);    
				LCD12864_WriteCmd(0x92); 
				while(warming_t[i]!='\0')       //��ʾ������ʾ�����뿪��
				{
					LCD12864_WriteData(warming_t[i]);
					i++;
				}		
				Delay(50);	
				DIS_Default();          //�ָ���ʼ����ʾ
		}
				flag=0;
				flag_1=0;        //��λ��־λ
}
/******************
*function:code set
*parm@
*name:Code_SET
******************/

void Code_SET(void)
{
	flag_1=1;
	Tix_init();
	LCD12864_SetWindow(3, 0);
	flag=0;
	while(1)
			{	
				LCD12864_WriteCmd(0x98);
				default_code1=	KeyDown();//��һ����������
				LCD12864_WriteData(default_code1+0x30);
				if(flag==1)  break;
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x99);
				default_code2=	KeyDown();//�ڶ�����������
				LCD12864_WriteData(default_code2+0x30);
				if(flag==1)  break;
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x9a);
				default_code3=KeyDown();//��������������
				LCD12864_WriteData(default_code3+0x30);
				if(flag==1)   break;
			}
				flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x9b);
				default_code4=KeyDown();//���ĸ���������
				LCD12864_WriteData(default_code4+0x30);
				if(flag==1)   break;
			}
				
			flag_1=0;
			flag=0;										//�����־λ
     
}

void Delay(unsigned int  x)   //�򵥵���ʱ
{
    unsigned char a,b,c;
    for(c=1000;c>0;c--)
        for(b=38;b>0;b--)
            for(a=x;a>0;a--);
}



