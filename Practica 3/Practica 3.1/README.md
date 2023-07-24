# Punto 1: Configuración de Retardos No Bloqueantes

## Objetivo
El objetivo de este punto es configurar y utilizar retardos no bloqueantes en un nuevo proyecto basado en el proyecto realizado para la Práctica 2. Los retardos no bloqueantes permitirán generar intervalos de tiempo precisos sin bloquear la ejecución del programa.

## Configuración de Retardos No Bloqueantes
Para configurar los retardos no bloqueantes, siga los siguientes pasos:

1. Cree un nuevo proyecto como copia del proyecto realizado para la Práctica 2.
2. Cree una carpeta llamada "API" dentro de la carpeta "Drivers" en la estructura de directorios del nuevo proyecto.
3. Dentro de la carpeta "API", cree las subcarpetas "Src" e "Inc".
4. Implemente las funciones necesarias para utilizar retardos no bloqueantes en un archivo fuente llamado "API_delay.c" con su correspondiente archivo de cabecera "API_delay.h" y colóquelos en las carpetas "Src" e "Inc" respectivamente.
5. En el archivo "API_delay.h", ubique los prototipos de las siguientes funciones y las declaraciones:

```c
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
```
5. En el archivo "API_delay.c", ubique la implementación para los retardos no bloqueantes:
```c
#include "API_delay.h"

void delayInit(delay_t *delay, tick_t duration) {
   delay->startTime = 0;
   delay->duration = duration;
   delay->running = false;
}

bool_t delayRead(delay_t *delay) {
   if (!delay->running)
      return false;

   tick_t currentTime = HAL_GetTick();
   if (currentTime - delay->startTime >= delay->duration) {
      delay->running = false;
      return true;
   }

   return false;
}

void delayWrite(delay_t *delay, tick_t duration) {
   delay->startTime = HAL_GetTick();
   delay->duration = duration;
   delay->running = true;
}
``` 
*Nota*: Para que las carpetas agregadas sean reconocidas por el compilador, asegúrese de incluirlas en el "include path" de su proyecto. Haga clic derecho sobre la carpeta con los archivos de encabezado y seleccione la opción "Add/Remove Include Path".

Uso de Retardos No Bloqueantes
Una vez configurados los retardos no bloqueantes, puede utilizarlos en su programa para crear intervalos de tiempo precisos sin bloquear la ejecución del código.

Por ejemplo, para crear un retardo de 500 ms y después realizar una acción, puede hacer lo siguiente:

```c
#include "API_delay.h"

int main(void) {
    // Inicializar el retardo
    delay_t delay;
    delayInit(&delay, 500);

    while (1) {
        // Actualizar el retardo periódicamente
        delayWrite(&delay, 500);
        
        // Esperar hasta que se complete el retardo
        while (!delayRead(&delay)) {
            // Aquí puede realizar otras tareas mientras espera
        }

        // Realizar la acción después del retardo de 500 ms
        // ...
    }
}
```
## Solución
La configuración y uso de retardos no bloqueantes permitirá generar intervalos de tiempo precisos sin afectar la ejecución del programa. Con esta implementación, podrá realizar tareas temporales con mayor precisión y flexibilidad, mejorando la eficiencia y el rendimiento de su aplicación en la placa NUCLEO-F401RE.
