#include "API_Semaphores.h"
#include "API_button.h"
#include "API_uart2.h"
#include "main.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim3;

static semaphoreState_t currentSemaphoreState1 = SEMAPHORE_RED;
static semaphoreState_t currentSemaphoreState2 = SEMAPHORE_GREEN;

#define TIME_RED 10000
#define TIME_GREEN 10000
#define TIME_YELLOW 5000


void api_semaforo_init(void) {

    // Encender todos los LEDs simultáneamente
    HAL_GPIO_WritePin(SEMAPHORE1_RED_GPIO_Port, SEMAPHORE1_RED_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SEMAPHORE1_YELLOW_GPIO_Port, SEMAPHORE1_YELLOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SEMAPHORE1_GREEN_GPIO_Port, SEMAPHORE1_GREEN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SEMAPHORE2_RED_GPIO_Port, SEMAPHORE2_RED_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SEMAPHORE2_YELLOW_GPIO_Port, SEMAPHORE2_YELLOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SEMAPHORE2_GREEN_GPIO_Port, SEMAPHORE2_GREEN_Pin, GPIO_PIN_SET);

    for (int i = 0; i < 3; i++) {
        HAL_Delay(500);  // Encendido durante 0.5 segundos
        HAL_GPIO_WritePin(SEMAPHORE1_RED_GPIO_Port, SEMAPHORE1_RED_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEMAPHORE1_YELLOW_GPIO_Port, SEMAPHORE1_YELLOW_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEMAPHORE1_GREEN_GPIO_Port, SEMAPHORE1_GREEN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEMAPHORE2_RED_GPIO_Port, SEMAPHORE2_RED_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEMAPHORE2_YELLOW_GPIO_Port, SEMAPHORE2_YELLOW_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEMAPHORE2_GREEN_GPIO_Port, SEMAPHORE2_GREEN_Pin, GPIO_PIN_RESET);
        HAL_Delay(500);  // Apagado durante 0.5 segundos
        HAL_GPIO_WritePin(SEMAPHORE1_RED_GPIO_Port, SEMAPHORE1_RED_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEMAPHORE1_YELLOW_GPIO_Port, SEMAPHORE1_YELLOW_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEMAPHORE1_GREEN_GPIO_Port, SEMAPHORE1_GREEN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEMAPHORE2_RED_GPIO_Port, SEMAPHORE2_RED_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEMAPHORE2_YELLOW_GPIO_Port, SEMAPHORE2_YELLOW_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEMAPHORE2_GREEN_GPIO_Port, SEMAPHORE2_GREEN_Pin, GPIO_PIN_SET);
    }

    // Apagar todos los LEDs
    HAL_GPIO_WritePin(SEMAPHORE1_RED_GPIO_Port, SEMAPHORE1_RED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE1_YELLOW_GPIO_Port, SEMAPHORE1_YELLOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE1_GREEN_GPIO_Port, SEMAPHORE1_GREEN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE2_RED_GPIO_Port, SEMAPHORE2_RED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE2_YELLOW_GPIO_Port, SEMAPHORE2_YELLOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE2_GREEN_GPIO_Port, SEMAPHORE2_GREEN_Pin, GPIO_PIN_RESET);

    // Inicializar los semáforos en sus estados iniciales
    currentSemaphoreState1 = SEMAPHORE_RED;
    currentSemaphoreState2 = SEMAPHORE_GREEN;

}


void semaphore_controlLEDs(semaphoreState_t state1, semaphoreState_t state2) {
    // Apaga todos los LEDs
    HAL_GPIO_WritePin(SEMAPHORE1_RED_GPIO_Port, SEMAPHORE1_RED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE1_YELLOW_GPIO_Port, SEMAPHORE1_YELLOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE1_GREEN_GPIO_Port, SEMAPHORE1_GREEN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE2_RED_GPIO_Port, SEMAPHORE2_RED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE2_YELLOW_GPIO_Port, SEMAPHORE2_YELLOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEMAPHORE2_GREEN_GPIO_Port, SEMAPHORE2_GREEN_Pin, GPIO_PIN_RESET);

    // Configura los LEDs según los estados de los semáforos
    if (state1 == SEMAPHORE_RED) {
        HAL_GPIO_WritePin(SEMAPHORE1_RED_GPIO_Port, SEMAPHORE1_RED_Pin, GPIO_PIN_SET);
    } else if (state1 == SEMAPHORE_YELLOW) {
    	HAL_GPIO_WritePin(SEMAPHORE1_YELLOW_GPIO_Port, SEMAPHORE1_YELLOW_Pin, GPIO_PIN_SET);
    } else if (state1 == SEMAPHORE_GREEN) {
        HAL_GPIO_WritePin(SEMAPHORE1_GREEN_GPIO_Port, SEMAPHORE1_GREEN_Pin, GPIO_PIN_SET);
    }

    if (state2 == SEMAPHORE_RED) {
        HAL_GPIO_WritePin(SEMAPHORE2_RED_GPIO_Port, SEMAPHORE2_RED_Pin, GPIO_PIN_SET);
    } else if (state2 == SEMAPHORE_YELLOW) {
        HAL_GPIO_WritePin(SEMAPHORE2_YELLOW_GPIO_Port, SEMAPHORE2_YELLOW_Pin, GPIO_PIN_SET);
    } else if (state2 == SEMAPHORE_GREEN) {
        HAL_GPIO_WritePin(SEMAPHORE2_GREEN_GPIO_Port, SEMAPHORE2_GREEN_Pin, GPIO_PIN_SET);
    }
}

