#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "hc05.h"
#include "usart3.h"			 	 
#include "string.h"	   
#include "usmart.h"	
#include "io.h"

 
 /************************************************
 扩展实验1：ALIENTEK STM32F103开发板 
 ATK-HC05蓝牙串口模块实验-库函数版本  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
	
 int main(void)
 {	 
	u8 reclen=0,GM_last=1; 
	u8 gmflag=0;        //光敏电阻标志位
	delay_init();	    	 //延时函数初始化	  
   JK_Init();
	LED_Init();				//初始化与LED连接的硬件接口
	delay_ms(1000);			//等待蓝牙模块上电稳定										   	   
	USART3_RX_STA=0;
	 HC05_Init();
 	while(1) 
	{		 
		if(USART3_RX_STA&0X8000)			//接收到一次数据了
		{
 			reclen=USART3_RX_STA&0X7FFF;	//得到数据长度
		  	USART3_RX_BUF[reclen]=0;	 	//加入结束符
			if(reclen==9||reclen==8) 		//控制DS1检测
			{
				if(strcmp((const char*)USART3_RX_BUF,"+LED1 ON")==0)
				{
					DJ1=1;
					DJ2=0;
					delay_ms(5000);
					DJ1=0;
				}	
//				LED1=0;	//打开LED1
				if(strcmp((const char*)USART3_RX_BUF,"+LED1 OFF")==0)
				{
					DJ1=0;
					DJ2=1;
					delay_ms(5000);
					DJ2=0;
				}	
				if(strcmp((const char*)USART3_RX_BUF,"+LED2 ON")==0)
				{
					 gmflag=1;
				}	
				if(strcmp((const char*)USART3_RX_BUF,"+LED2 OFF")==0)
				{

						gmflag=0;
				}	
				
//				LED1=1;//关闭LED1
			}
			
 			USART3_RX_STA=0;	 
		}	 		
			if(gmflag)
			{
					if(GM!=GM_last)
					{
						if(GM==1)
						{
							DJ1=1;
						DJ2=0;
						delay_ms(5000);
						DJ1=0;
						}
						else
						{
							DJ1=0;
						DJ2=1;
						delay_ms(5000);
						DJ2=0;
						}
						GM_last=GM;
					}
					
					
			}
			if(!gmflag)
			{
				DJ1=0;
				DJ2=0;
			}



	}
}
