# Punto 1

Implementar un programa que genere la secuencia descrita anteriormente.

Ejemplo de secuencia: Led1(ON) 200ms, Leds(OFF) 200ms, Led2(ON) 200ms, Leds(OFF) 200ms, Led3(ON) 200ms, Leds(OFF) 200ms, Led1(ON) 200ms, Leds(OFF) 200ms, etc.

Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%201/Practica%201.1).

## Archivos del Proyecto

Este repositorio contiene los siguientes archivos y directorios relacionados con la práctica:

- `.settings`: Directorio que contiene la configuración específica del proyecto para el entorno STM32CubeIDE.
- `Core`: Directorio que contiene archivos esenciales del proyecto.
- `Debug`: Directorio que contiene archivos relacionados con la configuración de depuración.
- `Drivers`: Directorio que contiene archivos de controladores para el microcontrolador STM32.
- `.cproject`: Archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.mxproject`: Archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `.project`: Archivo de configuración del proyecto para el entorno STM32CubeIDE.
- `Practica 1 Debug.launch`: Archivo de configuración de depuración específico de la Práctica 1.
- `Practica 1.1.ioc`: Archivo de configuración específico de la Práctica 1.1.
- `STM32F401RETX_FLASH.ld`: Archivo de enlace (linker script) relacionado con el proyecto.
- `STM32F401RETX_RAM.ld`: Archivo de enlace (linker script) relacionado con la memoria RAM del proyecto.

Además, los archivos principales del proyecto son:

- `main.c`: Este archivo se encuentra en la carpeta `Core` especificamete en `Src`. Contiene la función `main()`, que se ejecuta al iniciar el programa. Aquí es donde se encuentra la lógica principal de la práctica.
- `main.h`: Este archivo se encuentra en la carpeta `Core` especificamete en `Inc`. Es un archivo de encabezado (header file) que contiene las declaraciones de las funciones y variables utilizadas en `main.c` y otros archivos del proyecto.

La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

El archivo `STM32F401RETX_RAM.ld` es un script de enlace (linker script) que define la configuración de memoria RAM para el proyecto. Proporciona información sobre la asignación y disposición de la memoria RAM del microcontrolador STM32F401RETX utilizado en la placa NUCLEO-F401RE.

## main.c

El archivo `main.c` se encuentra en la carpeta `Core`. Contiene la función `main()`, que se ejecuta al iniciar el programa. Aquí se encuentra la lógica principal de la práctica. Algunas funciones importantes incluidas en `main.c` son:

- `setup()`: Esta función se encarga de la configuración inicial del microcontrolador y los periféricos utilizados en la práctica. Aquí se inicializan los pines, los temporizadores, las interrupciones, etc.
- `loop()`: Esta función se ejecuta en un bucle continuo después de la configuración inicial. Aquí se coloca la lógica principal de la práctica, incluyendo la lectura de sensores, el procesamiento de datos y el control de los actuadores.
- `delay(ms)`: Esta función se utiliza para introducir una pausa en la ejecución del programa durante un tiempo determinado en milisegundos. Se puede utilizar para crear retardos o establecer intervalos de tiempo entre operaciones.

En el bucle principal (`while (1)`), el programa realiza el parpadeo de los LEDs LD1, LD2 y LD3 en intervalos de 200 ms. El código más importante en el bucle principal es el siguiente:

```c
while (1)
{
  // Parpadeo del LED LD1
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
  HAL_Delay(200);
  
  // Parpadeo del LED LD2
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  HAL_Delay(200);
  
  // Parpadeo del LED LD3
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
  HAL_Delay(200);
}
```
En cada iteración del bucle, se enciende y apaga secuencialmente cada LED (LD1, LD2 y LD3) en intervalos de 200 ms. Esto se logra utilizando las funciones HAL_GPIO_WritePin() para establecer el estado del pin del LED y HAL_Delay() para pausar el programa durante el intervalo de tiempo especificado.

La secuencia de parpadeo se repite continuamente mientras el programa está en funcionamiento debido a que el bucle principal tiene una condición while (1) que siempre es verdadera.

## main.h

El archivo `main.h` se encuentra en la carpeta `Core`. Es un archivo de encabezado (header file) que contiene las declaraciones de las funciones y variables utilizadas en `main.c` y otros archivos del proyecto. Aquí se definen los prototipos de las funciones principales y las variables globales utilizadas en el proyecto.

La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

¡Diviértete programando los LEDs y experimentando con diferentes secuencias!

