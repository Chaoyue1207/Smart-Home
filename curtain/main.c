/**************************************************************
*该C文件中包含了main函数和所有的控制逻辑，详细说明这里不赘叙
*
*开发板连接方法：
*			LCD12864连接开发板右上角最长的排针
*			步进电机模块的ABCD四个排针用杜邦线接到IO口P1.3~P1.6（顺序随意）
*			HC05的GND，VCC接到开发板的对应口，RxD端接到P3.1，TxD端接到P3.0(P3.1,P3.0的第二功能分别为TxD和RxD)
*					注意：若出现电量不够的情况，则可以部分模块的电源移到另外的电源上
*
*使用方法：
*			手机下载蓝牙串口助手，成功连接上后，可以从手机上发送“m”，“k”，“b”，“s”，“t”，“o”，“q”
*     你可以在终端模式、聊天模式中输入以上字符，也可以在按键模式自定义，具体功能不再赘叙
*
*实现现象：
*			用步进电机模拟的功能完善，断电有记忆的智能窗帘系统
*
*@contributor： lc，myc
*                        2020-09-15
**************************************************************/



//所有的头文件（自定义+库文件）都包含在main.h中
#include "main.h"

//初始化lcd12864各行
uchar data lcd_line1[]={" 2000/00/00 000 "};
uchar data lcd_line2[]={"  00:00:00 00.0C"};
uchar data lcd_line3[]={"光强:0-255 L:000"};
uchar data lcd_line4[]={"模式:0 100状态:1"};
uchar code Weeks[][3]={{"SUN"},{"MON"},{"TUE"},{"WED"},{"THU"},{"FRI"},{"SAT"},{"SUN"}};
uchar code mun_to_char[] = {"0123456789ABCDEF"}; /*定义数字跟ASCII码的关系*/


unsigned char time_buf2[16]={2,0,2,1,0,9,0,8,1,2,5,5,0,0,0,6}; //初始化时间

//-------以下标志位，参与了复杂的控制逻辑--------------
uint SetFlag=0;        //更新时间标志位
uint  SetTime=0;       //设置时间标志位
uint  ShowP=0;         //显示参数标志位
uint  rospeed=600;     //电机步长控制位
uchar  percentage=0;  //窗帘开关度 0代表全打开，100代表全关闭
uint  grad=0;   // 标志位  0中间量  1全关 2全开
uint MotorFlag =0; //动作命令
uint MotorState=1; //窗帘状态
uchar i=0;
uchar j=0;
uint  x=11;
unsigned int q =0;
uint temp=0; //温度值
uint temp1=0;//光强
uint timeH=0; //小时
uint MODE=1; //mode：0； 自动模式  1；手动以及蓝牙模式 

//---------定义快速方便的查找表--------------
uchar code check[10][10]={0,1,2,3,4,5,6,7,8,9,
												10,11,12,13,14,15,16,17,18,19,
												20,21,22,23,24,25,26,27,28,29,
												30,31,32,33,34,35,36,37,38,39,
												40,41,42,43,44,45,46,47,48,49,
												50,51,52,53,54,55,56,57,58,59,
												60,61,62,63,64,65,66,67,68,69,
												70,71,72,73,74,75,76,77,78,79,
												80,81,82,83,84,85,86,87,88,89,
												90,91,92,93,94,95,96,97,98,99};

												
/****************************************************************************
*函数名：main
*功  能：1）系统初始化
*				2）进入循环：读取时间、温度、光强并显示；校准时间；按控制逻辑驱动步进电机
*输  入：无
*输  出：无 
****************************************************************************/
void main(void){
		sys_init();
		while(1){
		Ds1302_Read_Time();
		temp=ReadTemperature();
		temp1=255-ReadADC(1);//值取差值，用于显示光强越小，数值越小
	
//--------------
		RST= 1;  //  display前必须加
		P1=0x87;
		display();
//--------------
	
		setTime1();

		motor_control();
		At24c02Write(1,percentage);
 }
}


/****************************************************************************
*函数名：setTime1
*功  能：见具体注释
*输  入：无
*输  出：无 
****************************************************************************/
void setTime1(){
	
	if(SetFlag)     //如果接收到串口信息则更新时钟
  {
	for(j=0;j<8;j++)
		{
			time_buf1[j]=check[time_buf2[2*j]-'0'][time_buf2[2*j+1]-'0'];
			}
		Ds1302_Write_Time();//接收更新的时间然后写入ds1302
		SetFlag=0;          //时钟信息更新后标志位清零
    }
}


