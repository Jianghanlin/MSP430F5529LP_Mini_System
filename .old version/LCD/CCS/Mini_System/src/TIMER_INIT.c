/*
 * TIMER_INIT.c
 *
 *  Created on: 2015��11��20��
 *      Author: yumin
 *
 *      ��ʱ������ʹ�ñȽ�ģʽ������Ϊ��ʱ����ʹ�ã�Ҳ����ʹ�ò���ģʽ����������
 *
 *      ����ģʽ�±�����ʹ�����ַ�������Ƶ�ʣ����ڣ�ռ�ձ�
 */
#include <msp430F5529.h>

#define CAP_MODE 1           //TA0��ʱ��ʹ��ģʽ              0���Ƚϣ���ʱ��ģʽ     ��   1������ģʽ

#define SMCLK  4000000
#define mS     5             //��ʱ��ʹ��SMCLK��1��Ƶ�£������趨16ms���ı�ʱ��Դ���Ƶ�����Զ�ʱ����
#define count  mS*SMCLK/1000

void CAP1_deal();
void CAP2_deal();
void CAP3_deal();
void CAP4_deal();

/*-----------------------------------------------------Ƶ�ʣ�ռ�ձȣ���λ�������*/
unsigned int cap_count=0,
		     cap1value,cap2value;

unsigned int cap_flag=0,cap_finish=0,
             uptime=0,downtime=0,addtime=0;
/*--------------------------------------------------------------------*/
void TA0_Init(void)
{
#if CAP_MODE

//	P1DIR &=~ BIT2;
//	P1SEL |= BIT2;           //P1.2  CAPTURE1
//	P1DIR &=~ BIT3;
//	P1SEL |= BIT3;           //P1.3  CAPTURE2

	P1DIR &=~ BIT4;
	P1SEL |= BIT4;           //P1.4  CAPTURE3
	P1DIR &=~ BIT5;
	P1SEL |= BIT5;           //P1.5  CAPTURE4

//	TA0CCTL1 = CM_2 | CCIS_0 | SCS | CAP | CCIE;
//	TA0CCTL2 = CM_2 | CCIS_0 | SCS | CAP | CCIE;

	TA0CCTL3 = CM_2 | CCIS_0 | SCS | CAP | CCIE;
	TA0CCTL4 = CM_2 | CCIS_0 | SCS | CAP | CCIE;
	//������Ƚ�ģ������ж�����,�½��ز���,ͬ������,�����ڲ���ģʽ
	TA0CTL    =  TACLR | TASSEL_2 | ID_0 | MC_2;
	//��ʱ������,ѡ��ʱ��SMCLK,1��Ƶ,��������ģʽ

#else

	TA0CCTL0 |= CCIE;       //�ȽϹ���0(��ʱ����)����CCIFGλ�ж�
    TA0CCR0   = count;      //������ֵ
//	TA0CCTL1 |= CCIE;		//�ȽϹ���1�����ж�
//	TA0CCR1   = 10;		    //����Ҫ�Ƚϵ���ֵ
//	TA0CCTL2 |= CCIE;		//�ȽϹ���2�����ж�
//	TA0CCR2   = 100;		//����Ҫ�Ƚϵ���ֵ
//	TA0CCTL3 |= CCIE;		//�ȽϹ���3�����ж�
//	TA0CCR3   = 1000;		//����Ҫ�Ƚϵ���ֵ
//	TA0CCTL4 |= CCIE;		//�ȽϹ���4�����ж�
//	TA0CCR4   = 10000;		//����Ҫ�Ƚϵ���ֵ

	TA0CTL    = TACLR | TASSEL_2 | MC_1 | TAIE;
	//���������㣬ѡ��SCLK��Ϊʱ�ӣ�ѡ�É�����ģʽ�������ж�
#endif
}

