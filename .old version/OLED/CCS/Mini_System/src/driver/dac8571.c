/*
 * dac8571.c
 *
 *  Created on: 2018-05-17 20:43
 *      Author: Jack Chen <redchenjs@live.com>
 *  Fixed on :  2018-05-25 11:14
 *      Author: art-j <jjw903427521@gmail.com>
 */


#include <stdint.h>

#include <inc/device/soft_i2c.h>
#include <inc/device/usci_b0_i2c.h>

#define DAC8571_I2C_ADDRESS 0x4c
#define DAC8571_UPDATE_REG  0x10

#define TAG "dac8571"

void dac8571_set_output(uint16_t value)
{
    unsigned char temp[3] = {0};
    temp[0] = DAC8571_UPDATE_REG;
    temp[1] = value >> 8;
    temp[2] = value & 0xff;
//    usci_b0_i2c_transmit_frame(DAC8571_I2C_ADDRESS, temp, 3);
    soft_i2c_transmit_frame(DAC8571_I2C_ADDRESS, temp, 3);
}

void dac8571_init(void)
{
    dac8571_set_output(0x0000);
}
