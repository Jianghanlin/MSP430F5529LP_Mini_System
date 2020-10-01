/*
 * define.h
 *
 *  Created on: 2020��9��26��
 *      Author: www14
 */

#ifndef SRC_DEFINE_H_
#define SRC_DEFINE_H_

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define CPU_F ((double)25000000)                                          //CPUƵ��
#define delay_us(x) __delay_cycles((long)(CPU_F * (double)x / 1000000.0)) //�ӳ�x΢��
#define delay_ms(x) __delay_cycles((long)(CPU_F * (double)x / 1000.0))    //�ӳ�x����

#endif /* SRC_DEFINE_H_ */
