#include "main.h"
//#include"18b20.h"
//DS18B20延时函数
void delay(unsigned int i)
{
	while(i--);
}

//DS18B20初始化函数
Init_DS18B20(void)
{
	unsigned char x=0;
	DQ = 1; //DQ复位
	delay(8); //稍做延时
	DQ = 0; //单片机将DQ拉低
	delay(80); //精确延时 大于 480us
	DQ = 1; //拉高总线
	delay(14);
	x=DQ; //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	delay(20);
}

//DS18B20读一个字节
ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--){
		DQ = 0; // 给脉冲信号
		dat>>=1;
		DQ = 1; // 给脉冲信号
		if(DQ)  dat|=0x80;
		delay(4);
		}
	return(dat);
}

//DS18B20写一个字节
WriteOneChar(unsigned char dat)
{
	unsigned char i=0;
	for (i=8; i>0; i--){
		DQ = 0;
		DQ = dat&0x01;
		delay(5);
		DQ = 1;
		dat>>=1;
		}
}

//DS18B20读取温度
ReadTemperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int t=0;
	float tt=0;
	Init_DS18B20();
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作
	WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=ReadOneChar();
	b=ReadOneChar();
	t=b;
	t<<=8;
	t=t|a;
	tt=t*0.0625; //将温度的高位与低位合并
	t= tt*10+0.5; //对结果进行4舍5入
	return(t);
}