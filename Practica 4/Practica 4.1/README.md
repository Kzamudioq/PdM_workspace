# Punto 1: Implementación de una MEF Anti-rebote por Software

## Objetivo
El objetivo de este punto es implementar una MEF (Máquina de Estados Finitos) para trabajar con anti-rebotes por software en la placa NUCLEO-F401RE. Se utilizará dos LED para mostrar el estado y una tecla para generar acciones o eventos ante un flanco descendente o ascendente como se evudencia en el siguiente video:

https://github.com/Kzamudioq/PdM_workspace/assets/138271936/877fd9fa-adfd-44b5-9fd2-8a9f64bb42ad


## Estructura de la MEF
La MEF anti-rebote se implementará utilizando los siguientes estados:

![estados](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/25d3b435-9151-40aa-a613-eb9f44ab7e35)


- BUTTON_UP: Estado inicial de la MEF cuando el pulsador no está presionado.
- BUTTON_FALLING: Transición hacia este estado cuando se detecta un flanco descendente en el pulsador (pulsador presionado).
- BUTTON_DOWN: Estado cuando el pulsador está presionado, se ha registrado el evento y se espera el flanco ascendente.
- BUTTON_RAISING: Transición hacia este estado cuando se detecta un flanco ascendente en el pulsador (pulsador liberado).
  

La MEF se representará mediante un diagrama de estados con las transiciones entre ellos.

## Implementación en main.c
1. Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.
2. Implementar la MEF anti-rebote en el archivo "main.c" de acuerdo al siguiente imagen:

![Anti-rebotes con MEF](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/2f6c0794-4590-43ef-87e6-a1e6223f3177)


3. El estado inicial de la MEF debe ser BUTTON_UP.
4. Implementar las siguientes funciones dentro de "main.h":
   ```c
   void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue);    // debe cargar el estado inicial
   oid debounceFSM_update(debounceState_t *currentState, delay_t *delay);  // debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
   void buttonPressed(void);       // debe invertir el estado del LED1
   void buttonReleased(void);      // debe invertir el estado del LED3
   ```
5. Implementar las siguientes funciones dentro de "main.h":
   ```c
   /* Private user code ---------------------------------------------------------*/
   /* Application entry point */
   int main(void)
    {
     // Inicializar el hardware
     HAL_Init();
     SystemClock_Config();
     MX_GPIO_Init();

     // Inicializar la estructura para el retardo no bloqueante
     delayInit(&ledDelay, 40); // 40 ms delay

     // Inicializar la MEF Anti-Rebote con el estado inicial BUTTON_UP
     debounceState_t state;
     debounceFSM_init(&state, BUTTON_UP);

     /* Infinite loop */
     while (1) {
         // Actualizar la MEF Anti-Rebote y controlar los LEDs
         debounceFSM_update(&state, &ledDelay);
    }

    return 0;
   }
   ```
 La anterior función (*main()*) es el punto de entrada del programa. Su objetivo es inicializar el hardware, configurar la MEF Anti-Rebote y controlar los LEDs en función 
 del estado del pulsador.

  ```c
    /* Inicializa la máquina de estados debounce */
    void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue)
    {
     // Establecer el estado inicial de la MEF
     *currentState = initialValue;
    }
  ```
La función debounceFSM_init() inicializa la MEF Anti-Rebote con el estado inicial especificado. Recibe como parámetros un puntero al estado actual de la MEF (currentState) y el estado inicial deseado (initialValue).

  ```c
    /* Actualiza la máquina de estados debounce */
    void debounceFSM_update(debounceState_t *currentState, delay_t *delay)
    {
      switch (*currentState)
      {
      case BUTTON_UP:
          // Si el botón está presionado (flanco descendente)
          if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
          {
              *currentState = BUTTON_FALLING;
          }
          break;

      case BUTTON_FALLING:
          // Si el botón sigue presionado y ha pasado el retardo
          if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET && delayRead(delay))
          {
              *currentState = BUTTON_DOWN;
              buttonPressed();
          }
          else
          {
              *currentState = BUTTON_UP;
          }
          break;

      case BUTTON_DOWN:
          // Si el botón ha sido soltado (flanco ascendente)
          if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET)
          {
              *currentState = BUTTON_RAISING;
          }
          break;

      case BUTTON_RAISING:
          // Si el botón sigue soltado y ha pasado el retardo
          if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET && delayRead(delay))
          {
              *currentState = BUTTON_UP;
              buttonReleased();
          }
          else
          {
              *currentState = BUTTON_DOWN;
          }
          break;

      default:
          /* Manejar estado inesperado (Error) */
          Error_Handler();
      }
    }

  ```
  La función debounceFSM_update() se encarga de actualizar la MEF Anti-Rebote y controlar los flancos del pulsador. Recibe como parámetros un puntero al estado actual de 
  la MEF (currentState) y un puntero a la estructura de retardo no bloqueante para controlar el LED (delay).

  Esta función contiene un switch-case que maneja los diferentes estados de la MEF Anti-Rebote y toma acciones según los flancos detectados en el pulsador. También utiliza 
  el retardo no bloqueante para controlar el LED.

  ```c
    /* Maneja el evento de botón presionado */
    void buttonPressed(void)
    {
      // Invertir el estado del LED1
      HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
    }
  ```
  La función buttonPressed() se encarga de manejar el evento de botón presionado. Es llamada cuando se detecta un flanco descendente del pulsador. En este caso, invierte 
  el estado del LED1, es decir, si estaba encendido lo apaga, y si estaba apagado lo enciende.

  ```c
    /* Maneja el evento de botón soltado */
    void buttonReleased(void)
     {
       // Invertir el estado del LED3
       HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    }
  ```
  La función buttonReleased() se encarga de manejar el evento de botón soltado. Es llamada cuando se detecta un flanco ascendente del pulsador. En este caso, invierte el estado del LED3, es decir, si estaba encendido lo apaga, y si estaba apagado lo enciende.
  
