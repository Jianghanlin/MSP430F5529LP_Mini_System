/*
 * TA_PWM.c
 * ������PWM�⺯����������TA��������PWM��
 *  Created on: 2015-11-20
 *  Author: yumin
 */

#include "msp430F5529.h"
#define Dead 1											//Ԥ������ʱ�䣬��TA��clkΪ��λ

#define TA01_SET 	P1SEL |= BIT2; P1DIR |= BIT2		//P1.2
#define TA02_SET 	P1SEL |= BIT3; P1DIR |= BIT3		//P1.3
#define TA03_SET 	P1SEL |= BIT4; P1DIR |= BIT4		//P1.4
#define TA04_SET 	P1SEL |= BIT5; P1DIR |= BIT5		//P1.5

#define TA01_OFF 	P1SEL &= ~BIT2 						//P1.2
#define TA02_OFF 	P1SEL &= ~BIT3 						//P1.3
#define TA03_OFF 	P1SEL &= ~BIT4 						//P1.4
#define TA04_OFF 	P1SEL &= ~BIT5						//P1.5
/*****************************************************************************************
* ��       �ƣ�TA0_PWM_Init()
* ��       �ܣ�TA0��ʱ����ΪPWM�������ĳ�ʼ�����ú���
* ��ڲ�����Clk:ʱ��Դ 'S'=SMCLK;   'A'=ACLK ;   'E'=TACLK(�ⲿ����)�� 'e'= TACLK(TACLKȡ��)
                    Div:ʱ�ӷ�Ƶϵ��: 1/2/4/8
		    Mode1:ͨ��1�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM��ģʽ3�� ��'D'��������PWM��ģʽ6����0=����
		    Mode2:ͨ��2�����ģʽ 'F'��Ϊ��ǰPWM��ģʽ7����'B'�ͺ�PWM ��ģʽ3����'D'��������PWM��ģʽ2����0=����
		    ����������������Ƶ�PWMʱ����ͨ������ʹ�ã��Ҿ�Ϊ����ģʽ��
* ���ڲ�����1��ʾ���óɹ���0��ʾ������������ʧ�ܡ�
* ˵       �� : �ڵ���PWM��غ���֮ǰ����Ҫ���øú�������TA��ģʽ��ʱ��Դ��
* ��       �� : TA0_PWM_Init('A',1,'F','P')TAʱ����ΪACLK,ͨ��1��ͨ��2��Ϊ��ǰPWM���
                   TA0_PWM_Init('S',4,'D','D')TAʱ����ΪSMCLK/4, ͨ��1Ϊ������PWM��ͨ��2Ϊ������PWM
                   TA0_PWM_Init('A',1,'F',0)TAʱ����ΪACLK,ͨ��1��ǰPWM�����ͨ��2����TA�á�
 ****************************************************************************************/
