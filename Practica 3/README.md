# Práctica 3

En esta práctica, el objetivo es implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2. Se debe crear un nuevo proyecto y encapsular las funciones necesarias en un archivo fuente y su correspondiente archivo de cabecera. para esto se implementara una placa STM con nucleo F401RE, se añade una proto boart con dos leds adicionales.


## Objetivo

El objetivo de esta práctica es implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2. Se debe crear un nuevo proyecto, crear una estructura de directorios adecuada y encapsular las funciones necesarias en un archivo fuente y su correspondiente archivo de cabecera.

### Punto 1

Para comenzar, crea un nuevo proyecto como copia del proyecto realizado para la Práctica 2.

1. Crea una carpeta llamada `API` dentro de la carpeta `Drivers` en la estructura de directorios del nuevo proyecto.
2. Dentro de la carpeta `API`, crea las subcarpetas `Src` e `Inc`.
3. Encapsula las funciones necesarias para utilizar retardos no bloqueantes en un archivo fuente llamado `API_delay.c` con su correspondiente archivo de cabecera `API_delay.h`, y coloca estos archivos en la carpeta `API` creada.

En el archivo `API_delay.h`, se deben ubicar los prototipos de las siguientes funciones y las declaraciones:

```c
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
```
nota: cuando se agregar carpetas a un proyecto de eclipse se deben incluir en el include path para que se incluya su contenido en la compilación.  Se debe hacer clic derecho sobre la carpeta con los archivos de encabezamiento y seleccionar la opción add/remove include path.


### Punto 2

Implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F401RE de acuerdo a una secuencia predeterminada como en la práctica 1, punto 2.

Cada led debe permanecer encendido 200 ms.  No debe encenderse más de un led simultáneamente en ningún momento.

