#include "main.h"



//unsigned char MotorFlag;  //δ�����ȫ�ֱ������ɼ��̿���
unsigned char code F_Rotation[4]={0x8F,0x97,0xA7,0xC7}; //��ת���񣬻���ɶ����� 1000 1111��1001 0111��1010 0111��1100 0111
unsigned char code B_Rotation[4]={0xC7,0xA7,0x97,0x8F}; //��ת���񣬻���ɶ����� 1100 0111��1010 0111��1001 0111��1000 1111



/******************************************************************
*������ʱ����
******************************************************************/
void Delay1(unsigned int i)//��ʱ
{
 while(i--);
}


void delay1s(void)   //��� 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

/******************************************************************
*������Motor
*���ܣ�����MotorFlag�����жϵ���˶�״̬
*      MotorFlag=0  �����ͣ
*      MotorFlag=1  �����ת
*      MotorFlag=2  �����ת
******************************************************************/

uint Motor_F(uint x)  //����
{
	 unsigned char i;
  unsigned int x1;
	x1=x;
	 for(x;x>0;x--){
      for(i=0;i<4;i++)      //4��
        { 
       P1=F_Rotation[i];  //�����Ӧ���� �������л��ɷ�ת����
       Delay1(500);        //�ı�����������Ե������ת�� ,����ԽС��ת��Խ��
	    }
    }
	 return (x1/6);

}



uint Motor_B(uint x) //�ر�
{
	unsigned char i;
  unsigned int x1;
	x1=x;
 for(x;x>0;x--){
	     for(i=0;i<4;i++)      //4��
         {
         P1=B_Rotation[i];  //�����Ӧ���� �������л��ɷ�ת����
         Delay1(500);        //�ı�����������Ե������ת�� ,����ԽС��ת��Խ��
	     }
	   }
 return (x1/6);
}


