/*
 * ads1118.h
 *
 *  Created on: 2018-05-17 11:23
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_DRIVER_ADS1118_H_
#define INC_DRIVER_ADS1118_H_

#define uint  unsigned int
#define uchar unsigned char

extern void ADS1118_Init();
extern float ADS1118(uchar port, uchar scale);

#endif /* INC_DRIVER_ADS1118_H_ */
