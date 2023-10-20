#include "main.h"



//unsigned char MotorFlag;  //未定义的全局变量，由键盘控制
unsigned char code F_Rotation[4]={0x8F,0x97,0xA7,0xC7}; //正转表格，换算成二进制 1000 1111，1001 0111，1010 0111，1100 0111
unsigned char code B_Rotation[4]={0xC7,0xA7,0x97,0x8F}; //反转表格，换算成二进制 1100 0111，1010 0111，1001 0111，1000 1111



/******************************************************************
*两个延时函数
******************************************************************/
void Delay1(unsigned int i)//延时
{
 while(i--);
}


void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

/******************************************************************
*函数：Motor
*功能：根据MotorFlag参数判断电机运动状态
*      MotorFlag=0  电机暂停
*      MotorFlag=1  电机正转
*      MotorFlag=2  电机反转
******************************************************************/

uint Motor_F(uint x)  //拉开
{
	 unsigned char i;
  unsigned int x1;
	x1=x;
	 for(x;x>0;x--){
      for(i=0;i<4;i++)      //4相
        { 
       P1=F_Rotation[i];  //输出对应的相 可以自行换成反转表格
       Delay1(500);        //改变这个参数可以调整电机转速 ,数字越小，转速越大
	    }
    }
	 return (x1/6);

}



uint Motor_B(uint x) //关闭
{
	unsigned char i;
  unsigned int x1;
	x1=x;
 for(x;x>0;x--){
	     for(i=0;i<4;i++)      //4相
         {
         P1=B_Rotation[i];  //输出对应的相 可以自行换成反转表格
         Delay1(500);        //改变这个参数可以调整电机转速 ,数字越小，转速越大
	     }
	   }
 return (x1/6);
}



