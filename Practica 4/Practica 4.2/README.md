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
```c
#include "API_debounce.h"

// Variable privada global para almacenar el estado de la tecla
static bool_t keyPressed = false;

void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue) {
    *currentState = initialValue;
    keyPressed = false; // Inicializamos la variable global keyPressed en falso
}

void debounceFSM_update(debounceState_t *currentState, delay_t *delay) {
    switch (*currentState) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
                *currentState = BUTTON_FALLING;
            }
            break;
        case BUTTON_FALLING:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET && delayRead(delay)) {
                *currentState = BUTTON_DOWN;
                keyPressed = true; // Se activó un flanco descendente, establecemos keyPressed en true
            } else {
                *currentState = BUTTON_UP;
            }
            break;
        case BUTTON_DOWN:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
                *currentState = BUTTON_RAISING;
            }
            break;
        case BUTTON_RAISING:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET && delayRead(delay)) {
                *currentState = BUTTON_UP;
                keyPressed = false; // Se activó un flanco ascendente, establecemos keyPressed en false
            } else {
                *currentState = BUTTON_DOWN;
            }
            break;
        default:
            // Manejo de estado inesperado
            Error_Handler();
            break;
    }
}

bool_t readKey(void) {
    bool_t keyStatus = keyPressed; // Leemos el estado de la tecla almacenado en keyPressed
    keyPressed = false; // Reseteamos el estado de keyPressed para la siguiente lectura
    return keyStatus; // Devolvemos el estado de la tecla
}
```
- La variable privada global ´keyPressed´ se utiliza para almacenar el estado de la tecla. Se inicializa como false en la función debounceFSM_init, y su valor puede cambiar cuando ocurren flancos ascendentes o descendentes.

- debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue): Esta función inicializa la MEF Anti-Rebote. Recibe como argumentos un puntero a la variable currentState, que almacenará el estado actual de la MEF, y un valor initialValue, que indica el estado inicial de la MEF. Además, inicializa la variable global keyPressed en false.

- debounceFSM_update(debounceState_t *currentState, delay_t *delay): Esta función actualiza la MEF Anti-Rebote en cada iteración del programa principal. Recibe como argumentos un puntero a la variable currentState, que almacena el estado actual de la MEF, y un puntero a la estructura delay_t, que es utilizada para implementar los retardos no bloqueantes. Dependiendo del estado actual de la MEF y del estado del pulsador, se realiza la transición entre estados y se activa la variable keyPressed en caso de que ocurra un flanco ascendente o descendente.

- bool_t readKey(void): Esta función se utiliza para leer el estado interno de la MEF Anti-Rebote y determinar si ocurrió un flanco descendente en el pulsador. Retorna true si ocurrió un flanco descendente y false en caso contrario. Además, resetea el estado interno de la MEF almacenado en keyPressed para futuros flancos.
