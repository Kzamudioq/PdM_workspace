# Punto 2

En esta practica se implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F401RE de acuerdo a una secuencia predeterminada como en la práctica 1. Cada led debe permanecer encendido 200 ms.  No debe encenderse más de un led simultáneamente en ningún momento. Tener presente que se implementa el punto 2 de la primera practica donde  se utiliza el pulsador azul (USER_BUTTON) para controlar el orden de la secuencia de los LEDs. Cada vez que se presiona el pulsador, se alternará el orden de la secuencia entre dos opciones:

1. Secuencia: LED1, LED2, LED3, LED1,... y así sucesivamente.
2. Secuencia: LED1, LED3, LED2, LED1,... y así sucesivamente.

El pulsador azul (USER_BUTTON) actúa como un interruptor para cambiar entre las dos opciones de secuencia. Cada vez que se presiona el pulsador, se alterna el orden de los LEDs en la secuencia. Esta funcionalidad permite al usuario experimentar con diferentes patrones de iluminación y explorar diferentes combinaciones de LEDs. Puedes ver una demostración del proyecto en acción en el siguiente video:



https://github.com/Kzamudioq/PdM_workspace/assets/138271936/2f28a9bb-d607-4332-b6fb-bbc66b0754e0



## Archivos del Proyecto


Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/4ad0a88e1328ac0dc331319ea155e1032585eab0/Practica%203/Practica%203.2) y este contiene los siguientes archivos y directorios relacionados con la práctica, :

- `.settings`: directorio que contiene la configuración específica del proyecto para el entorno STM32CubeIDE.
- `Core`: directorio que contiene los archivos esenciales del proyecto. Aquí se encuentran los archivos principales que son necesarios para el funcionamiento del programa, como `main.c`, `main.h` y otros archivos fuente o de configuración esenciales para la aplicación específica.
- `Debug`: directorio que contiene los archivos relacionados con la configuración de depuración. Estos archivos son utilizados durante el proceso de depuración del programa para obtener información detallada sobre el estado del programa, variables, registros y otros datos relevantes para facilitar la detección y corrección de errores.
- `Drivers`: directorio que contiene archivos de controladores para el microcontrolador STM32 , donde se genero la carpeta `API`, y a su vez en esta sse genero dos carpetas denominadas cada una como `Inc` y `Src`. Se puede encontrar en `Inc` el  `API_delay.h` y en `Src` el `API_delay.c`.
- `.cproject`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.mxproject`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.project`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `Practica 3.2 Debug.launch`: archivo de configuración de depuración específico de la Práctica 3.2.
- `Practica 3.2.ioc`: archivo de configuración específico de la Práctica 3.2.
- `STM32F401RETX_FLASH.ld`: archivo de enlace (linker script) relacionado con el proyecto.
- `STM32F401RETX_RAM.ld`: archivo de enlace (linker script) relacionado con la memoria RAM del proyecto.

Además, los archivos principales del proyecto son:

- `API_delay.c`: Este archivo se encuentra en la carpeta `Drivers` que contiene a su vez `API` especificamete en `Src`. Contiene la funciónes **delayInit**,**delayRead** y **delayWrite** necesarias para ejecuta al iniciar el programa.
- `API_delay.h`: Este archivo se encuentra en la carpeta `Drivers` que contiene a su vez `API` especificamete en `Inc`. Es un archivo  que contiene las declaraciones de las funciones y variables utilizadas en `API_delay.c` y otros archivos del proyecto.

La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

El archivo `STM32F401RETX_RAM.ld` es un script de enlace (linker script) que define la configuración de memoria RAM para el proyecto. Proporciona información sobre la asignación y disposición de la memoria RAM del microcontrolador STM32F401RETX utilizado en la placa NUCLEO-F401RE.

## API_delay.c

Este archivo se encuentra en la carpeta `Drivers` que contiene a su vez `API` especificamete en `Src`. Contiene la funciónes **delayInit**,**delayRead** y **delayWrite** necesarias para ejecuta al iniciar el programa:

```c
#include "API_delay.h"

// Inicializa la estructura de retardo con la duración especificada
void delayInit(delay_t *delay, tick_t duration) {
   delay->duration = duration; // Establece la duración del retardo
   delay->running = false; // Establece el estado de ejecución del retardo como falso (no en ejecución)
}

// Lee el estado del retardo
// Devuelve true si el retardo ha terminado, o false si aún está en curso
bool_t delayRead(delay_t *delay) {
   if (!delay->running) { // Si el retardo no está en ejecución
      delay->startTime = HAL_GetTick(); // Obtiene el tiempo actual y lo guarda como inicio del retardo
      delay->running = true; // Cambia el estado de ejecución del retardo a verdadero (en ejecución)
      return false; // Indica que el retardo aún no ha terminado
   } else { // Si el retardo está en ejecución
      tick_t currentTime = HAL_GetTick(); // Obtiene el tiempo actual
      if (currentTime - delay->startTime >= delay->duration) { // Comprueba si el tiempo transcurrido es mayor o igual a la duración del retardo
         delay->running = false; // Cambia el estado de ejecución del retardo a falso (terminado)
         return true; // Indica que el retardo ha terminado
      } else {
         return false; // Indica que el retardo aún no ha terminado
      }
   }
}

// Actualiza la duración del retardo con el valor especificado
void delayWrite(delay_t *delay, tick_t duration) {
   delay->duration = duration; // Actualiza la duración del retardo
}
```

## API_delay.h

 Este archivo se encuentra en la carpeta `Drivers` que contiene a su vez `API` especificamete en `Inc`. Es un archivo  que contiene las declaraciones de las funciones y variables utilizadas en `API_delay.c` y otros archivos del proyecto:

- La directiva `#ifndef __API_delay.h` y `#define __API_delay.h` aseguran que el contenido del archivo solo se incluya una vez para evitar problemas de duplicación.

- El bloque `#ifdef __cplusplus` y `#endif` permite que el archivo sea compatible tanto con el lenguaje C como con el lenguaje C++.

- Se incluye el archivo de encabezado `stm32f4xx_hal.h`, que contiene las definiciones y funciones específicas del microcontrolador STM32F4.

- Se declara el prototipo de la función `Error_Handler()`, que se utiliza para manejar errores en el programa. La implementación de esta función se encuentra en otro lugar del proyecto.

- Se definen los pines utilizados en el proyecto, como el botón B1, los LEDs LD1, LD2 y LD3, y los pines USART para la comunicación serie.

- El bloque `#ifdef __cplusplus` y `#endif` cierra la declaración `extern "C"` para indicar que las declaraciones de las funciones deben ser tratadas como código C en lugar de código C++ cuando se incluye este archivo en un proyecto de lenguaje mixto.
  
- Se definen los pines utilizados en el proyecto, como el botón B1 (B1_Pin y B1_GPIO_Port), los LEDs LD1, LD2 y LD3 (LD1_Pin, LD1_GPIO_Port, LD2_Pin, LD2_GPIO_Port, LD3_Pin y LD3_GPIO_Port), y los pines USART para la comunicación serie (USART_TX_Pin, USART_TX_GPIO_Port, USART_RX_Pin y USART_RX_GPIO_Port).


La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

¡Diviértete programando los LEDs y experimentando con diferentes secuencias!



