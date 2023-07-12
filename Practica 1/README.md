# Práctica 1

En esta práctica, el objetivo es familiarizarse con el entorno de trabajo STM32CubeIDE + NUCLEO-F401RE + firmware y desarrollar un programa que genere una secuencia periódica con el LEDs de la placa NUCLEO-F401RE, la ayuda de ua proto board y dos leds adicioales.

![materiales](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/c8dffdf2-32d9-429b-88b5-271382f21f7e)

## Objetivo

El objetivo de esta práctica es implementar un programa que genere una secuencia periódica con los LEDs de la placa NUCLEO-F429ZI. La secuencia debe seguir el orden: LED1, LED2, LED3, LED1, etc. Cada LED debe permanecer encendido durante 200 ms y no debe encenderse más de un LED simultáneamente. Además, debe haber una separación temporal de 200 ms entre las encendidas sucesivas.

### Punto 1

Implementar un programa que genere la secuencia descrita anteriormente.

Ejemplo de secuencia: Led1(ON) 200ms, Leds(OFF) 200ms, Led2(ON) 200ms, Leds(OFF) 200ms, Led3(ON) 200ms, Leds(OFF) 200ms, Led1(ON) 200ms, Leds(OFF) 200ms, etc.

Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%201/Practica%201.1).

### Punto 2

Utilizar el pulsador azul (USER_BUTTON) para controlar cómo se recorre la secuencia de LEDs. Cada vez que se presiona el pulsador, se debe alternar el orden de la secuencia entre:

- LED1, LED2, LED3, LED1, etc.
- LED1, LED3, LED2, LED1, etc.

Puedes encontrar el código y los detalles de la implementación en [este enlace](https://github.com/Kzamudioq/PdM_workspace/tree/main/Practica%201/Practica%201.2).

¡Diviértete programando los LEDs y experimentando con diferentes secuencias!

