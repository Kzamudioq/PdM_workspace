#include "API_delay.h"

void delayInit(delay_t *delay, tick_t duration) {
   delay->duration = duration;
   delay->running = false;
}

bool_t delayRead(delay_t *delay) {
   if (!delay->running) {
      delay->startTime = HAL_GetTick();
      delay->running = true;
      return false;
   } else {
      tick_t currentTime = HAL_GetTick();
      if (currentTime - delay->startTime >= delay->duration) {
         delay->running = false;
         return true;
      } else {
         return false;
      }
   }
}

void delayWrite(delay_t *delay, tick_t duration) {
   delay->duration = duration;
}
