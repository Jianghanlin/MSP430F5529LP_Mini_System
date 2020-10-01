/*
 * DAC8571.c
 *
 *  Created on: 2015-7-8
 *      Author: Administrator
 */
#include <msp430f5529.h>
#include "define.h"
#define VREF 3.28

#define SCL_H P3OUT |= BIT1 //IIC
#define SDA_H P3OUT |=BIT0 ;  //IIC
#define SCL_L P3OUT &= ~BIT1 ; //IIC
#define SDA_L P3OUT &= ~BIT0 ;  //IIC
#define SDA_DIRIN  P3DIR &= ~BIT0
#define SDA_DIROUT P3DIR |= BIT0
#define SDA_IN  P3IN&=BIT0

uint i, n;
uchar ack = 0;

void DAC8571_Init(void)
{
    P3DIR |= BIT1 + BIT0;
}

void IIC_START(void)
{
    SCL_H;                   //SCL
    delay_us(200);
    SDA_H
    ;
    delay_us(200);
    SDA_L
    ;                    //SCL
    delay_us(200);
}

void IIC_OVER(void)
{
    SCL_L
    ;
    SDA_H
    ;
    delay_us(400);
}

void IIC_STOP(void)
{
    SCL_L
    ;
    SDA_L
    ;
    delay_us(400);
    SCL_H;
    delay_us(100);
    SDA_H
    ;
    delay_us(400);
}

uchar IIC_TR(uint dat)
{
    uchar ack = 0;
    SDA_DIROUT;
    for (i = 0; i < 8; i++)
    {
        n = 7 - i;
        SCL_L
        ;
        delay_us(200);
        if (((dat & (1 << n)) >> n))
        {
            SDA_H
            ;
        }
        else
            SDA_L
        ;
        delay_us(200);
        SCL_H;
        delay_us(200);
    }
    SCL_L
    ;
    SDA_DIRIN;
    delay_us(200);
    ack = SDA_IN;
    delay_us(200);
    SCL_H;
    delay_us(200);
    return ack;
}

uchar DAC_Init(void)
{
    uchar ack = 0;
    IIC_START();   //IIC
    ack = IIC_TR(0x98);   //·¢ËÍµØÖ·
    if (ack != 0)
    {
        return ack;
    }
    IIC_OVER();
    IIC_TR(0x10);   //¿ØÖÆ¼Ä´æÆ÷Write temporary register and load DAC with data
    if (ack != 0)
    {
        return ack;
    }
    IIC_OVER();
    return 0;
}

void DAC8571_OUT(float num)
{
    uchar ack = 0, error = 0;
    uint dat = 0x98;
    uint dat0, dat1;
    if ((num - VREF) > 0.0)
    {
        error = 1;
    }
    DAC_Init();
    dat = (uint) ((num / VREF) * 65535);
    dat1 = ((dat & 0xff00) >> 8);
    ack = IIC_TR(dat1);
    if (ack != 0)
    {
        error = 1;
    }
    IIC_OVER();
    dat0 = (dat & 0x00ff);
    ack = IIC_TR(dat0);
    if (ack != 0)
    {
        error = 1;
    }
    IIC_STOP();

    while (error == 1)
        ;
}

