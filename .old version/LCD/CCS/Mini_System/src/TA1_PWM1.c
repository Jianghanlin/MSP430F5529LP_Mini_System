/*
 * TA1_PWM1.c
 *
 *  Created on: 2015��11��20��
 *      Author: yumin
 */
/*************TA1*******************/
#include "msp430F5529.h"

#define TA11_SET 	P2SEL |= BIT0; P2DIR |= BIT0		//P2.0
#define TA11_OFF 	P2SEL &= ~BIT0 						//P2.0

/*****************************************************************************************
* ��       �ƣ�    TA1_PWM_Init()
* ��       �ܣ�    TA1��ʱ����ΪPWM�������ĳ�ʼ�����ú���
* ��ڲ�����   Clk:ʱ��Դ 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(�ⲿ����)�� 'e'= TACLK(TACLKȡ��)
         Div:ʱ�ӷ�Ƶϵ��: 1/2/4/8
		 Mode1:ͨ��1�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM��ģʽ3��
* ���ڲ�����   1��ʾ���óɹ���0��ʾ������������ʧ�ܡ�
* ˵       �� : �ڵ���PWM��غ���֮ǰ����Ҫ���øú�������TA��ģʽ��ʱ��Դ��
* ��       �� : TA1_PWM_Init('A',1,'B')TAʱ����ΪACLK,ͨ��1�ͺ�PWM���
         TA1_PWM_Init('S',1,'F')TAʱ����ΪSMCLK,ͨ��1��ǰPWM���
 ****************************************************************************************/
char TA1_PWM_Init(char Clk,char Div,char Mode1)
{
  TA1CTL =0;												// �����ǰ����

  switch(Mode1)												//Ϊ��ʱ��ѡ�����ģʽ
  {
  case 'F': case 'f':										//��ͨPWM
	  TA1CTL |=MC_1; break;									//����ʱ��Ϊ������
  case 'B':case 'b':
	  TA1CTL |=MC_1; break;									//����ʱ��Ϊ������
  default : return(0);										//��������������ò������󣬷���0
  }

  switch(Clk)  												//Ϊ��ʱ��TAѡ��ʱ��Դ
  {
    case 'A': case 'a':  	TA1CTL|=TASSEL_1; break;   		//ACLK
    case 'S': case 's': 	TA1CTL|=TASSEL_2; break;  		//SMCLK
    case 'E':            	TA1CTL|=TASSEL_0; break;  		//�ⲿ����(TACLK)
    case 'e':          		TA1CTL|=TASSEL_3; break;   		//�ⲿ����(TACLKȡ��)
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Div) 												//Ϊ��ʱ��TAѡ���Ƶϵ��
  {
    case 1:   TA1CTL|=ID_0; break;   						//1
    case 2:   TA1CTL|=ID_1; break;   						//2
    case 4:   TA1CTL|=ID_2; break;  						//4
    case 8:   TA1CTL|=ID_3; break;                          //8
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Mode1)										 		//����PWMͨ��1�����ģʽ��
  {
     case 'F':	case 'f':
              TA1CCTL1 =OUTMOD_7;
              TA11_SET;
              break;
     case 'B':	case 'b':
              TA1CCTL1 =OUTMOD_3;
              TA11_SET;
              break;
     default :  return(0); 							        //���ò������󣬷���0
  }
  return(1);
}
/*****************************************************************************************
* ��       �ƣ�TA1_PWM_SetPeriod()
* ��       �ܣ�����PWM������������
* ��ڲ�����Period:����(0~65535) ʱ�Ӹ���
* ���ڲ�����1�����óɹ�     0������ʧ��
* ˵       �� :
* ��       �� : TA1_PWM_SetPeriod(500)����PWM��������Ϊ500��ʱ������
 ****************************************************************************************/
char TA1_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TA1CCR0 = Period;
	return(1);
}

/*****************************************************************************************
* ��    �ƣ�TA0_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(һ��ʱ�Ӹ���)
* ��ڲ�����Duty: PWM�ߵ�ƽ��Чʱ��(0~65535)
* ���ڲ�����1���óɹ���0����ʧ��
* ˵    ��: PWM�ߵ�ƽ��Чʱ��ΪDuty��ʱ������
* ��    ��: TA1_PWM_SetPermill(50)����PWM�����ߵ�ƽ��Чʱ��Ϊ50��ʱ������
 ****************************************************************************************/
char TA1_PWM_SetPermill(unsigned int Duty)
{
	unsigned char Mod;
	Mod = (TA1CCTL1 & 0x00e0)>>5; //��ȡ���ģʽ��OUTMOD0λ��5-7λ
	switch(Mod)			          //����ģʽ�趨TACCRx
		{
		case 7: TA1CCR1=Duty;          break;
		case 3: TA1CCR1=TA1CCR0-Duty;  break;
		default: return(0);
		}
	return (1);
}



