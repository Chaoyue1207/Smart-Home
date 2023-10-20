#ifndef __LCD1602_H__
#define __LCD1602_H__

//#include <reg52.h>
//#include <intrins.h>
#include "main.h"
sbit lcd_rs_port = P3^5;  /*定义LCD控制端口*/
sbit lcd_rw_port = P3^6;
sbit lcd_en_port = P3^4;
#define lcd_data_port P0

void lcd_delay(uchar ms); /*LCD1602 延时*/
void lcd_busy_wait(); /*LCD1602 忙等待*/
void lcd_command_write(uchar command); /*LCD1602 命令字写入*/
void lcd_system_reset(); /*LCD1602 初始化*/
void lcd_char_write(uchar x_pos,y_pos,lcd_dat); /*LCD1602 字符写入*/	
#endif
