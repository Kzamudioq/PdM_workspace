### Punto 1

Implementar un programa que genere la secuencia descrita anteriormente.

Ejemplo de secuencia: Led1(ON) 200ms, Leds(OFF) 200ms, Led2(ON) 200ms, Leds(OFF) 200ms, Led3(ON) 200ms, Leds(OFF) 200ms, Led1(ON) 200ms, Leds(OFF) 200ms, etc.

Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%201/Practica%201.1).

### Archivos del Proyecto

El repositorio contiene los siguientes archivos y directorios relacionados con la práctica:

- .settings: Directorio que contiene la configuración específica del proyecto para el entorno STM32CubeIDE.
- Core: Directorio que contiene archivos esenciales del proyecto.
- Debug: Directorio que contiene archivos relacionados con la configuración de depuración.
- Drivers: Directorio que contiene archivos de controladores para el microcontrolador STM32.
- .cproject: Archivo de configuración del proyecto para el entorno STM32CubeIDE.
- .mxproject: Archivo de configuración del proyecto para el entorno STM32CubeIDE.
- .project: Archivo de configuración del proyecto para el entorno STM32CubeIDE.
- Practica 1 Debug.launch: Archivo de configuración de depuración específico de la Práctica 1.
- Practica 1.1.ioc: Archivo de configuración específico de la Práctica 1.1.
- STM32F401RETX_FLASH.ld: Archivo de enlace (linker script) relacionado con el proyecto.
- STM32F401RETX_RAM.ld: Archivo de enlace (linker script) relacionado con la memoria RAM del proyecto.

El archivo `STM32F401RETX_RAM.ld` es un script de enlace (linker script) que define la configuración de memoria RAM para el proyecto. Proporciona información sobre la asignación y disposición de la memoria RAM del microcontrolador STM32F401RETX utilizado en la placa NUCLEO-F429ZI.

¡Diviértete programando los LEDs y experimentando con diferentes secuencias!
