/*************************
版本1.0
仅实现显示字符的功能
*************************/


//#include "lcd12864.h"
//#include <reg52.h>
//#include <intrins.h>
#include "main.h"

//uchar code dis1[] = {"室内温度"};
//uchar code dis2[] = {"00"};
//uchar code dis3[] = {"室外光强"};
//uchar code dis4[] = {"00"};

//12864 IO端口定义
//#define LCD_data  P0             //数据口
//sbit LCD_RS  =  P3^5;            //寄存器选择输入 
//sbit LCD_RW  =  P3^6;            //液晶读/写控制
//sbit LCD_EN  =  P3^4;            //液晶使能控制
//sbit LCD_PSB =  P3^7;            //串/并方式控制
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;

void delay3(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<250;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}	


bit lcd_busy()
 { 
                           
    bit result;
    P0=0X00;              //关掉数码管的信号。阻止数码管受到P0口信号的影响
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
 
 
 
 
 
void lcd_wcmd(uchar cmd)
{   
                         
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}
 
 
 
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}


void lcd_init()
{ 

    LCD_PSB = 1;         //并口方式
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay3(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay3(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    delay3(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay3(5);
}
 
 
void delay0(uchar x)    //x*0.14MS
{
  uchar i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}
 
 
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   lcd_wcmd(pos);     //显示地址
}
 
 
//void lcd_drive()
//{
//	 uchar i;
//   delay3(10);                 //延时
//   wela=0;
//	 dula=0; 
//   lcd_init();                //初始化LCD             
//  
//    lcd_pos(0,0);             //设置显示位置为第一行的第1个字符
//     i = 0;
//    while(dis1[i] != '\0')
//     {                         //显示字符
//       lcd_wdat(dis1[i]);
//       i++;
//     }
//    lcd_pos(1,0);             //设置显示位置为第二行的第1个字符
//     i = 0;
//    while(dis2[i] != '\0')
//     {
//       lcd_wdat(dis2[i]);      //显示字符
//       i++;
//     }
// 	 lcd_pos(2,0);             //设置显示位置为第三行的第1个字符
//     i = 0;
//    while(dis3[i] != '\0')
//     {
//       lcd_wdat(dis3[i]);      //显示字符
//       i++;
//     }
//	 lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
//     i = 0;
//    while(dis4[i] != '\0')
//     {
//       lcd_wdat(dis4[i]);      //显示字符
//       i++;
//     };
//}