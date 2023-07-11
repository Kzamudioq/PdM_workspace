#ifndef API_DELAY_H
#define API_DELAY_H

#include "stm32f4xx_hal.h"
#include <stdint.h> // Para incluir el tipo uint32_t
#include <stdbool.h> // Para incluir el tipo bool_t

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit(delay_t* delay, tick_t duration);
bool_t delayRead(delay_t* delay);
void delayWrite(delay_t* delay, tick_t duration);

#endif // API_DELAY_H
