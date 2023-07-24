#include "API_delay.h"

/* Inicializa la estructura de retardo no bloqueante */
void delayInit(delay_t* delay, tick_t duration) {
   delay->duration = duration;
   delay->running = false;
}

/* Lee el retardo no bloqueante y devuelve true si ha finalizado */
bool_t delayRead(delay_t* delay) {
   if (!delay->running) {
      // Si el retardo no estaba en ejecución, se inicia y se registra el tiempo de inicio
      delay->startTime = HAL_GetTick();
      delay->running = true;
      return false;
   } else {
      // Si el retardo está en ejecución, se verifica si ha finalizado
      tick_t currentTime = HAL_GetTick();
      tick_t elapsedTime = currentTime - delay->startTime;

      if (elapsedTime >= delay->duration) {
         // Si ha pasado el tiempo establecido, se finaliza el retardo y devuelve true
         delay->running = false;
         return true;
      } else {
         // Si el retardo aún no ha finalizado, devuelve false
         return false;
      }
   }
}

/* Actualiza la duración del retardo no bloqueante */
void delayWrite(delay_t* delay, tick_t duration) {
   delay->duration = duration;
}
