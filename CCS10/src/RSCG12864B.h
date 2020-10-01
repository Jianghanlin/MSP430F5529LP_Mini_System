/*
 * 作者：江瀚林
 * 日期：2020.9.26
 * 内容：RSCG12864B 128*64模块代码
 * 芯片容量大小：256*8=256Byte
 * 使用方法：
 *
 */

#ifndef SRC_RSCG12864B_H_
#define SRC_RSCG12864B_H_

#include "define.h"
#define SCL_H()    P1OUT |=BIT2
#define SCL_L()    P1OUT &=~BIT2
#define SDA_H()    P1OUT |=BIT3
#define SDA_L()    P1OUT &=~BIT3
#define BUSYIN P3IN&BIT5
#define SDAIN P1IN&BIT3

extern void RSCG12864B_init();

extern void display_on(uchar address);

/***********************************************************************

 ***********************************************************************/
extern void display_off(uchar address);

/***********************************************************************

 ***********************************************************************/
extern void brightness(uchar address, uchar n);
/***********************************************************************

 ***********************************************************************/
extern void draw_pixel(uchar address, uchar x, uchar y);
/***********************************************************************

 ***********************************************************************/
extern void delete_pixel(uchar address, uchar x, uchar y);

/***********************************************************************
 ***********************************************************************/
extern void draw_line(uchar address, uchar x1, uchar y1, uchar x2, uchar y2);

/***********************************************************************
 ***********************************************************************/
extern void delete_line(uchar address, uchar x1, uchar y1, uchar x2, uchar y2);

/***********************************************************************
 ***********************************************************************/
extern void draw_rectangle(uchar address, uchar x1, uchar y1, uchar x2,
                           uchar y2);

/***********************************************************************
 ***********************************************************************/
extern void delete_rectangle(uchar address, uchar x1, uchar y1, uchar x2,
                             uchar y2);

/***********************************************************************
 ***********************************************************************/
extern void draw_fill_rectangle(uchar address, uchar x1, uchar y1, uchar x2,
                                uchar y2);

/***********************************************************************
 ***********************************************************************/
extern void delete_fill_rectangle(uchar address, uchar x1, uchar y1, uchar x2,
uchar y2);
/***********************************************************************
 ***********************************************************************/
extern void draw_circle(uchar address, uchar x, uchar y, uchar r);

/***********************************************************************
 ***********************************************************************/
extern void delete_circle(uchar address, uchar x, uchar y, uchar r);

/***********************************************************************
 ***********************************************************************/
extern void draw_fill_circle(uchar address, uchar x, uchar y, uchar r);

/***********************************************************************
 ***********************************************************************/
extern void delete_fill_circle(uchar address, uchar x, uchar y, uchar r);

/***********************************************************************
 ***********************************************************************/
extern void inversely_area(uchar address, uchar x1, uchar y1, uchar x2,
                           uchar y2);

/***********************************************************************
 ***********************************************************************/
extern void display_bmp(uchar address, uint n);

/**************************************************
 * 矩形绘制函数，传入参数(设备地址0x00,x1,y1,x2,y2)
 */
extern void delete_fill_rectangle(uchar address, uchar x1, uchar y1, uchar x2,
uchar y2);

extern void display_bmp_block(uchar address, uint n, uchar px, uchar py,
uchar x,
                              uchar y,
                              uchar w,
                              uchar h);

extern void cursor_p(uchar address, uchar x, uchar y);

extern void x_spacing_p(uchar address, uchar xs);

extern void print_ulong_8x16_p(uchar address, ulong n);

extern void print_ulong_8x16_xy_p(uchar address, uchar x, uchar y, ulong n);

extern void print_string_8x16_p(uchar address, char *ptr);

extern void print_string_8x16_xy_p(uchar address, uchar x, uchar y, char *ptr);

extern void print_string_16_p(uchar address, char *ptr);

extern void print_string_16_xy_p(uchar address, uchar x, uchar y, char *ptr);

extern void print_ulong_5x7_P(uchar address, ulong n);

extern void print_ulong_5x7_xy_P(uchar address, uchar x, uchar y, ulong n);

extern void print_string_5x7_P(uchar address, char *ptr);

extern void print_string_5x7_xy_P(uchar address, uchar x, uchar y, char *ptr);

extern void cursor(uchar address, uchar x, uchar y);

extern void spacing(uchar address, uchar xs, uchar ys);

extern void print_ulong_5x7(uchar address, ulong n);

extern void print_ulong_6x12(uchar address, ulong n);

extern void print_ulong_8x16(uchar address, ulong n);

extern void print_ulong_5x7_xy(uchar address, uchar x, uchar y, ulong n);

extern void print_ulong_6x12_xy(uchar address, uchar x, uchar y, ulong n);

extern void print_ulong_8x16_xy(uchar address, uchar x, uchar y, ulong n);

extern void print_string_12(uchar address, char *ptr);

extern void print_string_16(uchar address, char *ptr);

extern void print_string_12_xy(uchar address, uchar x, uchar y, char *ptr);

extern void print_string_16_xy(uchar address, uchar x, uchar y, char *ptr);

extern void print_string_5x7(uchar address, char *ptr);

extern void print_string_6x12(uchar address, char *ptr);

extern void print_string_8x16(uchar address, char *ptr);

extern void print_string_5x7_xy(uchar address, uchar x, uchar y, char *ptr);

extern void print_string_6x12_xy(uchar address, uchar x, uchar y, char *ptr);

extern void print_string_8x16_xy(uchar address, uchar x, uchar y, char *ptr);
#endif
