/*
 * 作者：江瀚林
 * 日期：2020.9.26
 * 内容：AT24C02模块代码
 * 芯片容量大小：256*8=256Byte
 * 使用方法：
 *
 */

#ifndef SRC_AT24C02_C_
#define SRC_AT24C02_C_
#include "define.h"
#include <stdbool.h>
#include <msp430.h>

#define SDA_H()   P8DIR &=~BIT2
#define SDA_L()   P8DIR |=BIT2;P8OUT&=~BIT2
#define SCL_H()   P8DIR &=~BIT1
#define SCL_L()   P8DIR |=BIT1;P8OUT&=~BIT1
#define SDA_Val() P8IN&BIT2

void IIC_Start(void) //IIC开始信号
{
    SCL_L();
    SDA_H();
    delay_us(5);
    SCL_H();
    delay_us(5);
    SDA_L();
    delay_us(5);
    SCL_L();
    delay_us(5);
}

void IIC_Stop(void) //IIC停止信号
{
    SCL_L();
    SDA_L();
    delay_us(5);
    SCL_H();
    delay_us(5);
    SDA_H();
    delay_us(5);
    SCL_L();
    delay_us(5);
}

void IIC_Write_Byte(uchar data)
{
    uchar i = 0;
    for (i = 0; i < 8; i++) //1Byte=8bits，所以要重复发送8次
    {
        SCL_L();
        if ((data << i) & 0x80) //从最高位开始写
        {
            SDA_H();
        }
        else
        {
            SDA_L();
        }
        delay_us(5);
        SCL_H();
        delay_us(5);
        SCL_L();
        delay_us(5);
    }
}

void EEPROM_Software_Reset(void)
{
    uchar i = 0;
    IIC_Start();
    SCL_L();
    SDA_H();
    for (i = 0; i < 9; i++)
    {
        SCL_L();
        delay_us(2);
        SCL_H();
        delay_us(5);
        SCL_L();
        delay_us(2);
    }
    IIC_Start();
    IIC_Stop();
}

void AT24C02_init(void)
{
    P8DIR |= BIT1; //时钟线
    P8DIR &= ~BIT2; //数据线
    SCL_L();
    IIC_Stop();
    delay_ms(6);
    EEPROM_Software_Reset();
}

uchar IIC_Ack(void) //应答信号函数
{
    uchar flag = 0; //应答信号标志变量
    SCL_L();
    SDA_H(); //释放总线，解除MSP430的控制权，因为应答信号此时是AT24C02为主机
    delay_us(2);
    SCL_H();
    delay_us(5);
    P8DIR &= ~BIT2;
    flag = SDA_Val(); //读取此时SDA的引脚状态
    SCL_L();
    delay_us(5);
    P8DIR |= BIT2;
    return flag;
}

void IIC_NoAck(void)
{
    SCL_L();
    SDA_H(); //释放总线，解除MSP430的控制权，因为应答信号此时是AT24C02为主机
    delay_us(2);
    SCL_H();
    delay_us(5);
    SCL_L();
    delay_us(5);
}

uchar IIC_Read_Byte(void) //应答信号函数
{
    uchar data = 0, i; //应答信号标志变量
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        SCL_L();
        SDA_H(); //释放总线，解除MSP430的控制权，因为应答信号此时是AT24C02为主机
        delay_us(10);
        SCL_H();
        delay_us(5);
        P8DIR &= ~BIT2;
        if (SDA_Val())
            data |= 0x01;
        SCL_L();
        delay_us(5);
        P8DIR |= BIT2;
    }
    return data;
}

/*
 向AT24C02指定位置写一个字节
 1、发送开始位
 2、发送设备地址device_address
 3、应答信号Ack
 4、发送存储地址save_address
 5、应答信号Ack
 6、发送数据data
 7、应答信号Ack
 8、发送停止位
 */
void EEPROM_Write_Byte(uchar device_address, uchar save_address, uchar datasend) //EEPROM写字节函数
{
    IIC_Start();
    IIC_Write_Byte(device_address); //AT24C02的地址由原理图决定，图中A2A1A0接VCC，所以设备地址为1010+A2A1A0+R/W=1010111+(1是读，0是写)，所以读的地址是0xae
    IIC_Ack();
    IIC_Write_Byte(save_address);
    IIC_Ack();
    IIC_Write_Byte(datasend);
    IIC_Ack();
    IIC_Stop();
    delay_ms(100);
}

uchar EEPROM_CurrentAddr_Read(uchar address)
{
    uchar dataread = 0;
    IIC_Start();
    IIC_Write_Byte(address);
    IIC_Ack();
    dataread = IIC_Read_Byte();
    IIC_NoAck();
    IIC_Stop();
    return dataread;
}

void AT24C02_Test()
{
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
    EEPROM_Write_Byte(0xae, 0x11, 0x56);
    EEPROM_Write_Byte(0xae, 0x10, 0x11);
    if (EEPROM_CurrentAddr_Read(0xaf) == 0x56)
    {
        P4OUT |= BIT7;
    }
}

#endif /* SRC_AT24C02_C_ */

