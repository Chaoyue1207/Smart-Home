/**************************************************************
*��C�ļ��а�����main���������еĿ����߼�����ϸ˵�����ﲻ׸��
*
*���������ӷ�����
*			LCD12864���ӿ��������Ͻ��������
*			�������ģ���ABCD�ĸ������öŰ��߽ӵ�IO��P1.3~P1.6��˳�����⣩
*			HC05��GND��VCC�ӵ�������Ķ�Ӧ�ڣ�RxD�˽ӵ�P3.1��TxD�˽ӵ�P3.0(P3.1,P3.0�ĵڶ����ֱܷ�ΪTxD��RxD)
*					ע�⣺�����ֵ������������������Բ���ģ��ĵ�Դ�Ƶ�����ĵ�Դ��
*
*ʹ�÷�����
*			�ֻ����������������֣��ɹ������Ϻ󣬿��Դ��ֻ��Ϸ��͡�m������k������b������s������t������o������q��
*     ��������ն�ģʽ������ģʽ�����������ַ���Ҳ�����ڰ���ģʽ�Զ��壬���幦�ܲ���׸��
*
*ʵ������
*			�ò������ģ��Ĺ������ƣ��ϵ��м�������ܴ���ϵͳ
*
*@contributor�� lc��myc
*                        2020-09-15
**************************************************************/



//���е�ͷ�ļ����Զ���+���ļ�����������main.h��
#include "main.h"

//��ʼ��lcd12864����
uchar data lcd_line1[]={" 2000/00/00 000 "};
uchar data lcd_line2[]={"  00:00:00 00.0C"};
uchar data lcd_line3[]={"��ǿ:0-255 L:000"};
uchar data lcd_line4[]={"ģʽ:0 100״̬:1"};
uchar code Weeks[][3]={{"SUN"},{"MON"},{"TUE"},{"WED"},{"THU"},{"FRI"},{"SAT"},{"SUN"}};
uchar code mun_to_char[] = {"0123456789ABCDEF"}; /*�������ָ�ASCII��Ĺ�ϵ*/


unsigned char time_buf2[16]={2,0,2,1,0,9,0,8,1,2,5,5,0,0,0,6}; //��ʼ��ʱ��

//-------���±�־λ�������˸��ӵĿ����߼�--------------
uint SetFlag=0;        //����ʱ���־λ
uint  SetTime=0;       //����ʱ���־λ
uint  ShowP=0;         //��ʾ������־λ
uint  rospeed=600;     //�����������λ
uchar  percentage=0;  //�������ض� 0����ȫ�򿪣�100����ȫ�ر�
uint  grad=0;   // ��־λ  0�м���  1ȫ�� 2ȫ��
uint MotorFlag =0; //��������
uint MotorState=1; //����״̬
uchar i=0;
uchar j=0;
uint  x=11;
unsigned int q =0;
uint temp=0; //�¶�ֵ
uint temp1=0;//��ǿ
uint timeH=0; //Сʱ
uint MODE=1; //mode��0�� �Զ�ģʽ  1���ֶ��Լ�����ģʽ 

//---------������ٷ���Ĳ��ұ�--------------
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
*��������main
*��  �ܣ�1��ϵͳ��ʼ��
*				2������ѭ������ȡʱ�䡢�¶ȡ���ǿ����ʾ��У׼ʱ�䣻�������߼������������
*��  �룺��
*��  ������ 
****************************************************************************/
void main(void){
		sys_init();
		while(1){
		Ds1302_Read_Time();
		temp=ReadTemperature();
		temp1=255-ReadADC(1);//ֵȡ��ֵ��������ʾ��ǿԽС����ֵԽС
	
//--------------
		RST= 1;  //  displayǰ�����
		P1=0x87;
		display();
//--------------
	
		setTime1();

		motor_control();
		At24c02Write(1,percentage);
 }
}


/****************************************************************************
*��������setTime1
*��  �ܣ�������ע��
*��  �룺��
*��  ������ 
****************************************************************************/
void setTime1(){
	
	if(SetFlag)     //������յ�������Ϣ�����ʱ��
  {
	for(j=0;j<8;j++)
		{
			time_buf1[j]=check[time_buf2[2*j]-'0'][time_buf2[2*j+1]-'0'];
			}
		Ds1302_Write_Time();//���ո��µ�ʱ��Ȼ��д��ds1302
		SetFlag=0;          //ʱ����Ϣ���º��־λ����
    }
}


