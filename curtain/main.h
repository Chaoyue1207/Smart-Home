#ifndef __MAIN_H__
#define __MAIN_H__

#define uint unsigned int
#define uchar unsigned char

#include <reg52.h>
#include <intrins.h>
#include "motordriver.h"
#include "ds1302.h"
#include "18b20.h"
#include "lcd1602.h"
#include "lumination.h"
#include "i2c.h"
#include "delay.h"
#include "bt.h"
#include "lcd12864.h"
#include "Tim0.h"
//#include "control.h"

void sys_init();
void display(void);
void motor_control(void);
void setTime1();

extern uint temp; //温度值
extern uint temp1;//光强
//extern unsigned int MotorFlag;  

#endif

