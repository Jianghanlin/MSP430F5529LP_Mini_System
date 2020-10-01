/*
 * AT24C02.h
 *
 *  Created on: 2020��9��26��
 *      Author: www14
 */

#ifndef SRC_AT24C02_H_
#define SRC_AT24C02_H_
#include "define.h"
#include "stdbool.h"
extern void AT24C02_init(void);
extern void EEPROM_Write_Byte(uchar device_address, uchar save_address,
                              uchar datasend); //EEPROMд�ֽں������������Ϊ�豸��ַ��д��ַ��������

/*ע�����
 1�����ݵ��ԣ������ǳ���оƬ��ԭ��ֻ��A2A1A0=000���ܶ�д�ɹ������Ҳ�֧�ֶ�ӻ�ͨѶ��û�г��Թ�Atmelԭ��оƬ
 2��������ʱ������д��ַ���Զ�+1��������Ҫ�Ƚ��������д��ǰһҳ��ָ����Զ�+1����ʱ���ټ������û�֮ǰд�ĵ�ַ��������*/

extern uchar EEPROM_CurrentAddr_Read(uchar address); //EEPROM���ֽں������������Ϊ�豸��ַ
extern void AT24C02_Test();
#endif /* SRC_AT24C02_H_ */
