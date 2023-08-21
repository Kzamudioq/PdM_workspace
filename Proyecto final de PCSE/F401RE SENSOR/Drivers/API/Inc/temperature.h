#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "stm32f4xx_hal.h"
#include <stdint.h>


float convertToCelsius(uint8_t tc1, uint8_t tc2);
float convertToFahrenheit(float celsius);
float calculateHumidity(uint8_t rh1, uint8_t rh2);
uint8_t calculateChecksum(uint8_t rh1, uint8_t rh2, uint8_t tc1, uint8_t tc2);


#endif /* TEMPERATURE */