void TA1_Init(void)
{
	TA1CCTL0 |= CCIE;       //�ȽϹ���0(��ʱ����)����CCIFGλ�ж�
    TA1CCR0   = count;      //������ֵ
//	TA1CCTL1 |= CCIE;		//�ȽϹ���1�����ж�
//	TA1CCR1   = 10;		    //����Ҫ�Ƚϵ���ֵ
//	TA1CCTL2 |= CCIE;		//�ȽϹ���2�����ж�
//	TA1CCR2   = 100;		//����Ҫ�Ƚϵ���ֵ
//	TA1CCTL3 |= CCIE;		//�ȽϹ���3�����ж�
//	TA1CCR3   = 1000;		//����Ҫ�Ƚϵ���ֵ
//	TA1CCTL4 |= CCIE;		//�ȽϹ���4�����ж�
//	TA1CCR4   = 10000;		//����Ҫ�Ƚϵ���ֵ

	TA1CTL    = TACLR | TASSEL_2 | MC_1 | TAIE;
	//���������㣬ѡ��SCLK��Ϊʱ�ӣ�ѡ�É�����ģʽ�������ж�
}

void TA2_Init(void)
{
	TA2CCTL0 |= CCIE;       //�ȽϹ���0(��ʱ����)����CCIFGλ�ж�
    TA2CCR0   = count;      //������ֵ
//	TA2CCTL1 |= CCIE;		//�ȽϹ���1�����ж�
//	TA2CCR1   = 10;		    //����Ҫ�Ƚϵ���ֵ
//	TA2CCTL2 |= CCIE;		//�ȽϹ���2�����ж�
//	TA2CCR2   = 100;		//����Ҫ�Ƚϵ���ֵ
//	TA2CCTL3 |= CCIE;		//�ȽϹ���3�����ж�
//	TA2CCR3   = 1000;		//����Ҫ�Ƚϵ���ֵ
//	TA2CCTL4 |= CCIE;		//�ȽϹ���4�����ж�
//	TA2CCR4   = 10000;		//����Ҫ�Ƚϵ���ֵ

	TA2CTL    = TACLR | TASSEL_2 | MC_1 | TAIE;
	//���������㣬ѡ��SCLK��Ϊʱ�ӣ�ѡ�É�����ģʽ�������ж�
}

void TB0_Init(void)
{
	TB0CCTL0 |= CCIE;       //�ȽϹ���0(��ʱ����)����CCIFGλ�ж�
    TB0CCR0   = count;      //������ֵ
//	TB0CCTL1 |= CCIE;		//�ȽϹ���1�����ж�
//	TB0CCR1   = 10;		    //����Ҫ�Ƚϵ���ֵ
//	TB0CCTL2 |= CCIE;		//�ȽϹ���2�����ж�
//	TB0CCR2   = 100;		//����Ҫ�Ƚϵ���ֵ
//	TB0CCTL3 |= CCIE;		//�ȽϹ���3�����ж�
//	TB0CCR3   = 1000;		//����Ҫ�Ƚϵ���ֵ
//	TB0CCTL4 |= CCIE;		//�ȽϹ���4�����ж�
//	TB0CCR4   = 10000;		//����Ҫ�Ƚϵ���ֵ

	TB0CTL    = TBCLR | TBSSEL_2 | MC_1 | TBIE;
	//���������㣬ѡ��SCLK��Ϊʱ�ӣ�ѡ�É�����ģʽ�������ж�
}




#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{

	//TA0CCR0 CCIFG0��λ, TAIFG��λ
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{

	//TA1CCR0 CCIFG0��λ, TAIFG��λ
}

#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{

	//TA2CCR0 CCIFG0��λ, TAIFG��λ
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
{

	//TB0CCR0 CCIFG0��λ, TBIFG��λ
}




#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
#if CAP_MODE

	  switch(__even_in_range(TA0IV,14))
	  {
	    case  0: break;                          // No interrupt
	    case  2: //CAP1_deal();
		         break;                          // CCR1
	    case  4: //CAP2_deal();
		         break;                          // CCR2
	    case  6: CAP3_deal();
	    	     break;                          // CCR3
	    case  8: CAP4_deal();
	    	     break;                          // CCR4
	    case 10: break;                          // CCR5
	    case 12: break;                          // CCR6
	    case 14: break;                          // overflow
	    default: break;
	  }

