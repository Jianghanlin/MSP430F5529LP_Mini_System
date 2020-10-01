#include <msp430f5529.h>
//IO�����ܹ�����Ϊʱ�������������ȡ��ע�ͺ���ucs_init��line53��54��55�е���������
#define SET_ACLK_OUT    P1SEL |= BIT0; P1DIR |= BIT0    // ����P1.0ΪACLK���
#define SET_SMCLK_OUT   P2SEL |= BIT2; P2DIR |= BIT2    // ����P2.2ΪSMCLK���
#define SET_MCLK_OUT    P7SEL |= BIT7; P7DIR |= BIT7    // ����P7.7ΪMCLK���

//�������Ӣ����Ҳ������-_-�������������õ�Դ�ȼ�
void set_vcore_up(unsigned int level)
{
    // Open PMM registers for write
    PMMCTL0_H = PMMPW_H;
    // Set SVS/SVM high side new level
    SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
    // Set SVM low side to new level
    SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
    // Wait till SVM is settled
    while ((PMMIFG & SVSMLDLYIFG) == 0)
        ;
    // Clear already set flags
    PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
    // Set VCore to new level
    PMMCTL0_L = PMMCOREV0 * level;
    // Wait till new level reached
    if ((PMMIFG & SVMLIFG))
    {
        while ((PMMIFG & SVMLVLRIFG) == 0)
            ;
    }
    // Set SVS/SVM low side to new level
    SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;
}

/*
 *MSPF5529ʱ��ϵͳ����5��ʱ��Դ��
 *LFXT1 �ⲿ��Ƶ��Դ��32.768KHZ����������FLL�Ĳ���Դ
 *XT2 �ⲿ��Ƶ��Դ��4MHZ
 *VLO ��Internal very low���ڲ��ͺĵ�Ƶ��Դ������Ϊ10KHZ������һ��
 *REFO �ڲ���Ƶ����Դ��32.768KHZ�������������໷FLL�Ļ�׼Ƶ�ʣ����Ⱥܸߣ���ʹ��ʱ�����ĵ�Դ������������Ҫ�ο�LPM ģʽ�ĵ�����
 *DCO�ڲ����ֿ�����Դ��һ��ͨ��FLL������
 ----------------------------------------------------------
 *ͨ��ʹ��3��ʱ���źţ����Ƕ�����������5���ź�Դ��
 *ACLK ��Auxiliary clock������ʱ�ӣ���ʱ��Դ����������ƴ�XT1��REFOC��VLO��DCO��DCOCLKDIV��XT2����ѡȡ������DCOCLKDIV ����DCO ��1��2��4��8��16����32��Ƶ�õ���ע�⣬ACLK ͬ�������ٴα�1��2��4��8��16����32��Ƶ��
 *MCLK ��Master clock����ʱ�ӣ���������ACLK һģһ����
 *SMCLK ��Subsystem master clock����ϵͳʱ�ӣ���������ACLK һģһ����
 *
 ------------------------------------------------------------
 *DCO ģ����MSP430F5529ϵ��оƬ�зǳ���Ҫ
 *DCO ��Ϊ��MSP430F4XX��ʼ��MSP430������FLLģ��
 *FLL�����໷������ͨ����Ƶ�ķ�ʽ���ϵͳʱ��Ƶ�ʣ��������ϵͳ�������ٶȡ�
 */

void ucs_init(void)
{
    // SET_MCLK_OUT;    ����MCLK���
    // SET_ACLK_OUT;    ����ACLK���
    // SET_SMCLK_OUT;   ����SMCLK���

    //Ϊ��ʹоƬ�ܹ��ﵽ25MHz�ĸ�Ƶ����Ҫ�ṩ�����������������ѹ����ߵȼ�������ע���������һ��ֻ�����һ��
    set_vcore_up(0x01);
    set_vcore_up(0x02);
    set_vcore_up(0x03);

    UCSCTL3 = SELREF_2;       // ���໷FLL�Ĳο�ʱ��Դѡ��ΪREFO=32.768kHz
    UCSCTL4 |= SELA_2;        // ���ø���ʱ��ACLK =32.768kHz

    __bis_SR_register(SCG0);    //���﷨Ϊ�̶���ʽ����Ϊ�������ڵı�����λ��SCG0��ϵͳ����ģʽ�йأ���ʱMCLK ��ͣ����
    UCSCTL0 = 0;        //�����㣬FLL ����ʱ���üĴ���ϵͳ���Զ����ã����ù�
    UCSCTL1 = DCORSEL_7;        //��������ʱ�ӵ�Ƶ������������Ƶ��50MHz��һ����8��
    UCSCTL2 = FLLD_0 + 762;
    /*FLLDΪԤ��Ƶ����0Ϊ1��Ƶ
     *FLLNΪ��Ƶϵ����ռ8λ�����ֵΪ2^8-1=255
     *�����������Ƶ�ʵļ��㹫ʽ=1*(762 + 1) * 32768 = 25MHz=����CPU��Ƶ��
     */
    __bic_SR_register(SCG0);

    /*     �����Զ���ʱ����Ҫ�ȴ�һ��ʱ�䣬����ʱ����㹫ʽ���ȴ���ʱ��=��Ƶϵ��*32*32*��Ƶ���Ƶ��/FLL�Ĳο�ʱ��Ƶ��
     �˴�Ϊ1*32 x 32 x 25 MHz / 32,768 Hz=780k MCLK cycles for DCO to settle*/
    __delay_cycles(782000);
    // һֱѭ��ֱ��XT1,XT2 & DCO�ȶ���ֻ�������������DCO�Ż��ȶ�
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    }
    while (SFRIFG1 & OFIFG);                  // Test oscillator fault flag

}
