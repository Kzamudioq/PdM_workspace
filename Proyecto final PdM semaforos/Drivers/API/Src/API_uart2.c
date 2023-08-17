#include "api_uart2.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include <string.h>

static UART_HandleTypeDef huart2;

void API_UART2_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // Si la inicialización falla, puedes imprimir un mensaje de error o tomar otra acción
        Error_Handler();
    }

    // Imprimir por la terminal serie un mensaje con los parámetros de configuración
    uint8_t msg[] = "UART initialized successfully!\r\n";
    HAL_UART_Transmit(&huart2, msg, sizeof(msg) - 1, HAL_MAX_DELAY);
}


void API_UART2_SendMessage(const char *message) {
    if (HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY) != HAL_OK) {
        Error_Handler();
    }

}
