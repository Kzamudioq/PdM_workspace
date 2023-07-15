#include "API_delay.h"

// Inicializa la estructura de retardo con la duración especificada
void delayInit(delay_t *delay, tick_t duration) {
   delay->duration = duration; // Establece la duración del retardo
   delay->running = false; // Establece el estado de ejecución del retardo como falso (no en ejecución)
}

// Lee el estado del retardo
// Devuelve true si el retardo ha terminado, o false si aún está en curso
bool_t delayRead(delay_t *delay) {
   if (!delay->running) { // Si el retardo no está en ejecución
      delay->startTime = HAL_GetTick(); // Obtiene el tiempo actual y lo guarda como inicio del retardo
      delay->running = true; // Cambia el estado de ejecución del retardo a verdadero (en ejecución)
      return false; // Indica que el retardo aún no ha terminado
   } else { // Si el retardo está en ejecución
      tick_t currentTime = HAL_GetTick(); // Obtiene el tiempo actual
      if (currentTime - delay->startTime >= delay->duration) { // Comprueba si el tiempo transcurrido es mayor o igual a la duración del retardo
         delay->running = false; // Cambia el estado de ejecución del retardo a falso (terminado)
         return true; // Indica que el retardo ha terminado
      } else {
         return false; // Indica que el retardo aún no ha terminado
      }
   }
}

// Actualiza la duración del retardo con el valor especificado
void delayWrite(delay_t *delay, tick_t duration) {
   delay->duration = duration; // Actualiza la duración del retardo
}