void api_semaforo_update(void) {
    static uint32_t stateStartTime1 = 0;
    static uint32_t stateStartTime2 = 0;
    static uint8_t sequenceStep = 0;

    static bool semaphore1InRed = true; // Inicialmente, asumimos que el semáforo 1 está en rojo
    static bool buttonPressed = false;
    static bool buttonWasPressed = false;
    debounceState_t currentState;

    uint32_t currentTime = HAL_GetTick();
    uint32_t elapsedTime1 = currentTime - stateStartTime1;
    uint32_t elapsedTime2 = currentTime - stateStartTime2;

    // Verificar si el botón ha sido presionado o liberado
    bool buttonState = Button_IsPressed(&currentState);
    if (buttonState && !buttonWasPressed) {
        buttonPressed = true;
        stateStartTime1 = currentTime; // Reiniciar el tiempo de estado para semáforo 1
        stateStartTime2 = currentTime; // Reiniciar el tiempo de estado para semáforo 2
    } else if (!buttonState && buttonWasPressed) {
        if (buttonPressed) {
            // Cambio de fase forzado por el botón
            currentSemaphoreState1 = SEMAPHORE_YELLOW;
            currentSemaphoreState2 = SEMAPHORE_YELLOW;

            // Controla los LEDs de los semáforos en amarillo
            semaphore_controlLEDs(currentSemaphoreState1, currentSemaphoreState2);

            // Determinar cuál semáforo estaba en rojo y cambiar la secuencia
            if (semaphore1InRed) {
                semaphore1InRed = false;
                API_UART2_SendMessage("Boton presionado - Semaforo 1: Verde, Semaforo 2: Rojo\r\n");
            } else {
                semaphore1InRed = true;
                API_UART2_SendMessage("Boton presionado - Semaforo 1: Rojo, Semaforo 2: Verde\r\n");
            }
        }
        buttonPressed = false;
    }
    buttonWasPressed = buttonState;

    // Lógica cíclica de cambio de semáforos
    switch (sequenceStep) {
        case 0:
            if (elapsedTime1 >= TIME_RED && elapsedTime2 >= TIME_RED) {
                currentSemaphoreState1 = SEMAPHORE_YELLOW;
                currentSemaphoreState2 = SEMAPHORE_YELLOW;
                sequenceStep = 1;
                stateStartTime1 = currentTime;
                stateStartTime2 = currentTime;
            }
            break;
        case 1:
            if (elapsedTime1 >= TIME_YELLOW && elapsedTime2 >= TIME_YELLOW) {
                currentSemaphoreState1 = SEMAPHORE_GREEN;
                currentSemaphoreState2 = SEMAPHORE_RED;
                sequenceStep = 2;
                stateStartTime1 = currentTime;
                stateStartTime2 = currentTime;
            }
            break;
        case 2:
            if (elapsedTime1 >= TIME_GREEN && elapsedTime2 >= TIME_GREEN) {
                currentSemaphoreState1 = SEMAPHORE_YELLOW;
                currentSemaphoreState2 = SEMAPHORE_YELLOW;
                sequenceStep = 3;
                stateStartTime1 = currentTime;
                stateStartTime2 = currentTime;
            }
            break;
        case 3:
            if (elapsedTime1 >= TIME_YELLOW && elapsedTime2 >= TIME_YELLOW) {
                currentSemaphoreState1 = SEMAPHORE_RED;
                currentSemaphoreState2 = SEMAPHORE_GREEN;
                sequenceStep = 0;
                stateStartTime1 = currentTime;
                stateStartTime2 = currentTime;
            }
            break;
        default:
            break;
    }

    // Controla los LEDs de los semáforos según los estados actuales
    semaphore_controlLEDs(currentSemaphoreState1, currentSemaphoreState2);
}
