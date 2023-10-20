#ifndef __LCD12864_H__
#define __LCD12864_H__

//#include"reg52.h"
#include "main.h"

//#define uchar unsigned char
//#define uint  unsigned int

//12864 IO端口定义
#define LCD_data  P0;             //数据口
sbit LCD_RS  =  P3^5;            //寄存器选择输入 
sbit LCD_RW  =  P3^6;            //液晶读/写控制
sbit LCD_EN  =  P3^4;            //液晶使能控制
sbit LCD_PSB =  P3^7;            //串/并方式控制
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;

#define delayNOP();  {_nop_();_nop_();_nop_();_nop_();}


void delay0(uchar x);  //x*0.14MS
void beep();
void  dataconv();
void lcd_pos(uchar X,uchar Y);  //确定显示位置
void delay3(int ms);
bit lcd_busy();                 //检查lcd忙状态
void lcd_wcmd(uchar cmd);       //写指令数据到lcd
void lcd_wdat(uchar dat);       //写显示数据到lcd
void lcd_init();                //lcd初始化设定
//void lcd_drive();               //lcd驱动运行函数





#endif
