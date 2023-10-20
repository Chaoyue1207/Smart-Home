#include "reg52.h"	
#include "main.h"



/*******************************************************************************
* 函数名         :UartInit()
* 函数功能		   :设置串口
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void UartInit(void)
{
   TMOD = 0x20;  //9600
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;
}
void uart_tx_byte(uchar str){
  SBUF=str;
	while(TI==0);
     TI=0;
}

