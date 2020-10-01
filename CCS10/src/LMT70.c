/*
 * LMT70.c
 *
 *  Created on: 2020��9��29��
 *      Author: www14
 */

#ifndef SRC_LMT70_C_
#define SRC_LMT70_C_
#include <math.h>

double LMT70_Temp(float v) //�������Ϊģ���ѹ����λΪV
{
    double temp = 0;
    float mv = 0;
    mv = v * 1000;
    temp = ((-1.809628) * pow(10, -9)) * pow(mv, 3)
            + ((-3.325395) * pow(10, -6)) * pow(mv, 2) + (-1.814103) * 0.1 * mv
            + 2.055894 * 100;
    //3���¶�������ߣ�temp�ĵ�λΪ���϶ȣ�mv�ĵ�λΪmV
    return temp;
}

#endif /* SRC_LMT70_C_ */
