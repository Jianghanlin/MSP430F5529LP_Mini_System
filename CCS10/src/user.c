/*
 * user.cpp
 *
 *  Created on: 2020年9月29日
 *      Author: www14
 */

#include <stdio.h>
#include <SSD1351.h>
#include "ADS1118.h"
#include "fonts.h"
#include "DS18B20.h"
#include "LMT70.h"
#include <math.h>
#include "RSCG12864B.h"
#include <string.h>

void LMT70_temp_display() //依赖16Bit ADS1118，显示LMT70的温度
{
    double temp = 0;
    char print_temp[6] = { };
    temp = LMT70_Temp(ADS1118(4, 1));
    sprintf(print_temp, "%.2lf", temp);
    ssd1351_display_string(0, 0, print_temp, 0, White, Black);
}

void user_init(void)
{

}

void user_loop(void)
{
//    ssd1351_show_rainbow();
//    input_update();
//    measure_update();
//    control_update();
//    display_update();

}

