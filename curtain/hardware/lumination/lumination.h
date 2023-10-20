#ifndef __LUMINATION_H__
#define __LUMINATION_H__


// lum口可能要改
#include <main.h>

#define AddWr 0x90   //写数据地址 
#define AddRd 0x91   //读数据地址

extern bit ack;
unsigned char ReadADC(unsigned char Chl);
//bit WriteDAC(unsigned char dat);


 
#endif

