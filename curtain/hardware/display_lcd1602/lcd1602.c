//#include"lcd1602.h"
#include "main.h"

//---------------------------------------------
void lcd_delay(uchar ms) /*LCD1602 延时*/
{
    uchar j;
    while(ms--){
        for(j=0;j<250;j++)
            {;}
        }   
}

void lcd_busy_wait() /*LCD1602 忙等待*/
{
    lcd_rs_port = 0;
    lcd_rw_port = 1;
    lcd_en_port = 1;
    lcd_data_port = 0xff;
    while (lcd_data_port&0x80);
    lcd_en_port = 0; 

}


void lcd_command_write(uchar command) /*LCD1602 命令字写入*/
{
    lcd_busy_wait();
    lcd_rs_port = 0;
    lcd_rw_port = 0;
    lcd_en_port = 0;
    lcd_data_port = command;
    lcd_en_port = 1;
    lcd_en_port = 0;     
}



void lcd_system_reset() /*LCD1602 初始化*/
{
    lcd_delay(20);
    lcd_command_write(0x38);
    lcd_delay(100);
    lcd_command_write(0x38);
    lcd_delay(50);
    lcd_command_write(0x38);
    lcd_delay(10);
    lcd_command_write(0x08);
    lcd_command_write(0x01);
    lcd_command_write(0x06);
    lcd_command_write(0x0c); 
	lcd_data_port = 0xff; /*释放数据端口*/
}

void lcd_char_write(uchar x_pos,y_pos,lcd_dat) /*LCD1602 字符写入*/
{
    x_pos &= 0x0f; /* X位置范围 0~15 */
    y_pos &= 0x01; /* Y位置范围 0~ 1 */
    if(y_pos==1) x_pos += 0x40;
    x_pos += 0x80;
    lcd_command_write(x_pos);
    lcd_busy_wait();
    lcd_rs_port = 1;
    lcd_rw_port = 0;
    lcd_en_port = 0;
    lcd_data_port = lcd_dat;
    lcd_en_port = 1;
    lcd_en_port = 0; 
	lcd_data_port = 0xff; /*释放数据端口*/
}



//void main()
//{
//	uchar i;
//	uint temp; //温度值
//	lcd_system_reset(); /*LCD1602 初始化*/
//	/////////////////////////////////////////////////////////////////
//	P0=0X00;//关掉数码管的信号。阻止数码管受到P0口信号的影响。
//	dula=1;
//	wela=0;
//	delay1();
//	dula=0;
//	wela=0;
//	delay1();
//    ////////////////////////////////////////////////////////////////
//	lcd_data_port = 0xff; /*释放P0端口*/
//	Set1302(time_data_buff);  /*设置时间*/
//	while(1){
//		Get1302(time_data_buff); /*读取当前时间*/
//		temp = 	ReadTemperature(); /*读取当前温度值*/
//		/*刷新显示*/
//		lcd1602_line1[3]  = mun_to_char[time_data_buff[6]/0x10];
//		lcd1602_line1[4]  = mun_to_char[time_data_buff[6]%0x10];  /*年*/
//		lcd1602_line1[6]  = mun_to_char[time_data_buff[4]/0x10];
//		lcd1602_line1[7]  = mun_to_char[time_data_buff[4]%0x10];  /*月*/
//		lcd1602_line1[9]  = mun_to_char[time_data_buff[3]/0x10];
//		lcd1602_line1[10] = mun_to_char[time_data_buff[3]%0x10];  /*日*/
//		for(i=0;i<3;i++) lcd1602_line1[i+12]=Weeks[time_data_buff[5]&0x07][i]; /*星期*/
//		lcd1602_line2[2]  = mun_to_char[time_data_buff[2]/0x10];
//  		lcd1602_line2[3]  = mun_to_char[time_data_buff[2]%0x10]; /*时*/
//		lcd1602_line2[5]  = mun_to_char[time_data_buff[1]/0x10];
//		lcd1602_line2[6]  = mun_to_char[time_data_buff[1]%0x10]; /*分*/
//		lcd1602_line2[8]  = mun_to_char[time_data_buff[0]/0x10];
//		lcd1602_line2[9]  = mun_to_char[time_data_buff[0]%0x10]; /*秒*/
//        //------
//		lcd1602_line2[12] = mun_to_char[temp/100];
//		lcd1602_line2[13] = mun_to_char[temp%100/10];
//		lcd1602_line2[15] = mun_to_char[temp%10];  /*温度*/
//		//------
//		for(i=0;i<16;i++) lcd_char_write(i,0,lcd1602_line1[i]);
//	    for(i=0;i<16;i++) lcd_char_write(i,1,lcd1602_line2[i]);
//		}
//}




