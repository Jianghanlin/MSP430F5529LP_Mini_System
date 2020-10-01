/*
 * TA2_PWM.c
 *
 *  Created on: 2015��11��20��
 *      Author: yumin
 */
/*************TA2*******************/
#include "msp430F5529.h"
#define Dead   1             							//Ԥ������ʱ�䣬��TA��clkΪ��λ

#define TA20_SET 	P2SEL |= BIT3; P2DIR |= BIT3		//P2.3
#define TA21_SET 	P2SEL |= BIT4; P2DIR |= BIT4		//P2.4
#define TA22_SET 	P2SEL |= BIT5; P2DIR |= BIT5		//P2.5

#define TA20_OFF 	P2SEL &= ~BIT3 						//P2.3
#define TA21_OFF 	P2SEL &= ~BIT4 						//P2.4
#define TA22_OFF 	P2SEL &= ~BIT5						//P2.5
/*****************************************************************************************
* ��       �ƣ�TA2_PWM_Init()
* ��       �ܣ�TA2��ʱ����ΪPWM�������ĳ�ʼ�����ú���
* ��ڲ�����Clk:ʱ��Դ 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(�ⲿ����)�� 'e'= TACLK(TACLKȡ��)
                    Div:ʱ�ӷ�Ƶϵ��: 1/2/4/8
		    Mode1:ͨ��1�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM��ģʽ3�� ��'D'��������PWM��ģʽ6����0=����
		    Mode2:ͨ��2�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM ��ģʽ3����'D'��������PWM��ģʽ2����0=����
		    ����������������Ƶ�PWMʱ����ͨ������ʹ�ã��Ҿ�Ϊ����ģʽ��
* ���ڲ�����1��ʾ���óɹ���0��ʾ������������ʧ�ܡ�
* ˵       �� : �ڵ���PWM��غ���֮ǰ����Ҫ���øú�������TA��ģʽ��ʱ��Դ��
* ��       �� : TA2_PWM_Init('A',1,'F','P')TAʱ����ΪACLK,ͨ��1��ͨ��2��Ϊ��ǰPWM���
                   TA2_PWM_Init('S',4,'D','D')TAʱ����ΪSMCLK/4, ͨ��1Ϊ������PWM��ͨ��2Ϊ������PWM
                   TA2_PWM_Init('A',1,'F',0)TAʱ����ΪACLK,ͨ��1��ǰPWM�����ͨ��2����TA�á�
 ****************************************************************************************/
char TA2_PWM_Init(char Clk,char Div,char Mode1,char Mode2)
{
  TA2CTL =0;												// �����ǰ����

  switch(Mode1)												//Ϊ��ʱ��ѡ�����ģʽ
  {
  case 'F': case 'f':										//��ͨPWM
		  TA2CTL |=MC_1; break;								//����ʱ��Ϊ������
  case 'B': case 'b':
	  	  TA2CTL |=MC_1; break;								//����ʱ��Ϊ������
  case 'D': case 'd':										//����PWM
     	  TA2CTL |=MC_3; break;								//����ʱ��Ϊ��������
  default : return(0);										//��������������ò������󣬷���0
  }

  switch(Clk)  												//Ϊ��ʱ��TAѡ��ʱ��Դ
  {
    case 'A': case 'a':  	TA2CTL|=TASSEL_1; break;   		//ACLK
    case 'S': case 's': 	TA2CTL|=TASSEL_2; break;  		//SMCLK
    case 'E':            	TA2CTL|=TASSEL_0; break;  		//�ⲿ����(TACLK)
    case 'e':          		TA2CTL|=TASSEL_3; break;   		//�ⲿ����(TACLKȡ��)
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Div) 												//Ϊ��ʱ��TAѡ���Ƶϵ��
  {
    case 1:   TA2CTL|=ID_0; break;   						//1
    case 2:   TA2CTL|=ID_1; break;   						//2
    case 4:   TA2CTL|=ID_2; break;  						//4
    case 8:   TA2CTL|=ID_3; break;  						//8
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Mode1)										 		//����PWMͨ��1�����ģʽ��
  {
     case 'F':	case 'f':
              TA2CCTL1 = OUTMOD_7;
              TA21_SET;
              break;
     case 'B':	case 'b':
              TA2CCTL1 = OUTMOD_3;
              TA21_SET;
              break;
     case 'D':  case'd':
	          TA2CCTL1 = OUTMOD_6;
    	      TA21_SET;
    	      break;
      case '0': case 0:   							        //�������Ϊ����
              TA21_OFF;   									//TA2.1�ָ�Ϊ��ͨIO��
              break;
     default :  return(0); 							  		//���ò������󣬷���0
  }
  switch(Mode2) 											//����PWMͨ��2�����ģʽ��
  {
      case 'F':	 case 'f':
              TA2CCTL2 = OUTMOD_7;
              TA22_SET;  break;
       case 'B': case 'b':
              TA2CCTL2 = OUTMOD_3;
              TA22_SET;  break;
       case 'D': case 'd':
	       	  TA2CCTL2 = OUTMOD_2;
	       	  TA22_SET;  break;
       case '0': case 0:   									//�������Ϊ����
           	  TA22_OFF;  break;
       default :  return(0); 								//���ò������󣬷���0
    }
  return(1);
}
/****************************************************************************************
* ��       �ƣ�TA2_PWM_SetPeriod()
* ��       �ܣ�����PWM������������
* ��ڲ�����Channel: TA0=0, TA1=1
*                     Period:����(0~65535) ʱ�Ӹ���
* ���ڲ�����1�����óɹ�     0������ʧ��
* ˵       �� : ��ͨPWM�������PWM�������һ��
* ��       �� : TA2_PWM_SetPeriod(500)����PWM��������Ϊ500��1000��ʱ������
 ****************************************************************************************/
char TA2_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TA2CCR0 = Period;
	return(1);
}

/*****************************************************************************************
* ��    �ƣ�TA2_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(
* ��ڲ�����Channel: ��ǰ���õ�ͨ����  1/2
            Duty: PWM�ߵ�ƽ��Чʱ��
* ���ڲ�����1���óɹ���0����ʧ��
* ˵    ��: ����ģʽʱ����channelͬʱ�趨��
* ��    ��:
 ****************************************************************************************/
char TA2_PWM_SetPermill(char Channel,unsigned int Duty)
{
	unsigned char Mod = 0;
	switch (Channel)									//���жϳ�ͨ���Ĺ���ģʽ
		{
	case 1:
		Mod = (TA2CCTL1 & 0x00e0)>>5;	break;	   		//��ȡ���ģʽ��OUTMOD0λ��5-7λ
	case 2:
		Mod = (TA2CCTL2 & 0x00e0)>>5;	break;	        //��ȡ���ģʽ��OUTMOD1λ��5-7λ
	default:	return(0);
		}

	switch(Mod)											//����ģʽ�趨TACCRx
		{
	case 2: case 6:		  /*����ģʽ2,6ʱ����Ҫ�ж���������ʱ�䣬��ͬʱ�趨TA0CCR1/2 ��ֵ*/
		{
			TA2CCR1 = Duty;
			TA2CCR2 = TA2CCR1-Dead;  				break;
		}
	case 7: if(Channel==1) TA2CCR1 = Duty;
	        if(Channel==2) TA2CCR2 = Duty;			break;
	case 3:	if(Channel==1) TA2CCR1 = TA2CCR0-Duty;
			if(Channel==2) TA2CCR2 = TA2CCR0-Duty;	break;
		default: return(0);
		}
	return (1);
}
