#include "msp430.h"
#include "define.h"
#include "RSCG12864B.h"

void I2C_Clock(void)
{
    SCL_H();
    delay_us(50);
    SCL_L();
    delay_us(50);
}

void Busy(void)
{
    while ((BUSYIN) == BIT4)
        ;
}

void I2C_Start(void)
{
    Busy();
    SCL_H();
    delay_us(50);
    SDA_L();
    delay_us(50);
    SCL_L();
    delay_us(50);
}

/***********************************************************************

 ************************************************************************/
void I2C_Stop(void)
{
    SDA_L();
    delay_us(50);
    SCL_H();
    delay_us(50);
    SDA_H();
    delay_us(50);
    SCL_L();
    delay_us(50);
}

void I2C_Write_Byte(uchar data)
{
    uchar i;
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
            SDA_H();
        else
            SDA_L();
        data = data << 1;
        I2C_Clock();
    }
    I2C_Clock();
}

void I2C_Ack(void)
{
    SDA_L();
    I2C_Clock();
    SDA_H();
}

/***********************************************************************

 ***********************************************************************/
void reset(uchar address)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x01);
    I2C_Stop();
}

/***********************************************************************

 ***********************************************************************/
void clear(uchar address)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x10);
    I2C_Stop();
}

/***********************************************************************

 ***********************************************************************/
void display_on(uchar address)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x11);
    I2C_Stop();
}

/***********************************************************************

 ***********************************************************************/
void display_off(uchar address)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x12);
    I2C_Stop();
}

/***********************************************************************

 ***********************************************************************/
void brightness(uchar address, uchar n)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x13);
    I2C_Write_Byte(n);
    I2C_Stop();
}

/***********************************************************************

 ***********************************************************************/
void draw_pixel(uchar address, uchar x, uchar y)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x30);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Stop();
}

/***********************************************************************

 ***********************************************************************/
void delete_pixel(uchar address, uchar x, uchar y)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x31);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void draw_line(uchar address, uchar x1, uchar y1, uchar x2, uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x32);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void delete_line(uchar address, uchar x1, uchar y1, uchar x2, uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x33);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void draw_rectangle(uchar address, uchar x1, uchar y1, uchar x2, uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x34);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void delete_rectangle(uchar address, uchar x1, uchar y1, uchar x2, uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x35);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void draw_fill_rectangle(uchar address, uchar x1, uchar y1, uchar x2, uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x36);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void delete_fill_rectangle(uchar address, uchar x1, uchar y1, uchar x2,
uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x37);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void draw_circle(uchar address, uchar x, uchar y, uchar r)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x38);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(r);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void delete_circle(uchar address, uchar x, uchar y, uchar r)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x39);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(r);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void draw_fill_circle(uchar address, uchar x, uchar y, uchar r)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x3A);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(r);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void delete_fill_circle(uchar address, uchar x, uchar y, uchar r)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x3B);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(r);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void inversely_area(uchar address, uchar x1, uchar y1, uchar x2, uchar y2)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x38);
    I2C_Write_Byte(x1);
    I2C_Write_Byte(y1);
    I2C_Write_Byte(x2);
    I2C_Write_Byte(y2);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void display_bmp(uchar address, uint n)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x3d);
    I2C_Write_Byte(n >> 8);
    I2C_Write_Byte(n);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void display_bmp_block(uchar address, uint n, uchar px, uchar py, uchar x,
uchar y,
                       uchar w, uchar h)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x3E);
    I2C_Write_Byte(n >> 8);
    I2C_Write_Byte(n);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(px);
    I2C_Write_Byte(py);
    I2C_Write_Byte(w);
    I2C_Write_Byte(h);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void cursor_p(uchar address, uchar x, uchar y)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x29);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Stop();
}
/***********************************************************************
 ***********************************************************************/
void x_spacing_p(uchar address, uchar xs)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x2A);
    I2C_Write_Byte(xs);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_8x16_p(uchar address, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x2B);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_8x16_xy_p(uchar address, uchar x, uchar y, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x29);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x2B);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_8x16_p(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x2B);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_8x16_xy_p(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x29);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x2B);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_16_p(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x2C);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_16_xy_p(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x29);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x2C);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_5x7_P(uchar address, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x2D);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_5x7_xy_P(uchar address, uchar x, uchar y, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x29);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x2D);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_5x7_P(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x2D);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_5x7_xy_P(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x29);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x2D);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void cursor(uchar address, uchar x, uchar y)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void spacing(uchar address, uchar xs, uchar ys)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x21);
    I2C_Write_Byte(xs);
    I2C_Write_Byte(ys);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_5x7(uchar address, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x24);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/

void print_ulong_6x12(uchar address, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x25);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_8x16(uchar address, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x26);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_5x7_xy(uchar address, uchar x, uchar y, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x24);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_6x12_xy(uchar address, uchar x, uchar y, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x25);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_ulong_8x16_xy(uchar address, uchar x, uchar y, ulong n)
{
    ulong i, temp;
    uchar t = 0;
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x26);
    if (n == 0)
    {
        I2C_Write_Byte(0x30);
    }
    else
    {
        for (i = 1000000000; i >= 1; i = i / 10)
        {
            temp = n / i;
            if (t == 0 && temp)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
                t = 1;
            }
            else if (t == 1)
            {
                I2C_Write_Byte(temp % 10 + 0x30);
            }
        }
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_12(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x27);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}
/***********************************************************************
 ***********************************************************************/
void print_string_16(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x28);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_12_xy(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x27);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}
/***********************************************************************
 ***********************************************************************/
void print_string_16_xy(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x28);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_5x7(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x24);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_6x12(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x25);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_8x16(uchar address, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x26);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_5x7_xy(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x24);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_6x12_xy(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x25);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

/***********************************************************************
 ***********************************************************************/
void print_string_8x16_xy(uchar address, uchar x, uchar y, char *ptr)
{
    I2C_Start();
    I2C_Write_Byte(address);
    I2C_Write_Byte(0x20);
    I2C_Write_Byte(x);
    I2C_Write_Byte(y);
    I2C_Write_Byte(0x26);
    while (*ptr != '\0')
    {
        I2C_Write_Byte(*ptr++);
    }
    I2C_Write_Byte(0x00);
    I2C_Stop();
}

void RSCG12864B_init()
{
    P1DIR |= BIT2 + BIT3;
    P3DIR &= ~ BIT5;
    SCL_L();
    I2C_Stop();
    delay_ms(1000);
    brightness(0, 0xff);
}

