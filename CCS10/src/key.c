#include <msp430.h>
//������ʼ��
void key_init(void)
{
    P2DIR &= ~(BIT0 + BIT2 + BIT4 + BIT5); //ʹ�õ�P2.0��P2.2��P2.4��P2.5
    P2REN |= BIT0 + BIT2 + BIT4 + BIT5;
    P2OUT |= BIT0 + BIT2 + BIT4 + BIT5;
}
