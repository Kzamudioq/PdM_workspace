#include "API_uart.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>

// Variables globales
UART_HandleTypeDef huart2; // Suponiendo que estás usando la UART2 en la STM32F401RE

bool uartInit() {
    // Inicialización del periférico UART (UART2 en este caso)
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200; // Velocidad de transmisión
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // Si la inicialización falla, devolvemos false
        return false;
    }

    // Imprimir por la terminal serie un mensaje con los parámetros de configuración
    uint8_t msg[] = "UART initialized successfully!\r\n";
    HAL_UART_Transmit(&huart2, msg, sizeof(msg) - 1, HAL_MAX_DELAY);

    return true;
}

void uartSendString(uint8_t *pstring) {
    // Encender el LED correspondiente al pin TX
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);

    // Utilizar la función HAL para transmitir el string completo
    HAL_UART_Transmit(&huart2, pstring, strlen((const char *)pstring), HAL_MAX_DELAY);

    // Apagar el LED correspondiente al pin TX
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
}

void uartSendStringSize(uint8_t *pstring, uint16_t size) {
    // Encender el LED correspondiente al pin TX
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);

    // Utilizar la función HAL para transmitir el string con el tamaño especificado
    HAL_UART_Transmit(&huart2, pstring, size, HAL_MAX_DELAY);

    // Apagar el LED correspondiente al pin TX
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
}
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
    // Encender el LED correspondiente al pin RX
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);

    // Utilizar la función HAL para recibir datos por la UART
    HAL_UART_Receive(&huart2, pstring, size, HAL_MAX_DELAY);

    // Apagar el LED correspondiente al pin RX
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}
