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
 ��չʵ��1��ALIENTEK STM32F103������ 
 ATK-HC05��������ģ��ʵ��-�⺯���汾  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
	
 int main(void)
 {	 
	u8 reclen=0,GM_last=1; 
	u8 gmflag=0;        //���������־λ
	delay_init();	    	 //��ʱ������ʼ��	  
   JK_Init();
	LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�
	delay_ms(1000);			//�ȴ�����ģ���ϵ��ȶ�										   	   
	USART3_RX_STA=0;
	 HC05_Init();
 	while(1) 
	{		 
		if(USART3_RX_STA&0X8000)			//���յ�һ��������
		{
 			reclen=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
		  	USART3_RX_BUF[reclen]=0;	 	//���������
			if(reclen==9||reclen==8) 		//����DS1���
			{
				if(strcmp((const char*)USART3_RX_BUF,"+LED1 ON")==0)
				{
					DJ1=1;
					DJ2=0;
					delay_ms(5000);
					DJ1=0;
				}	
//				LED1=0;	//��LED1
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
				
//				LED1=1;//�ر�LED1
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
