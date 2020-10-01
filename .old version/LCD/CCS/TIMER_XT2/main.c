#include<MSP430F5529.h>
/*XT2��ʱ��*/
void SetVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	  P1SEL |= BIT0;P1DIR |= BIT0;	//����ACLK��
	  P2SEL |= BIT2;P2DIR |= BIT2;	//����SMCLK��
	  P7SEL |= BIT7;P7DIR |= BIT7;	//����MCLK��
	  P5SEL |= BIT2+BIT3;
	  UCSCTL6 &= ~XT2OFF;          	//��XT2
	  SetVcoreUp(3);
	  __bis_SR_register(SCG0);
	  UCSCTL0 =0;
	  UCSCTL1 = DCORSEL_7;                    //DCOƵ�ʷ�Χ��28.2MHZ����
	  UCSCTL2 = FLLD_0+24;		//D=16��N=1
	  UCSCTL3 = SELREF_5 + FLLREFDIV_2;    //n=8,FLLREFCLKʱ��ԴΪXT2CLK��
	  UCSCTL4=SELM_3+SELS_4+SELA_2;
	  __bic_SR_register(SCG0);
	  __delay_cycles(8192);
	  do
	  {
	  	UCSCTL7 &=~(XT2OFFG+DCOFFG+XT1LFOFFG);//���3��ʱ�Ӵ����־
	  	SFRIFG1&=~(OFIFG);//���ʱ�Ӵ����־λ
	  }while(SFRIFG1 & OFIFG);	//�����ʱ�Ӵ���
}
