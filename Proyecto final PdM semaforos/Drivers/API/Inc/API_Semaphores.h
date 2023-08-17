#ifndef API_SEMAFORO_H
#define API_SEMAFORO_H

#include <stdint.h>
#include "main.h"

typedef enum {
    SEMAPHORE_RED,
    SEMAPHORE_YELLOW,
    SEMAPHORE_GREEN,
} semaphoreState_t;

void api_semaforo_init(void);
void api_semaforo_update(void);

// Función para controlar los LEDs según el estado del semáforo
void semaphore_controlLEDs(semaphoreState_t state1, semaphoreState_t state2);

#endif /* API_SEMAFORO_H */