/****************************************************************************
*函数名：motor_control
*功  能：执行控制逻辑
*逻  辑：1）检测窗帘初始开关度，检测标志位并初始化
*			   2）检测手动模式或者自动模式，根据环境或者指令驱动电机进行相应操作
*        3）电机停止后，检测当前状态并录入标志位
*输  入：无
*输  出：无 
****************************************************************************/
void motor_control()
{
	if(grad==1)
		{
			//让窗帘全关
			rospeed=(100-percentage)*6;
			Motor_B(rospeed);
			percentage=100;
			MotorState=0;
	    grad=0;
			rospeed=600;
		}
		if(grad==2)
		{
			//让窗帘全开
			rospeed=percentage*6;
			Motor_F(rospeed);
			percentage=0;
			MotorState=1;
			grad=0;
			rospeed=600;
		}
	//--窗帘全开全闭状态检测
	if(percentage>=100)
	{
		MotorState=0;
	}
	if(percentage==0)
	{
		MotorState=1;
	}
	if(percentage>0&&percentage<100){
		MotorState=2;
	}
	
	
	if(MODE==1)//自动控制模式
	{
		timeH=(time_buf[4]/0x10)*10+(time_buf[4]%0x10);
		if((timeH>=0&&timeH<6)||(timeH<=23&&timeH>20)||(timeH<=16&&timeH>=12))  //21-6点  13-16点
			{				
			if(temp1>189||temp>300)
			{
				if(MotorState==1) //如果是打开状态，关上
				{
					  grad=1;
				
				}
			}
		 }
		else
			{
				if(temp1<170&&temp<300)
			{
				if(MotorState==0) //如果是关上状态，打开
				{
					 grad=2;					
				}
			}
		
		}
	}
	else  // 手动按键或蓝牙
	{
		if(MotorFlag==2)
		{
			MotorFlag=0;
			if(MotorState==1||MotorState==2) //如果是打开状态，关上
				{
					percentage=Motor_B(rospeed)+percentage;
					if(percentage>=100)
					{
					percentage=100;
					MotorState=0;
					}
					rospeed=600;
				}
		}
	if(MotorFlag==1)
		{
			MotorFlag=0;
			if(MotorState==0||MotorState==2) //如果是关闭状态，打开
				{
					percentage=percentage-Motor_F(rospeed);
					if(percentage<=0)
					{
					percentage=0;
					MotorState=1;
					}
					rospeed=600;
				}
		}
	}
	
	//--窗帘全开全闭状态检测
	if(percentage>=100)
	{
		MotorState=0;
	}
	if(percentage==0)
	{
		MotorState=1;
	}
	if(percentage>0&&percentage<100){
		MotorState=2;
	}
}

/***********************************************************
*函数名：sys_init
*功  能：初始化系统
*输  入：无
*输  出：无 
***********************************************************/
void sys_init()
{
	 lcd_init();    /*LCD12864 初始化*/ 
   Ds1302_Init();
	 Ds1302_Write_Time();//time_buf1[8]
	 UartInit();
	MODE=0; //初始化mode 
	MotorFlag=0;  
  MotorState=1; //0： 拉上状态   1：打开状态
	lcd_data_port = 0xff; /*释放P0端口*/	
	percentage=At24c02Read(1);
	if(percentage>100)
		percentage=100;
}


