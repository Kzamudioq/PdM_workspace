#ifndef DHT22_H
#define DHT22_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

void microDelay(uint16_t delay);
uint8_t DHT22_Start(void);
uint8_t DHT22_Read(void);


#endif // DHT22_H
