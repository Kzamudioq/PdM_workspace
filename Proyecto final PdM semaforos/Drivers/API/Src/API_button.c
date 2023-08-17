#include "API_button.h"
#include "main.h"
static bool keyPressed = false;

#define DEBOUNCE_DELAY 50

void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue) {
    *currentState = initialValue;
    keyPressed = false;
}

void debounceFSM_update(debounceState_t *currentState) {
    switch (*currentState) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
                *currentState = BUTTON_FALLING;
            }
            break;
        case BUTTON_FALLING:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
                HAL_Delay(DEBOUNCE_DELAY);
                *currentState = BUTTON_DOWN;
                keyPressed = true;
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
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
                HAL_Delay(DEBOUNCE_DELAY);
                *currentState = BUTTON_UP;
                keyPressed = false;
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

bool Button_IsPressed(debounceState_t *currentState) {
    return (keyPressed && *currentState == BUTTON_UP);
}
