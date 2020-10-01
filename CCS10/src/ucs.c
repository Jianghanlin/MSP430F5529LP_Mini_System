#include <msp430f5529.h>
//IO引脚能够复用为时钟输出，启用需取消注释函数ucs_init中line53、54、55行的引脚设置
#define SET_ACLK_OUT    P1SEL |= BIT0; P1DIR |= BIT0    // 设置P1.0为ACLK输出
#define SET_SMCLK_OUT   P2SEL |= BIT2; P2DIR |= BIT2    // 设置P2.2为SMCLK输出
#define SET_MCLK_OUT    P7SEL |= BIT7; P7DIR |= BIT7    // 设置P7.7为MCLK输出

//这个部分英文我也看不懂-_-，反正就是配置电源等级
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
 *MSPF5529时钟系统包含5个时钟源：
 *LFXT1 外部低频振荡源，32.768KHZ，可以用作FLL的参照源
 *XT2 外部高频振荡源，4MHZ
 *VLO （Internal very low）内部低耗低频振荡源，典型为10KHZ，精度一般
 *REFO 内部低频参照源，32.768KHZ，常被用作锁相环FLL的基准频率，精度很高，不使用时不消耗电源，其设置往往要参考LPM 模式的的设置
 *DCO内部数字控制振荡源，一般通过FLL来设置
 ----------------------------------------------------------
 *通常使用3种时钟信号，它们都来自于上述5个信号源：
 *ACLK （Auxiliary clock）辅助时钟，其时钟源可由软件控制从XT1、REFOC、VLO、DCO、DCOCLKDIV、XT2里面选取。其中DCOCLKDIV 是由DCO 经1、2、4、8、16或者32分频得到。注意，ACLK 同样可以再次被1、2、4、8、16或者32分频。
 *MCLK （Master clock）主时钟，其特性与ACLK 一模一样。
 *SMCLK （Subsystem master clock）子系统时钟，其特性与ACLK 一模一样。
 *
 ------------------------------------------------------------
 *DCO 模块在MSP430F5529系列芯片中非常重要
 *DCO 因为从MSP430F4XX开始，MSP430引用了FLL模块
 *FLL即锁相环，可以通过倍频的方式提高系统时钟频率，进而提高系统的运行速度。
 */

void ucs_init(void)
{
    // SET_MCLK_OUT;    开启MCLK输出
    // SET_ACLK_OUT;    开启ACLK输出
    // SET_SMCLK_OUT;   开启SMCLK输出

    //为了使芯片能够达到25MHz的高频，需要提供更多的能量，提升电压到最高等级，但是注意这个函数一次只能提高一级
    set_vcore_up(0x01);
    set_vcore_up(0x02);
    set_vcore_up(0x03);

    UCSCTL3 = SELREF_2;       // 锁相环FLL的参考时钟源选择为REFO=32.768kHz
    UCSCTL4 |= SELA_2;        // 设置辅助时钟ACLK =32.768kHz

    __bis_SR_register(SCG0);    //该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时MCLK 暂停工作
    UCSCTL0 = 0;        //先清零，FLL 运行时，该寄存器系统会自动配置，不用管
    UCSCTL1 = DCORSEL_7;        //设置数字时钟的频率区间区包含频率50MHz，一共有8档
    UCSCTL2 = FLLD_0 + 762;
    /*FLLD为预分频器，0为1分频
     *FLLN为倍频系数，占8位，最大值为2^8-1=255
     *数控振荡器输出频率的计算公式=1*(762 + 1) * 32768 = 25MHz=现在CPU的频率
     */
    __bic_SR_register(SCG0);

    /*     设置自定义时钟需要等待一段时间，具体时间计算公式，等待的时间=分频系数*32*32*倍频后的频率/FLL的参考时钟频率
     此处为1*32 x 32 x 25 MHz / 32,768 Hz=780k MCLK cycles for DCO to settle*/
    __delay_cycles(782000);
    // 一直循环直到XT1,XT2 & DCO稳定，只有在这种情况下DCO才会稳定
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    }
    while (SFRIFG1 & OFIFG);                  // Test oscillator fault flag

}