#else

	switch(__even_in_range(TA0IV,14))
	// ��仰����˼�ǣ�ֻ����TA0IV��ֵ����0--14�ڵ�ż��ʱ�Ż�ִ��switch�����ڵ���䡣
	{
		case 2:
		break;   //TA0CCR1 CCIFG1��λ
		case 4:  ;
		break;   //TA0CCR2 CCIFG2��λ
		case 6:  ;
		break;   //TA0CCR3 CCIFG3��λ
		case 8:  ;
		break;   //TA0CCR4 CCIFG4��λ
		case 14:
		break;   //TAIFG��λ
		default: break;
	}
#endif
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{
	switch(__even_in_range(TA1IV,14))
	// ��仰����˼�ǣ�ֻ����TA1IV��ֵ����0--14�ڵ�ż��ʱ�Ż�ִ��switch�����ڵ���䡣
	{
		case 2:
		break;   //TA1CCR1 CCIFG1��λ
		case 4:  ;
		break;   //TA1CCR2 CCIFG2��λ
		case 6:  ;
		break;   //TA1CCR3 CCIFG3��λ
		case 8:  ;
		break;   //TA1CCR4 CCIFG4��λ
		case 14:
		break;   //TAIFG��λ
		default: break;
	}
}

#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
	switch(__even_in_range(TA2IV,14))
	// ��仰����˼�ǣ�ֻ����TA2IV��ֵ����0--14�ڵ�ż��ʱ�Ż�ִ��switch�����ڵ���䡣
	{
		case 2:
		break;   //TA2CCR1 CCIFG1��λ
		case 4:  ;
		break;   //TA2CCR2 CCIFG2��λ
		case 6:  ;
		break;   //TA2CCR3 CCIFG3��λ
		case 8:  ;
		break;   //TA2CCR4 CCIFG4��λ
		case 14:
		break;   //TAIFG��λ
		default: break;
	}
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
	switch(__even_in_range(TB0IV,14))
	// ��仰����˼�ǣ�ֻ����TB0IV��ֵ����0--14�ڵ�ż��ʱ�Ż�ִ��switch�����ڵ���䡣
	{
		case 2:
		break;   //TB0CCR1 CCIFG1��λ
		case 4:  ;
		break;   //TB0CCR2 CCIFG2��λ
		case 6:  ;
		break;   //TB0CCR3 CCIFG3��λ
		case 8:  ;
		break;   //TB0CCR4 CCIFG4��λ
		case 14:
		break;   //TBIFG��λ
		default: break;
	}
}

void CAP1_deal()
{
//	TA0CCTL1 &= ~CCIFG;     //��ȡ��Ӧ�ж�Ӳ���Զ�����
	if(cap_count == 0) TA0R=0;
	if(cap_count == 1) cap1value=TA0R;
	cap_count ++;
	if(cap_count >= 2) cap_count = 2;
}

void CAP2_deal()
{
//	TA0CCTL2 &= ~CCIFG;     //��ȡ��Ӧ�ж�Ӳ���Զ�����
	if(cap_count==1)   cap2value=TA0R;
}

void CAP3_deal()
{
//	TA0CCTL3&=~CCIFG;    //��ȡ��Ӧ�ж�Ӳ���Զ�����
	cap_flag++;
	if(cap_flag==1)
	  {
	   TA0CCTL3 |= CM_1;
	   TA0R=0;
	  }
	if(cap_flag==2)
	  {
	   downtime=TA0R;
	   TA0CCTL3 |= CM_2;
	   TA0R=0;
	  }
	if(cap_flag==3)
	  {
	   uptime=TA0R;
	   cap_flag=0;
	   cap_finish=1;
	  }

}

void CAP4_deal()
{
//	TA0CCTL4&=~CCIFG;    //��ȡ��Ӧ�ж�Ӳ���Զ�����
	if(cap_flag==1)
	  {
	   addtime=TA0R;
	  }
}