/****************************************************************************
*��������motor_control
*��  �ܣ�ִ�п����߼�
*��  ����1����ⴰ����ʼ���ضȣ�����־λ����ʼ��
*			   2������ֶ�ģʽ�����Զ�ģʽ�����ݻ�������ָ���������������Ӧ����
*        3�����ֹͣ�󣬼�⵱ǰ״̬��¼���־λ
*��  �룺��
*��  ������ 
****************************************************************************/
void motor_control()
{
	if(grad==1)
		{
			//�ô���ȫ��
			rospeed=(100-percentage)*6;
			Motor_B(rospeed);
			percentage=100;
			MotorState=0;
	    grad=0;
			rospeed=600;
		}
		if(grad==2)
		{
			//�ô���ȫ��
			rospeed=percentage*6;
			Motor_F(rospeed);
			percentage=0;
			MotorState=1;
			grad=0;
			rospeed=600;
		}
	//--����ȫ��ȫ��״̬���
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
	
	
	if(MODE==1)//�Զ�����ģʽ
	{
		timeH=(time_buf[4]/0x10)*10+(time_buf[4]%0x10);
		if((timeH>=0&&timeH<6)||(timeH<=23&&timeH>20)||(timeH<=16&&timeH>=12))  //21-6��  13-16��
			{				
			if(temp1>189||temp>300)
			{
				if(MotorState==1) //����Ǵ�״̬������
				{
					  grad=1;
				
				}
			}
		 }
		else
			{
				if(temp1<170&&temp<300)
			{
				if(MotorState==0) //����ǹ���״̬����
				{
					 grad=2;					
				}
			}
		
		}
	}
	else  // �ֶ�����������
	{
		if(MotorFlag==2)
		{
			MotorFlag=0;
			if(MotorState==1||MotorState==2) //����Ǵ�״̬������
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
			if(MotorState==0||MotorState==2) //����ǹر�״̬����
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
	
	//--����ȫ��ȫ��״̬���
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
*��������sys_init
*��  �ܣ���ʼ��ϵͳ
*��  �룺��
*��  ������ 
***********************************************************/
void sys_init()
{
	 lcd_init();    /*LCD12864 ��ʼ��*/ 
   Ds1302_Init();
	 Ds1302_Write_Time();//time_buf1[8]
	 UartInit();
	MODE=0; //��ʼ��mode 
	MotorFlag=0;  
  MotorState=1; //0�� ����״̬   1����״̬
	lcd_data_port = 0xff; /*�ͷ�P0�˿�*/	
	percentage=At24c02Read(1);
	if(percentage>100)
		percentage=100;
}


/***********************************************************
*��������display
*��  �ܣ�LCD16824��ʾ����
*��  �룺��
*��  ������ 
***********************************************************/
void display(void)
{
	/*ˢ����ʾ*/
    //---ʱ��---
		lcd_line1[3]  = mun_to_char[time_buf[1]/0x10];
		lcd_line1[4]  = mun_to_char[time_buf[1]%0x10];  /*��*/
		lcd_line1[6]  = mun_to_char[time_buf[2]/0x10];
		lcd_line1[7]  = mun_to_char[time_buf[2]%0x10];  /*��*/
		lcd_line1[9]  = mun_to_char[time_buf[3]/0x10];
		lcd_line1[10] = mun_to_char[time_buf[3]%0x10];  /*��*/
		for(i=0;i<3;i++) lcd_line1[i+12]=Weeks[time_buf[7]][i]; /*����*/
		lcd_line2[2]  = mun_to_char[time_buf[4]/0x10];
  	lcd_line2[3]  = mun_to_char[time_buf[4]%0x10]; /*ʱ*/
		lcd_line2[5]  = mun_to_char[time_buf[5]/0x10];
		lcd_line2[6]  = mun_to_char[time_buf[5]%0x10]; /*��*/
		lcd_line2[8]  = mun_to_char[time_buf[6]/0x10];
		lcd_line2[9]  = mun_to_char[time_buf[6]%0x10]; /*��*/
  	 //--�¶�--
		lcd_line2[11] = mun_to_char[temp/100];
		lcd_line2[12] = mun_to_char[temp%100/10];
		lcd_line2[14] = mun_to_char[temp%10];  /*�¶�*/
		//------
		//--��ǿ--
		lcd_line3[13] = mun_to_char[temp1/100];
		lcd_line3[14] = mun_to_char[temp1%100/10];
		lcd_line3[15] = mun_to_char[(temp1%100)%10];  /*��ǿ*/
		//------
		//--ģʽ--
		lcd_line4[5] = mun_to_char[MODE];
		//
		lcd_line4[7] = mun_to_char[percentage/100];
		lcd_line4[8] = mun_to_char[percentage%100/10];
		lcd_line4[9] = mun_to_char[(percentage%100)%10];
		//����״̬
		lcd_line4[15] = mun_to_char[MotorState];
		//------
//		/*l602��ʾ*/
//		for(i=0;i<16;i++) lcd_char_write(i,0,lcd_line1[i]);
//	    for(i=0;i<16;i++) lcd_char_write(i,1,lcd_line2[i]);

		/*l2864��ʾ*/
		lcd_pos(0,0);
		for(i=0;i<16;i++) lcd_wdat(lcd_line1[i]);
		lcd_pos(1,0);
	    for(i=0;i<16;i++) lcd_wdat(lcd_line2[i]);
		lcd_pos(2,0);
		for(i=0;i<16;i++) lcd_wdat(lcd_line3[i]);
		lcd_pos(3,0);
		for(i=0;i<16;i++) lcd_wdat(lcd_line4[i]);
		
		//���Ͳ���������
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
*��������UART_SER�������жϷ������
*��  �ܣ��������ݴӻ����͵��ַ�ָ�������Ӧ�жϣ���������ִ����Ӧ���ܡ�
*��  �룺��
*��  ������ 
***********************************************************/
void UART_SER (void) interrupt 4 //�����жϷ������
{
    unsigned char TEMP;          //������ʱ���� 
    //unsigned char q;
    if(RI)                        //�ж��ǽ����жϲ���
     {
	   RI=0;                      //��־λ����
	  TEMP=SBUF;                 //���뻺������ֵ
		if(TEMP=='m')
			 {
				 MODE=!MODE;
				 SBUF=MODE;
				 	while(!TI);			 //�ȴ������������ 
     TI=0;
			 }
			 
	 if(TEMP=='k')
			 {
				 //MotorFlag=1;
				 grad=2;
				 SBUF=TEMP;
				 	while(!TI);			 //�ȴ������������ 
     TI=0;
			 }
	if(TEMP=='b')
			 {
				  grad=1;
				 SBUF=TEMP;
				 	while(!TI);			 //�ȴ������������ 
     TI=0;
			 }
			 
   if(TEMP=='s')
			 {
				 ShowP=1;
				 SBUF=TEMP;
				 	while(!TI);			 //�ȴ������������ 
     TI=0;
			 }
	 if(TEMP=='o')        //��ת��Ȧ
	     {
				 MotorFlag=1; 
					rospeed=60;
				 SBUF=TEMP;
				 	while(!TI);			 //�ȴ������������ 
      TI=0;
			 }
			 
   if(TEMP=='q')
			 {
				 MotorFlag=2;     //��ת��Ȧ
				 rospeed=60;
				 SBUF=TEMP;
				 	while(!TI);			 //�ȴ������������ 
     TI=0;
			 }
    if(SetTime)
		{
	  time_buf2[q]=TEMP;//&0x0F
	  q++;
	  if(q==15)                  //��������16���ַ���Ϣ
	   {
	    q=0;
		SetFlag=1;               //������ɱ�־λ��1
		SetTime=0;
	   }
      SBUF=time_buf2[q]; //�ѽ��յ���ֵ�ٷ��ص��Զ�
		 	while(!TI);			 //�ȴ������������ 
     TI=0;
	  }
			if(TEMP=='t')
			 {
				  SetTime=1;
				 	SetFlag=1;
				 SBUF=TEMP;	
				 	while(!TI);			 //�ȴ������������ 
					TI=0;
			 }
		
	 }

}


