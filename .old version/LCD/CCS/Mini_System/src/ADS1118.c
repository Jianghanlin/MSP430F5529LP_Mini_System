//////////////////////////////////////////////////////	
//AIN����˿ڣ���-����								//
//  0:AIN0-AIN1 1:AIN0-AIN3 2:AIN1-AIN3 3:AIN2-AIN3	//
//  4:AIN0-GND  5:AIN1-GND  6:AIN2-GND  7:AIN3-GND	//
//����												//
//  0:��6.144V 1:��4.096V 2:��2.048V 3:��1.024V		//
//  4:��0.512V 5:��0.256V 6:��0.256V 7:��0.256V		//
//////////////////////////////////////////////////////
#include "msp430f5529.h"

#define SCLK_H P4OUT |= BIT0
#define SCLK_L P4OUT &= ~BIT0
#define CS_H   P4OUT |= BIT1
#define CS_L   P4OUT &= ~BIT1
#define DataIN_H  P4OUT |= BIT2
#define DataIN_L  P4OUT &= ~BIT2

#define uint  unsigned int
#define uchar unsigned char

void ADS1118_Init(void)
{
	P4DIR |=  BIT0;
	P4DIR |=  BIT1;
	P4DIR |=  BIT2;			 //�������Ƭ��д����
	P4DIR &=~ BIT3;   		 //���룬��Ƭ��������
}


//****************************************************************
//* �������ƣ�WriteSPI
//* ������������ʼSPIд����
//* ��ڲ�����config
//* ���ز�����void
//****************************************************************
void WriteSPI(uint config)
{
	uint i=0;
	CS_L;
	SCLK_L;
	//delay_us(200);
	for(i=0;i<16;i++)
	{	
		SCLK_H;
		//delay_us(200);
		if(config&0x8000)
		{
			DataIN_H;
		}
		else
		{
			DataIN_L;
		}
		config<<=1;
		SCLK_L;
		//delay_us(200);
	}
   	CS_H;
}

//****************************************************************
//* �������ƣ�ADS_ReadSPI��
//* ������������ʼSPI������
//* ��ڲ�����void
//* ���ز�����unsigned int
//****************************************************************
uint  ADS_Read()
{
	uint i=0;
	uint adc;
	CS_L;
	adc=0x0000; 

	while(P4IN&BIT3);//����һ��ת����ʼ�ж�
    DataIN_H;
	SCLK_L;
	for(i=0;i<16;i++)//��ȡ���ݣ�����λ��ȡ����16λ����λ��ʼ
	{ 
		adc = adc<<1;
		SCLK_H;
		//delay_us(200);
		if(P4IN&BIT3)
		{
			adc |=0x0001;
		}
		else
		{
			adc&=~0x0001;
		}
		SCLK_L;
 
		//delay_us(200);
	} 
	CS_H;
	return adc;
}

//****************************************************************
//* �������ƣ�ADS1118_Config
//* �������������üĴ���
//* ��ڲ�����add---ADS1118�ļĴ�������
//* ���ز�����void
//****************************************************************
void ADS1118_Config(uchar port, uchar scale)
{
	WriteSPI(0x81e3+port*4096+scale*512);//C1E3  1100 0001 1110 0011
}
//****************************************************************
//* �������ƣ�ADS1118
//* ��������������һ��ADת��
//* ��ڲ�����port---AIN����˿�(0~7)  scale---������(0~7)
//* ���ز�����void
//****************************************************************
float ADS1118(uchar port, uchar scale)
{
	float value;
	ADS1118_Config(port, scale);
	value=ADS_Read();
	if(value>0x7FFF) value -= 0x10000;
	switch(scale)
	{
		case 0: value*=6.144; break;
		case 1: value*=4.096; break;
		case 2: value*=2.048; break;
		case 3: value*=1.024; break;
		case 4: value*=0.512; break;
		case 5: value*=0.256; break;
		case 6: value*=0.256; break;
		case 7: value*=0.256; break;
		default: break;
	}
	value/=32768.0;
	return value ;
}
