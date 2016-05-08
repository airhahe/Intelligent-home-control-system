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
 int default_code1 =1,default_code2= 2,default_code3= 3,default_code4 =4;//Ä¬ÈÏÃÜÂë£º1£¬2£¬3£,4
 unsigned char KeyValue=1;                                               //°´¼üÖµ
 
 /**************
 *function:init  of enter code
 *parm@
 *name:Code_setting
 **************/
 
void Code_setting(void)
{
	Tix_init();				//ÊäÈëÌáÊ¾ÐÅÏ¢
	Code_Input();			//ÃÜÂëÊäÈëÒÔÅÐ¶Ï
}

/****************
*function:the tix of input
*parm@
*name:Tix_init
*****************/

void Tix_init(void)
{
	int j=0,i=0;
	LCD12864_WriteCmd(0x01);       //ÇåÆÁ³õÊ¼»¯
	
	LCD12864_SetWindow(0, 0);      //ÏÔÊ¾ÔÚµÚÒ»ÐÐ£º»¶Ó­Ê¹ÓÃ±¾ÏµÍ³
	while(tpm[i]!='\0')       
	{
		LCD12864_WriteData(tpm[i]);
		i++;
	}
		tmpchange();
  	Dis_Number(tmp());
	LCD12864_SetWindow(1, 0);      //ÏÔÊ¾ÔÚµÚ¶þÐÐ£ºµ±Ç°×´Ì¬£º
	i=0;                           //±êÖ¾Î»ÖÃÎ»
	while(LCD_Init_word[i]!='\0')
	{
		LCD12864_WriteData(LCD_Init_word[i]);
		i++;
	}
	i=0;
	while(status_safety[i]!='\0')   //×´Ì¬£º°²È«
	{
		LCD12864_WriteData(status_safety[i]);
		i++;
	}
	LCD12864_SetWindow(2, 0);//ÏÔÊ¾ÔÚµÚÈýÐÐ£ºÌáÊ¾ÊäÈëÃÜÂë£º
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
	int Key1=0,Key2=0,Key3=0,Key4=0,i=0;//°´¼üÖµ³õÊ¼»¯
	flag_1=1;                           //±êÖ¾ÖÃ1½øÈëÃÜÂëÊäÈë
	while(1)
			{	
				LCD12864_WriteCmd(0x98);
				Key1=	KeyDown();                //µÚÒ»¸öÃÜÂëÖµ
				LCD12864_WriteData(Key1+0x30);
				if(flag==1)  break;             //ÖÐ¶ÏÐÞ¸Ä£¬½øÈëÏÂÒ»¸öÃÜÂëµÄÉèÖÃ
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x99);
				Key2=	KeyDown();               //µÚ¶þ¸öÃÜÂëÖµ
				LCD12864_WriteData(Key2+0x30);
				if(flag==1)  break;											//ÖÐ¶ÏÐÞ¸Ä£¬½øÈëÏÂÒ»¸öÃÜÂëµÄÉèÖÃ
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
		if((Key1==default_code1)&&(Key2==default_code2)&&(Key3==default_code3)&&(Key4==default_code4))	//ÊäÈëÃÜÂëºÍ³õÊ¼»¯ÃÜÂë£¨1234£©Ò»Ñù£¬½øÈëÃÜÂëÉèÖÃ×´Ì¬
		{
			Code_SET();													//½øÈëÃÜÂëÉèÖÃ×´Ì¬
			LCD12864_WriteCmd(0x01);    
		  LCD12864_WriteCmd(0x91);
			
			while(success[i]!='\0')							//ÏÔÊ¾ÃÜÂëÉèÖÃ³É¹¦
			{
				LCD12864_WriteData(success[i]);
				i++;
			}
			Delay(50);	
			DIS_Default(); 										//»Ö¸´³õÊ¼»¯ÏÔÊ¾
		}
			else
		{
				Vioce_lasting=1;//ÃÜÂëÊäÈë´íÎó£¬³ÖÐø±¨¾¯
				led=1;
				LCD12864_WriteCmd(0x01);    
				LCD12864_WriteCmd(0x92); 
				while(warming_t[i]!='\0')       //ÏÔÊ¾¾¯¸æÌáÊ¾£ºÇëÀë¿ª£¡
				{
					LCD12864_WriteData(warming_t[i]);
					i++;
				}		
				Delay(50);	
				DIS_Default();          //»Ö¸´³õÊ¼»¯ÏÔÊ¾
		}
				flag=0;
				flag_1=0;        //ÖÃÎ»±êÖ¾Î»
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
				default_code1=	KeyDown();//µÚÒ»¸öÃÜÂëÉèÖÃ
				LCD12864_WriteData(default_code1+0x30);
				if(flag==1)  break;
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x99);
				default_code2=	KeyDown();//µÚ¶þ¸öÃÜÂëÉèÖÃ
				LCD12864_WriteData(default_code2+0x30);
				if(flag==1)  break;
			}
			flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x9a);
				default_code3=KeyDown();//µÚÈý¸öÃÜÂëÉèÖÃ
				LCD12864_WriteData(default_code3+0x30);
				if(flag==1)   break;
			}
				flag=0;
			while(1)
			{	
				LCD12864_WriteCmd(0x9b);
				default_code4=KeyDown();//µÚËÄ¸öÃÜÂëÉèÖÃ
				LCD12864_WriteData(default_code4+0x30);
				if(flag==1)   break;
			}
				
			flag_1=0;
			flag=0;										//Çå³ý±êÖ¾Î»
     
}

void Delay(unsigned int  x)   //¼òµ¥µÄÑÓÊ±
{
    unsigned char a,b,c;
    for(c=1000;c>0;c--)
        for(b=38;b>0;b--)
            for(a=x;a>0;a--);
}



