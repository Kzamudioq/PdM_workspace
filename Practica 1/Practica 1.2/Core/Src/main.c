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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables privadas ---------------------------------------------------------*/
GPIO_TypeDef* LD_GPIO_Port[3] = {LD1_GPIO_Port, LD2_GPIO_Port, LD3_GPIO_Port};
uint16_t LD_Pin[3] = {LD1_Pin, LD2_Pin, LD3_Pin};

/* Prototipos de funciones privadas -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Toggle_LED_Sequence(uint8_t sequenceIndex);
void Error_Handler(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* Reset de todos los periféricos, inicializa la interfaz Flash y el SysTick. */
  HAL_Init();

  /* Configura el reloj del sistema */
  SystemClock_Config();

  /* Inicializa todos los periféricos configurados */
  MX_GPIO_Init();
 
  /*  Variable para controlar el índice de la secuencia de LEDs*/
  uint8_t sequenceIndex = 0; 
 
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Comprueba si el pulsador está presionado*/
    if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
    {
      HAL_Delay(50);
      /* Comprueba nuevamete si el pulsador está presionado*/
      if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
      {
        /* Incrementa el índice de la secuencia*/
        sequenceIndex++;
        /* Incrementa el índice de la secuencia*/
        if (sequenceIndex >= 6)
        {
          sequenceIndex = 0;
        }
        /* Espera a que el pulsador se suelte antes de continuar*/
        while (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
        {
        }
      }
    }
    /* Alterna la secuencia de los LEDs*/
    Toggle_LED_Sequence(sequenceIndex);
  }
}
/**
  * @brief  Alterna los LEDs en función del índice de la secuencia dado.
  * @param  sequenceIndex: Índice de la secuencia de LEDs.
  * @retval None
  */
void Toggle_LED_Sequence(uint8_t sequenceIndex)
{
 /* Define las secuencias de los LEDs*/
  const uint8_t sequences[6][3] = {
    {1, 2, 3},  // Secuencia 1: LED1, LED2, LED3
    {1, 3, 2},  // Secuencia 2: LED1, LED3, LED2
    {2, 1, 3},  // Secuencia 3: LED2, LED1, LED3
    {2, 3, 1},  // Secuencia 4: LED2, LED3, LED1
    {3, 2, 1},  // Secuencia 5: LED3, LED2, LED1
    {3, 1, 2}   // Secuencia 6: LED3, LED1, LED2
  };
  /* Obtiene la secuencia correspondiente al índice dado*/
  const uint8_t* sequence = sequences[sequenceIndex];
 
  /* Itera sobre la secuencia y alterna los LEDs*/
  for (int i = 0; i < 3; i++) {
    uint8_t led = sequence[i];
    HAL_GPIO_WritePin(LD_GPIO_Port[led - 1], LD_Pin[led - 1], GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LD_GPIO_Port[led - 1], LD_Pin[led - 1], GPIO_PIN_RESET);
    HAL_Delay(200);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configura la tensión de salida del regulador interno principal
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Inicializa los osciladores RCC según los parámetros especificados
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

  /** Inicializa los relojes del CPU, AHB y APB
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Habilita el reloj de los puertos GPIO */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Configura el nivel de salida de los pines GPIOA como RESET */
  HAL_GPIO_WritePin(GPIOA, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /* Configura el pin B1 como IT_FALLING (interrupción por flanco de bajada) sin resistencia pull-up/pull-down */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /* Configura los pines LD1_Pin, LD3_Pin y LD2_Pin como OUTPUT_PP (salida push-pull) de baja frecuencia */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configura los pines USART_TX_Pin y USART_RX_Pin como AF_PP (función alternativa push-pull) de baja frecuencia */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif 
