#ifndef API_BUTTON_H
#define API_BUTTON_H

#include "stm32f4xx_hal.h" // Asegúrate de incluir la librería de tu microcontrolador
#include <stdbool.h>

// Enumeración para los posibles estados del botón
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;

// Inicialización de la máquina de estados de debounce
void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue);
// Actualización de la máquina de estados de debounce
void debounceFSM_update(debounceState_t *currentState);
// Comprobar si el botón está presionado
bool Button_IsPressed(debounceState_t *currentState);

#endif /* API_BUTTON_H */
