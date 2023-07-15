#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t tick_t; // Tipo de dato para representar el tiempo en ticks
typedef bool bool_t; // Tipo de dato booleano

typedef struct {
   tick_t startTime; // Tiempo de inicio del retardo
   tick_t duration; // Duración del retardo
   bool_t running; // Estado de ejecución del retardo
} delay_t; // Estructura para representar un retardo

// Inicializa la estructura de retardo con la duración especificada
void delayInit(delay_t *delay, tick_t duration);

// Lee el estado del retardo
// Devuelve true si el retardo ha terminado, o false si aún está en curso
bool_t delayRead(delay_t *delay);

// Actualiza la duración del retardo con el valor especificado
void delayWrite(delay_t *delay, tick_t duration);

#endif /* API_DELAY_H */