char TA0_PWM_Init(char Clk,char Div,char Mode1,char Mode2)
{
  TA0CTL =0;												// �����ǰ����

  switch(Mode1)												//Ϊ��ʱ��ѡ�����ģʽ
  {
  case 'F': case 'f':										//��ͨPWM
		  TA0CTL |=MC_1; break;								//����ʱ��Ϊ������
  case 'B':case 'b':
	  	  TA0CTL |=MC_1; break;								//����ʱ��Ϊ������
  case 'D': case 'd':										//����PWM
     	  TA0CTL |=MC_3; break;								//����ʱ��Ϊ��������
  default : return(0);										//��������������ò������󣬷���0
  }

  switch(Clk)  												//Ϊ��ʱ��TAѡ��ʱ��Դ
  {
    case 'A': case 'a':  	TA0CTL|=TASSEL_1; break;   		//ACLK
    case 'S': case 's': 	TA0CTL|=TASSEL_2; break;  		//SMCLK
    case 'E':            		TA0CTL|=TASSEL_0; break;  	//�ⲿ����(TACLK)
    case 'e':          			TA0CTL|=TASSEL_3; break;   	//�ⲿ����(TACLKȡ��)
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Div) 												//Ϊ��ʱ��TAѡ���Ƶϵ��
  {
    case 1:   TA0CTL|=ID_0; break;   						//1
    case 2:   TA0CTL|=ID_1; break;   						//2
    case 4:   TA0CTL|=ID_2; break;  						//4
    case 8:   TA0CTL|=ID_3; break;  						//8
    default :  return(0);  									//���ò������󣬷���0
  }
  switch(Mode1)										 		//����PWMͨ��1�����ģʽ��
  {
     case 'F':	case 'f':
              TA0CCTL1 = OUTMOD_7;
              TA01_SET;
              break;
     case 'B':	case 'b':
              TA0CCTL1 = OUTMOD_3;
              TA01_SET;
              break;
     case 'D': case'd':
	     TA0CCTL1 = OUTMOD_6;
    	     TA01_SET;
    	     break;
      case '0':case 0:   							        //�������Ϊ����
             TA01_OFF;   									//TA0.1�ָ�Ϊ��ͨIO��
              break;
     default :  return(0); 							  		//���ò������󣬷���0
  }
  switch(Mode2) 											//����PWMͨ��2�����ģʽ��
  {
      case 'F':	 case 'f':
              TA0CCTL2 = OUTMOD_7;
              TA02_SET;  break;
       case 'B':	case 'b':
              TA0CCTL2 = OUTMOD_3;
              TA02_SET;
                break;
       case 'D': case 'd':
	       	   TA0CCTL2 = OUTMOD_2;
	       	   TA02_SET;
	       	   break;
       case '0':case 0:   									//�������Ϊ����
           	 	TA02_OFF;   							 	//TA0.1�ָ�Ϊ��ͨIO��
           	 	break;
       default :  return(0); 								//���ò������󣬷���0
    }
  return(1);
}
/****************************************************************************************
* ��       �ƣ�TA0_PWM_SetPeriod()
* ��       �ܣ�����PWM������������
* ��ڲ�����Channel: TA0=0, TA1=1
*                     Period:����(0~65535) ʱ�Ӹ���
* ���ڲ�����1�����óɹ�     0������ʧ��
* ˵       �� : ��ͨPWM�������PWM�������һ��
* ��       �� : TA0_PWM_SetPeriod(500)����PWM��������Ϊ500��1000��ʱ������
 ****************************************************************************************/
char TA0_PWM_SetPeriod(unsigned int Period)
{
	if (Period>65535)	return(0);
	 TA0CCR0 = Period;
	return(1);
}

/*****************************************************************************************
* ��    �ƣ�TA0_PWM_SetPermill()
* ��    �ܣ�����PWM�����ռ�ձ�(ǧ�ֱ�)
* ��ڲ�����Channel: ��ǰ���õ�ͨ����  1/2
            Duty: PWM�ߵ�ƽ��Чʱ���ǧ�ֱ� (0~1000)��
* ���ڲ�����1���óɹ���0����ʧ��
* ˵    ��: 1000=100.0%  500=50.0% ���������ơ�����ģʽʱ����channelͬʱ�趨��
* ��    ��: TA0_PWM_SetPermill(1,300)����PWMͨ��1������ռ�ձ�Ϊ30.0%
               TA0_PWM_SetPermill(2,825)����PWMͨ��2������ռ�ձ�Ϊ82.5%
 ****************************************************************************************/
char TA0_PWM_SetPermill(char Channel,unsigned int Duty)
{
	unsigned char Mod = 0;

	switch (Channel)									//���жϳ�ͨ���Ĺ���ģʽ
		{
	case 1:
		Mod = (TA0CCTL1& 0x00e0)>>5;		break;	    //��ȡ���ģʽ��OUTMOD0λ��5-7λ
	case 2:
		Mod = (TA0CCTL2 & 0x00e0)>>5;	break;	        //��ȡ���ģʽ��OUTMOD1λ��5-7λ
	default:	return(0);
		}

	switch(Mod)											//����ģʽ�趨TACCRx
		{
	case 2: case 6:		  /*����ģʽ2,6ʱ����Ҫ�ж���������ʱ�䣬��ͬʱ�趨TA0CCR1/2 ��ֵ*/
		{
			TA0CCR1 = Duty;
			TA0CCR2 = TA0CCR1-Dead;  				break;
		}
	case 7: if(Channel==1) TA0CCR1 = Duty;
	        if(Channel==2) TA0CCR2 = Duty;			break;
	case 3:	if(Channel==1) TA0CCR1 = TA0CCR0-Duty;
			if(Channel==2) TA0CCR2 = TA0CCR0-Duty;	break;
		default: return(0);
		}
	return (1);
	}
