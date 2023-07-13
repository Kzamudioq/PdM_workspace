
# Punto 2

En esta práctica, se utiliza el pulsador azul (USER_BUTTON) para controlar el orden de la secuencia de los LEDs. Cada vez que se presiona el pulsador, se alternará el orden de la secuencia entre dos opciones:

1. Secuencia: LED1, LED2, LED3, LED1,... y así sucesivamente.
2. Secuencia: LED1, LED3, LED2, LED1,... y así sucesivamente.

El pulsador azul (USER_BUTTON) actúa como un interruptor para cambiar entre las dos opciones de secuencia. Cada vez que se presiona el pulsador, se alterna el orden de los LEDs en la secuencia. Esta funcionalidad permite al usuario experimentar con diferentes patrones de iluminación y explorar diferentes combinaciones de LEDs. Puedes ver una demostración del proyecto en acción en el siguiente video:

https://github.com/Kzamudioq/PdM_workspace/assets/138271936/c89f665f-2832-4407-9e63-0152dbb0d0ed


## Archivos del Proyecto


Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%201/Practica%201.2) y este contiene los siguientes archivos y directorios relacionados con la práctica, :

- `.settings`: directorio que contiene la configuración específica del proyecto para el entorno STM32CubeIDE.
- `Core`: directorio que contiene los archivos esenciales del proyecto. Aquí se encuentran los archivos principales que son necesarios para el funcionamiento del programa, como `main.c`, `main.h` y otros archivos fuente o de configuración esenciales para la aplicación específica.
- `Debug`: directorio que contiene los archivos relacionados con la configuración de depuración. Estos archivos son utilizados durante el proceso de depuración del programa para obtener información detallada sobre el estado del programa, variables, registros y otros datos relevantes para facilitar la detección y corrección de errores.
- `Drivers`: directorio que contiene archivos de controladores para el microcontrolador STM32.
- `.cproject`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.mxproject`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.project`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `Practica 1.2 Debug.launch`: archivo de configuración de depuración específico de la Práctica 1.
- `Practica 1.2.ioc`: archivo de configuración específico de la Práctica 1.1.
- `STM32F401RETX_FLASH.ld`: archivo de enlace (linker script) relacionado con el proyecto.
- `STM32F401RETX_RAM.ld`: archivo de enlace (linker script) relacionado con la memoria RAM del proyecto.

Además, los archivos principales del proyecto son:

- `main.c`: Este archivo se encuentra en la carpeta `Core` especificamete en `Src`. Contiene la función `main()`, que se ejecuta al iniciar el programa. Aquí es donde se encuentra la lógica principal de la práctica.
- `main.h`: Este archivo se encuentra en la carpeta `Core` especificamete en `Inc`. Es un archivo de encabezado (header file) que contiene las declaraciones de las funciones y variables utilizadas en `main.c` y otros archivos del proyecto.

La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

El archivo `STM32F401RETX_RAM.ld` es un script de enlace (linker script) que define la configuración de memoria RAM para el proyecto. Proporciona información sobre la asignación y disposición de la memoria RAM del microcontrolador STM32F401RETX utilizado en la placa NUCLEO-F401RE.

## main.c

El archivo `main.c` se encuentra en la carpeta `Core`. Contiene la función `main()`, que se ejecuta al iniciar el programa. Aquí se encuentra la lógica principal de la práctica. El programa principal se encuentra en el archivo `main.c`. Aquí se realiza la configuración inicial del microcontrolador y se implementa el bucle principal:

```c
// Función para alternar la secuencia de los LEDs
void Toggle_LED_Sequence(uint8_t sequenceIndex)
{
  const uint8_t sequences[6][3] = {
    {1, 2, 3},  // Secuencia 1: LED1, LED2, LED3
    {1, 3, 2},  // Secuencia 2: LED1, LED3, LED2
    {2, 1, 3},  // Secuencia 3: LED2, LED1, LED3
    {2, 3, 1},  // Secuencia 4: LED2, LED3, LED1
    {3, 2, 1},  // Secuencia 5: LED3, LED2, LED1
    {3, 1, 2}   // Secuencia 6: LED3, LED1, LED2
  };

  const uint8_t* sequence = sequences[sequenceIndex];

  for (int i = 0; i < 3; i++) {
    uint8_t led = sequence[i];
    HAL_GPIO_WritePin(LD_GPIO_Port[led - 1], LD_Pin[led - 1], GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LD_GPIO_Port[led - 1], LD_Pin[led - 1], GPIO_PIN_RESET);
    HAL_Delay(200);
  }
}

int main(void)
{
  // Configuración inicial del microcontrolador

  uint8_t sequenceIndex = 0; // Variable para controlar el índice de la secuencia de LEDs

  while (1)
  {
    // Verificar si el pulsador ha sido presionado
    if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
    {
      HAL_Delay(50);
      if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
      {
        sequenceIndex++;
        if (sequenceIndex >= 6)
        {
          sequenceIndex = 0;
        }
        while (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
        {
          // Esperar a que se suelte el pulsador
        }
      }
    }

    // Llamar a la función para alternar la secuencia de los LEDs
    Toggle_LED_Sequence(sequenceIndex);
  }
}
```
En el código anterior, se muestra la definición de la función Toggle_LED_Sequence(), que se encarga de alternar la secuencia de los LEDs. Luego, se muestra el bucle principal (while) del programa, donde se verifica si el pulsador ha sido presionado, se realiza el cambio de secuencia y se llama a la función Toggle_LED_Sequence() para encender y apagar los LEDs según el orden de la secuencia seleccionada.

## main.h

El archivo `main.h` se encuentra en la carpeta `Core`. Es un archivo de encabezado (header file) que contiene las declaraciones de las funciones y variables utilizadas en `main.c` y otros archivos del proyecto. Aquí se definen los prototipos de las funciones principales y las variables globales utilizadas en el proyecto:

- La directiva `#ifndef __MAIN_H` y `#define __MAIN_H` aseguran que el contenido del archivo solo se incluya una vez para evitar problemas de duplicación.

- El bloque `#ifdef __cplusplus` y `#endif` permite que el archivo sea compatible tanto con el lenguaje C como con el lenguaje C++.

- Se incluye el archivo de encabezado `stm32f4xx_hal.h`, que contiene las definiciones y funciones específicas del microcontrolador STM32F4.

- Se declara el prototipo de la función `Error_Handler()`, que se utiliza para manejar errores en el programa. La implementación de esta función se encuentra en otro lugar del proyecto.

- Se definen los pines utilizados en el proyecto, como el botón B1, los LEDs LD1, LD2 y LD3, y los pines USART para la comunicación serie.

- El bloque `#ifdef __cplusplus` y `#endif` cierra la declaración `extern "C"` para indicar que las declaraciones de las funciones deben ser tratadas como código C en lugar de código C++ cuando se incluye este archivo en un proyecto de lenguaje mixto.
  
- Se definen los pines utilizados en el proyecto, como el botón B1 (B1_Pin y B1_GPIO_Port), los LEDs LD1, LD2 y LD3 (LD1_Pin, LD1_GPIO_Port, LD2_Pin, LD2_GPIO_Port, LD3_Pin y LD3_GPIO_Port), y los pines USART para la comunicación serie (USART_TX_Pin, USART_TX_GPIO_Port, USART_RX_Pin y USART_RX_GPIO_Port).


La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

¡Diviértete programando los LEDs y experimentando con diferentes secuencias!
