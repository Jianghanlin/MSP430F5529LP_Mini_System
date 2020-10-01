/*
 * LMT70.c
 *
 *  Created on: 2020年9月29日
 *      Author: www14
 */

#ifndef SRC_LMT70_C_
#define SRC_LMT70_C_
#include <math.h>

double LMT70_Temp(float v) //传入参数为模拟电压，单位为V
{
    double temp = 0;
    float mv = 0;
    mv = v * 1000;
    temp = ((-1.809628) * pow(10, -9)) * pow(mv, 3)
            + ((-3.325395) * pow(10, -6)) * pow(mv, 2) + (-1.814103) * 0.1 * mv
            + 2.055894 * 100;
    //3阶温度拟合曲线，temp的单位为摄氏度，mv的单位为mV
    return temp;
}

#endif /* SRC_LMT70_C_ */
