/*
 * AT24C02.h
 *
 *  Created on: 2020年9月26日
 *      Author: www14
 */

#ifndef SRC_AT24C02_H_
#define SRC_AT24C02_H_
#include "define.h"
#include "stdbool.h"
extern void AT24C02_init(void);
extern void EEPROM_Write_Byte(uchar device_address, uchar save_address,
                              uchar datasend); //EEPROM写字节函数，传入参数为设备地址，写地址，和数据

/*注意事项：
 1、根据调试，怀疑是厂家芯片的原因，只有A2A1A0=000才能读写成功，并且不支持多从机通讯，没有尝试过Atmel原厂芯片
 2、读数据时，由于写地址会自动+1，所以需要先将随机内容写入前一页，指针会自动+1，这时候再继续读用户之前写的地址处的内容*/

extern uchar EEPROM_CurrentAddr_Read(uchar address); //EEPROM读字节函数，传入参数为设备地址
extern void AT24C02_Test();
#endif /* SRC_AT24C02_H_ */
