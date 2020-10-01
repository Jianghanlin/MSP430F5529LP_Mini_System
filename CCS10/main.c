/*
 * main.c
 ** --------key------------
 *  P2.0 P2.2 P2.4 P2.5
 * -----------------------
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ------------------------------------------------
 ---------SOFT_I2C-----   *  ---------SOFT_SPI-----   * --------SSD1351--------    * ------clock out-----
 * PORT     TYPE    PIN      * PORT     TYPE    PIN      * PORT     TYPE    PIN       *      ACLK:  P1.0
 * SDA      INOUT   P3.0     * MOSI     OUT     P3.3     * RES      OUT     P3.6      *      SMCLK: P2.2
 * SCL      OUT     P3.1     * MISO     IN      P3.4     * DC       OUT     P3.7      *      MCLK:  P7.7
 * -----------------------   * SCK      OUT     P2.7     * CS       OUT     P1.4
 * SCK      OUT     P1.5(SPI)
 * MOSI     OUT     P1.7(SPI)
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 * -----USCI_A0_SPI-------  * -----USCI_A1_SPI-------    * -----USCI_B0_SPI---------  * -----USCI_B1_SPI---------
 * PORT     TYPE    PIN     * PORT     TYPE    PIN       * PORT     TYPE    PIN       * PORT     TYPE    PIN
 * MOSI     OUT     P3.3    * MOSI     OUT     P4.4      * MOSI     OUT     P3.0      * MOSI     OUT     P4.1
 * MISO     IN      P3.4    * MISO     IN      P4.5      * MISO     IN      P3.1      * MISO     IN      P4.2
 * SCK      OUT     P2.7    * SCK      OUT     P4.0      * SCK      OUT     P3.2      * SCK      OUT     P4.3
 * ----------------------   * ----------------------     * ---------------------      * ---------------------

 * -----USCI_B1_I2C---------
 * PORT     TYPE    PIN
 * SDA      INOUT   P4.1
 * SCL      OUT     P4.2
 * -------------------------
 */

#include <msp430.h>
#include "SSD1351.h"
#include "fonts.h"
#include "init.h" //初始化相关函数
#include "user.h" //用户程序相关函数
#include "AT24C02.h"
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //关狗
    device_init();      //内部资源初始化函数
    user_init();       //用户函数初始化
    while (1)
    {
        ;
        //__bis_SR_register(LPM0_bits + GIE);
    }
}

