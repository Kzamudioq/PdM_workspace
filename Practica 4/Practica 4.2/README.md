# Punto 2

## Objetivo

Implementar un módulo de software para trabajar con anti-rebotes por software y utilizarlo para cambiar la frecuencia de toggleo del LED2 en la placa NUCLEO-F401RE entre 100 ms y 500 ms cada vez que se presione la tecla, como se evidencia en el siguiente video:


https://github.com/Kzamudioq/PdM_workspace/assets/138271936/a5aebb6e-15b5-4e48-8f03-59ae022e6e5c


## Estructura de directorios

Para comenzar, hemos creado un nuevo proyecto como copia del proyecto realizado en el Punto 1 de la Práctica 4. A continuación, hemos implementado el módulo de software necesario y organizado los archivos en las siguientes carpetas:

- `/drivers/API/src`: Contiene el archivo fuente "API_debounce.c".
- `/drivers/API/inc`: Contiene el archivo de cabecera "API_debounce.h".

## Contenido de "API_debounce.h"

```c
#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
} debounceState_t;

void debounceFSM_init(void);
void debounceFSM_update(void);
bool_t readKey(void);

#endif /* API_DEBOUNCE_H */
```
En este archivo de cabecera, hemos definido los prototipos de las funciones públicas del módulo API_debounce, así como también la declaración del tipo de enumeración "debounceState_t", que representa los estados posibles de la MEF Anti-Rebote.

La función debounceFSM_init() se encarga de inicializar la MEF Anti-Rebote. La función debounceFSM_update() actualiza la MEF Anti-Rebote y controla los flancos del pulsador. La función readKey() es utilizada para leer el estado interno de la MEF y determinar si la tecla fue presionada.

## Contenido de "API_debounce.c"

