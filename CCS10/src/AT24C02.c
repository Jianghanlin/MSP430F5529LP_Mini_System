/*
 * ���ߣ������
 * ���ڣ�2020.9.26
 * ���ݣ�AT24C02ģ�����
 * оƬ������С��256*8=256Byte
 * ʹ�÷�����
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

void IIC_Start(void) //IIC��ʼ�ź�
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

void IIC_Stop(void) //IICֹͣ�ź�
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
    for (i = 0; i < 8; i++) //1Byte=8bits������Ҫ�ظ�����8��
    {
        SCL_L();
        if ((data << i) & 0x80) //�����λ��ʼд
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
    P8DIR |= BIT1; //ʱ����
    P8DIR &= ~BIT2; //������
    SCL_L();
    IIC_Stop();
    delay_ms(6);
    EEPROM_Software_Reset();
}

uchar IIC_Ack(void) //Ӧ���źź���
{
    uchar flag = 0; //Ӧ���źű�־����
    SCL_L();
    SDA_H(); //�ͷ����ߣ����MSP430�Ŀ���Ȩ����ΪӦ���źŴ�ʱ��AT24C02Ϊ����
    delay_us(2);
    SCL_H();
    delay_us(5);
    P8DIR &= ~BIT2;
    flag = SDA_Val(); //��ȡ��ʱSDA������״̬
    SCL_L();
    delay_us(5);
    P8DIR |= BIT2;
    return flag;
}

void IIC_NoAck(void)
{
    SCL_L();
    SDA_H(); //�ͷ����ߣ����MSP430�Ŀ���Ȩ����ΪӦ���źŴ�ʱ��AT24C02Ϊ����
    delay_us(2);
    SCL_H();
    delay_us(5);
    SCL_L();
    delay_us(5);
}

uchar IIC_Read_Byte(void) //Ӧ���źź���
{
    uchar data = 0, i; //Ӧ���źű�־����
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        SCL_L();
        SDA_H(); //�ͷ����ߣ����MSP430�Ŀ���Ȩ����ΪӦ���źŴ�ʱ��AT24C02Ϊ����
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
 ��AT24C02ָ��λ��дһ���ֽ�
 1�����Ϳ�ʼλ
 2�������豸��ַdevice_address
 3��Ӧ���ź�Ack
 4�����ʹ洢��ַsave_address
 5��Ӧ���ź�Ack
 6����������data
 7��Ӧ���ź�Ack
 8������ֹͣλ
 */
void EEPROM_Write_Byte(uchar device_address, uchar save_address, uchar datasend) //EEPROMд�ֽں���
{
    IIC_Start();
    IIC_Write_Byte(device_address); //AT24C02�ĵ�ַ��ԭ��ͼ������ͼ��A2A1A0��VCC�������豸��ַΪ1010+A2A1A0+R/W=1010111+(1�Ƕ���0��д)�����Զ��ĵ�ַ��0xae
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

