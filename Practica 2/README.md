# Práctica 2

En esta práctica, el objetivo es implementar un módulo de software para trabajar con retardos no bloqueantes. Se deben desarrollar funciones auxiliares en el archivo fuente `main.c` y su correspondiente archivo de cabecera `main.h` para utilizar estos retardos no bloqueantes.

## Objetivo

Implementar un módulo de software para trabajar con retardos no bloqueantes en STM nucleo F401RE y adaptación de protoboard con dos LED, como sse vusualiza en el siguiente video:


https://github.com/Kzamudioq/PdM_workspace/assets/138271936/27717711-cb6e-4841-be7c-49d52c9cfee2


### Punto 1
Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente main.c con su correspondiente archivo de cabecera main.h.
En el archivo `main.h`, se deben ubicar los prototipos de las siguientes funciones y las declaraciones:

```c
typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t; // Qué biblioteca se debe incluir para que esto compile?

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
```
En main.c se deben ubicar la implementación de todas las funciones:
Consideraciones para la implementación:

1. delayInit debe cargar el valor de duración del retardo en la estructura, en el campo correspondiente. No debe iniciar el conteo del retardo. Debe inicializar el flag running en `false´.
2. delayRead debe verificar el estado del flag running.
- false, tomar marca de tiempo y cambiar running a ‘true’ 
- true, hacer la cuenta para saber si el tiempo del retardo se cumplió o no: marca de tiempo actual - marca de tiempo inicial es mayor o igual a duración del retardo’?, y devolver un valor booleano que indique si el tiempo se cumplió o no.
- Cuando el tiempo se cumple se debe cambiar el flag running a false.

3. delayWrite debe permitir cambiar el tiempo de duración de un delay existente

### Punto 2

Implementar un programa que utilice retardos no bloqueantes y  haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F401RE de la siguiente manera:

- LED1: 100 ms.
- LED2: 500 ms.
- LED3: 1000 ms.


## Archivos del Proyecto


Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%202) y este contiene los siguientes archivos y directorios relacionados con la práctica, :

- `.settings`: directorio que contiene la configuración específica del proyecto para el entorno STM32CubeIDE.
- `Core`: directorio que contiene los archivos esenciales del proyecto. Aquí se encuentran los archivos principales que son necesarios para el funcionamiento del programa, como `main.c`, `main.h` y otros archivos fuente o de configuración esenciales para la aplicación específica.
- `Debug`: directorio que contiene los archivos relacionados con la configuración de depuración. Estos archivos son utilizados durante el proceso de depuración del programa para obtener información detallada sobre el estado del programa, variables, registros y otros datos relevantes para facilitar la detección y corrección de errores.
- `Drivers`: directorio que contiene archivos de controladores para el microcontrolador STM32.
- `.cproject`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.mxproject`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.project`: archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `Practica 2 Debug.launch`: archivo de configuración de depuración específico de la Práctica 2.
- `Practica 2.ioc`: archivo de configuración específico de la Práctica 2.
- `STM32F401RETX_FLASH.ld`: archivo de enlace (linker script) relacionado con el proyecto.
- `STM32F401RETX_RAM.ld`: archivo de enlace (linker script) relacionado con la memoria RAM del proyecto.

Además, los archivos principales del proyecto son:

- `main.c`: Este archivo se encuentra en la carpeta `Core` especificamete en `Src`. Contiene la función `main()`, que se ejecuta al iniciar el programa. Aquí es donde se encuentra la lógica principal de la práctica.
- `main.h`: Este archivo se encuentra en la carpeta `Core` especificamete en `Inc`. Es un archivo de encabezado (header file) que contiene las declaraciones de las funciones y variables utilizadas en `main.c` y otros archivos del proyecto.

La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

El archivo `STM32F401RETX_RAM.ld` es un script de enlace (linker script) que define la configuración de memoria RAM para el proyecto. Proporciona información sobre la asignación y disposición de la memoria RAM del microcontrolador STM32F401RETX utilizado en la placa NUCLEO-F401RE.

## main.c

El archivo `main.c` se encuentra en la carpeta `Core`. Contiene la función `main()`, que se ejecuta al iniciar el programa. Aquí se encuentra la lógica principal de la práctica. El programa principal se encuentra en el archivo `main.c`. Aquí se realiza la configuración inicial del microcontrolador y se implementa el bucle principal:
El código principal se encuentra en el archivo `main.c`. A continuación se muestra una parte importante del código que controla el parpadeo de los LEDs:

```c
// Inicializar los retardos para cada LED
delayInit(&delayLED1, LED1_TIME);
delayInit(&delayLED2, LED2_TIME);
delayInit(&delayLED3, LED3_TIME);

while (1) {
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
```

En este fragmento de código, se inicializan los retardos para cada LED utilizando la función delayInit. Luego, en el bucle principal, se verifica el estado de cada retardo utilizando la función delayRead. Si un retardo ha finalizado, se cambia el estado correspondiente del LED utilizando la función HAL_GPIO_TogglePin. Esto crea el efecto de parpadeo de los LEDs en diferentes intervalos de tiempo.


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

