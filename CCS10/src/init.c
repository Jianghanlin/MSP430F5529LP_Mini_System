#include <ADS1118.h>
#include <DAC8571.h>
#include <SSD1351.h>
//#include "wdt.h"
#include "ucs.h"
//#include "soft_i2c.h"
#include "usci_a0_spi.h"
//#include "usci_b0_i2c.h"
//#include "usci_b1_spi.h"
//#include "led.h"
//#include "key.h"
//#include "DS18B20.h"
#include "RSCG12864B.h"
#include "AT24C02.h"
void device_init(void)
{
    ucs_init(); //内部时钟初始化

    //wdt_init(); //看门狗初始化

    /*
     usci_a0_spi_init(); //通用异步通信接口USCIA0组初始化
     ssd1351_init(); //oled屏幕初始化
     */

    RSCG12864B_init();
    //ADS1118_Init();
    //DAC8571_Init();
    //DS18B20_Init();
    //usci_b0_i2c_init();
    //soft_i2c_init();
    //usci_b1_spi_init();
    //led_init();
    //AT24C02_init();
    // key_init();
}

