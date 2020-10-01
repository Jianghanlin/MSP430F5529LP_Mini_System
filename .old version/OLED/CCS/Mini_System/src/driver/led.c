/*
 * led.c
 *
 *  Created on: 2018-02-13 15:53
 *      Author: Jack Chen <redchenjs@live.com>
 *  Fixed on :  2018-05-25 11:14
 *      Author: art-j <jjw903427521@gmail.com>
 */


#include <msp430.h>

void led_on(void)
{
    P1OUT |= BIT0;
}

void led_off(void)
{
    P1OUT &=~BIT0;
}

void led_init(void)
{
    P1DIR |= BIT0;
    led_on();
}
