/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Inclusiones ----------------------------------------------------------------*/
#include "main.h"


// Estructuras para los retardos de cada LED
delay_t delayLED1;
delay_t delayLED2;
delay_t delayLED3;

/* Inclusiones privadas -------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* Variables privadas ---------------------------------------------------------*/
UART_HandleTypeDef huart2;


/* Prototipos de funciones privadas -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/**
  * @brief  Punto de entrada de la aplicación.
  * @retval int
  */

int main(void)
{
  /*  Inicializar los retardos para cada LED*/
  delayInit(&delayLED1, LED1_TIME);
  delayInit(&delayLED2, LED2_TIME);
  delayInit(&delayLED3, LED3_TIME);

  /* Configuración del MCU */
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* Bucle infinito */
  while (1){
	  // Verificar los retardos y controlar el parpadeo de los LEDs

      if (delayRead(&delayLED1)) {
         // El tiempo de retardo para LED1 se ha cumplido, cambiar el estado del LED
         HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
      }

      if (delayRead(&delayLED2)) {
         // El tiempo de retardo para LED2 se ha cumplido, cambiar el estado del LED
         HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
      }

      if (delayRead(&delayLED3)) {
         // El tiempo de retardo para LED3 se ha cumplido, cambiar el estado del LED
         HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
      }
  }
}

/**
  * @brief Inicializa el retardo con la duración especificada.
  * @param delay: Puntero a la estructura de retardo.
  * @param duration: Duración del retardo en milisegundos.
  */

void delayInit(delay_t* delay, tick_t duration) {
   delay->duration = duration;
   delay->running = false;
}

/**
  * @brief Verifica el estado del retardo.
  * @param delay: Puntero a la estructura de retardo.
  * @return Estado del retardo (true si el retardo se ha completado, false en caso contrario).
  */

bool_t delayRead(delay_t* delay) {
   if (!delay->running) {
      delay->startTime = HAL_GetTick();
      delay->running = true;
      return false;
   } else {
      tick_t currentTime = HAL_GetTick();
      tick_t elapsedTime = currentTime - delay->startTime;

      if (elapsedTime >= delay->duration) {
         delay->running = false;
         return true;
      } else {
         return false;
      }
   }
}

/**
  * @brief Cambia la duración del retardo existente.
  * @param delay: Puntero a la estructura de retardo.
  * @param duration: Nueva duración del retardo en milisegundos.
  */

void delayWrite(delay_t* delay, tick_t duration) {
   delay->duration = duration;
}

/* Configuración del sistema de reloj */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configurar la tensión de salida del regulador interno principal
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Inicializar los osciladores RCC según los parámetros especificados
  * en la estructura RCC_OscInitStruct.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Inicializar los relojes de la CPU, AHB y APB
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Cofigure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : L1_Pin L3_Pin L2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
