/*
 * define.h
 *
 *  Created on: 2020ƒÍ9‘¬26»’
 *      Author: www14
 */

#ifndef SRC_DEFINE_H_
#define SRC_DEFINE_H_

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define CPU_F ((double)25000000)                                          //CPU∆µ¬ 
#define delay_us(x) __delay_cycles((long)(CPU_F * (double)x / 1000000.0)) //—”≥ŸxŒ¢√Ó
#define delay_ms(x) __delay_cycles((long)(CPU_F * (double)x / 1000.0))    //—”≥Ÿx∫¡√Î

#endif /* SRC_DEFINE_H_ */
