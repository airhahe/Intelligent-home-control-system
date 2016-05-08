#include <reg52.h>  
#include "lcd12864.h"
#include "Code_Setting.h"
#include "18B20.h"


#define uchar unsigned char //�����ض���
#define uint  unsigned int 
#define ulong unsigned long 

uint flag_set=0;        //���ڽ�����������״̬�ı�־λ
int flag=0,flag_1=0;    //������������flag_1�ͱ�����־flag
sbit SMOKE = P2^6;
sbit LED0 = P3^2;


void INT1_Init(void);   //�жϳ�ʼ��


void main()
{
	LCD12864_Init();       //Һ������ʼ��
	INT1_Init();           //�ж�1�������������ý�����������״̬	
	DIS_Default();         //Һ������ʼ����ʾ


	while(1)
	{
		if(flag_set==1)
		{
				Code_setting();  //�����ж���������
				flag_set=0;			 //����������ñ�־λ
		}
		if(SMOKE == 1)
		{
			LED0 = 1;
		}else{
			LED0 = 0;
}
		if(Hot_f==1)
		{
		  led=1;							//����
			motor=0;						//����������
			Vioce=1;           //������������	
		}
		else
		{
		led=0;      				//�ص�
		motor=1;						//�������ر�
		Vioce=0;            //���뱨��״̬��������������	
			//GSM
		Vioce_lasting=0;    //�������������ر�
		}
		tmpchange();				//�����¶�ת��
  	Dis_Number(tmp());	//��ʾ�¶�
}
}

/*******
*function:Init of interrupt 1
*parm@
*
********/
void INT1_Init(void)
{
	EA=1;      //�����ж�
	EX1=1;     //���ж�1
	IT1=1;     //�½��ش�����ʽ
}