/***********************************************************
*函数名：display
*功  能：LCD16824显示函数
*输  入：无
*输  出：无 
***********************************************************/
void display(void)
{
	/*刷新显示*/
    //---时间---
		lcd_line1[3]  = mun_to_char[time_buf[1]/0x10];
		lcd_line1[4]  = mun_to_char[time_buf[1]%0x10];  /*年*/
		lcd_line1[6]  = mun_to_char[time_buf[2]/0x10];
		lcd_line1[7]  = mun_to_char[time_buf[2]%0x10];  /*月*/
		lcd_line1[9]  = mun_to_char[time_buf[3]/0x10];
		lcd_line1[10] = mun_to_char[time_buf[3]%0x10];  /*日*/
		for(i=0;i<3;i++) lcd_line1[i+12]=Weeks[time_buf[7]][i]; /*星期*/
		lcd_line2[2]  = mun_to_char[time_buf[4]/0x10];
  	lcd_line2[3]  = mun_to_char[time_buf[4]%0x10]; /*时*/
		lcd_line2[5]  = mun_to_char[time_buf[5]/0x10];
		lcd_line2[6]  = mun_to_char[time_buf[5]%0x10]; /*分*/
		lcd_line2[8]  = mun_to_char[time_buf[6]/0x10];
		lcd_line2[9]  = mun_to_char[time_buf[6]%0x10]; /*秒*/
  	 //--温度--
		lcd_line2[11] = mun_to_char[temp/100];
		lcd_line2[12] = mun_to_char[temp%100/10];
		lcd_line2[14] = mun_to_char[temp%10];  /*温度*/
		//------
		//--光强--
		lcd_line3[13] = mun_to_char[temp1/100];
		lcd_line3[14] = mun_to_char[temp1%100/10];
		lcd_line3[15] = mun_to_char[(temp1%100)%10];  /*光强*/
		//------
		//--模式--
		lcd_line4[5] = mun_to_char[MODE];
		//
		lcd_line4[7] = mun_to_char[percentage/100];
		lcd_line4[8] = mun_to_char[percentage%100/10];
		lcd_line4[9] = mun_to_char[(percentage%100)%10];
		//窗帘状态
		lcd_line4[15] = mun_to_char[MotorState];
		//------
//		/*l602显示*/
//		for(i=0;i<16;i++) lcd_char_write(i,0,lcd_line1[i]);
//	    for(i=0;i<16;i++) lcd_char_write(i,1,lcd_line2[i]);

		/*l2864显示*/
		lcd_pos(0,0);
		for(i=0;i<16;i++) lcd_wdat(lcd_line1[i]);
		lcd_pos(1,0);
	    for(i=0;i<16;i++) lcd_wdat(lcd_line2[i]);
		lcd_pos(2,0);
		for(i=0;i<16;i++) lcd_wdat(lcd_line3[i]);
		lcd_pos(3,0);
		for(i=0;i<16;i++) lcd_wdat(lcd_line4[i]);
		
		//发送参数至蓝牙
		if(ShowP==1){
			uart_tx_byte('\n');
  		uart_tx_byte('T');
  		uart_tx_byte(':');	
			for( x=11;x<16;x++)
			{
				uart_tx_byte(lcd_line2[x]);
			} 
			uart_tx_byte('\n');
				for( x=11;x<16;x++)
			{
				uart_tx_byte(lcd_line3[x]);
			} 
			uart_tx_byte('\n');
			uart_tx_byte('P');
			uart_tx_byte(':');
			for( x=7;x<10;x++)
			{
				uart_tx_byte(lcd_line4[x]);
			} 
			ShowP=0;
			
	}
		
}


/***********************************************************
*函数名：UART_SER（串口中断服务程序）
*功  能：主机根据从机发送的字符指令进行相应判断，若成立则执行相应功能。
*输  入：无
*输  出：无 
***********************************************************/
void UART_SER (void) interrupt 4 //串行中断服务程序
{
    unsigned char TEMP;          //定义临时变量 
    //unsigned char q;
    if(RI)                        //判断是接收中断产生
     {
	   RI=0;                      //标志位清零
	  TEMP=SBUF;                 //读入缓冲区的值
		if(TEMP=='m')
			 {
				 MODE=!MODE;
				 SBUF=MODE;
				 	while(!TI);			 //等待发送数据完成 
     TI=0;
			 }
			 
	 if(TEMP=='k')
			 {
				 //MotorFlag=1;
				 grad=2;
				 SBUF=TEMP;
				 	while(!TI);			 //等待发送数据完成 
     TI=0;
			 }
	if(TEMP=='b')
			 {
				  grad=1;
				 SBUF=TEMP;
				 	while(!TI);			 //等待发送数据完成 
     TI=0;
			 }
			 
   if(TEMP=='s')
			 {
				 ShowP=1;
				 SBUF=TEMP;
				 	while(!TI);			 //等待发送数据完成 
     TI=0;
			 }
	 if(TEMP=='o')        //正转半圈
	     {
				 MotorFlag=1; 
					rospeed=60;
				 SBUF=TEMP;
				 	while(!TI);			 //等待发送数据完成 
      TI=0;
			 }
			 
   if(TEMP=='q')
			 {
				 MotorFlag=2;     //反转半圈
				 rospeed=60;
				 SBUF=TEMP;
				 	while(!TI);			 //等待发送数据完成 
     TI=0;
			 }
    if(SetTime)
		{
	  time_buf2[q]=TEMP;//&0x0F
	  q++;
	  if(q==15)                  //连续接收16个字符信息
	   {
	    q=0;
		SetFlag=1;               //接收完成标志位置1
		SetTime=0;
	   }
      SBUF=time_buf2[q]; //把接收到的值再发回电脑端
		 	while(!TI);			 //等待发送数据完成 
     TI=0;
	  }
			if(TEMP=='t')
			 {
				  SetTime=1;
				 	SetFlag=1;
				 SBUF=TEMP;	
				 	while(!TI);			 //等待发送数据完成 
					TI=0;
			 }
		
	 }

}


