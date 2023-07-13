### Punto 1

Implementar un programa que genere la secuencia descrita anteriormente.

Ejemplo de secuencia: Led1(ON) 200ms, Leds(OFF) 200ms, Led2(ON) 200ms, Leds(OFF) 200ms, Led3(ON) 200ms, Leds(OFF) 200ms, Led1(ON) 200ms, Leds(OFF) 200ms, etc.

Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%201/Practica%201.1).

### Archivos del Proyecto

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

## main.h

El archivo `main.h` se encuentra en la carpeta `Core`. Es un archivo de encabezado (header file) que contiene las declaraciones de las funciones y variables utilizadas en `main.c` y otros archivos del proyecto. Aquí se definen los prototipos de las funciones principales y las variables globales utilizadas en el proyecto.

La estructura del repositorio se organiza de esta manera para separar las configuraciones del entorno, los archivos esenciales del proyecto, los controladores del microcontrolador STM32 y los archivos de configuración específicos de la práctica. Esto ayuda a mantener el código ordenado y facilita la navegación y comprensión del proyecto.

¡Diviértete programando los LEDs y experimentando con diferentes secuencias!

