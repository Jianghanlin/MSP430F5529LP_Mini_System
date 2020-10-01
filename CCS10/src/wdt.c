/*
 * wdt.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp430.h>

void wdt_init(void)
{
    WDTCTL = WDT_MDLY_0_5; //看门狗每0.5ms引发中断
    SFRIE1 |= WDTIE; //打开分中断
}
