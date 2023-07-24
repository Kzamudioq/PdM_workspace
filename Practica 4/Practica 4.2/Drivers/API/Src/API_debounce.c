#include "API_debounce.h"

// Variable privada global para almacenar el estado de la tecla
static bool_t keyPressed = false;

void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue) {
    *currentState = initialValue;
    keyPressed = false; // Inicializamos la variable global keyPressed en falso
}

void debounceFSM_update(debounceState_t *currentState, delay_t *delay) {
    switch (*currentState) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
                *currentState = BUTTON_FALLING;
            }
            break;
        case BUTTON_FALLING:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET && delayRead(delay)) {
                *currentState = BUTTON_DOWN;
                keyPressed = true; // Se activó un flanco descendente, establecemos keyPressed en true
            } else {
                *currentState = BUTTON_UP;
            }
            break;
        case BUTTON_DOWN:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
                *currentState = BUTTON_RAISING;
            }
            break;
        case BUTTON_RAISING:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET && delayRead(delay)) {
                *currentState = BUTTON_UP;
                keyPressed = false; // Se activó un flanco ascendente, establecemos keyPressed en false
            } else {
                *currentState = BUTTON_DOWN;
            }
            break;
        default:
            // Manejo de estado inesperado
            Error_Handler();
            break;
    }
}

bool_t readKey(void) {
    bool_t keyStatus = keyPressed; // Leemos el estado de la tecla almacenado en keyPressed
    keyPressed = false; // Reseteamos el estado de keyPressed para la siguiente lectura
    return keyStatus; // Devolvemos el estado de la tecla
}
