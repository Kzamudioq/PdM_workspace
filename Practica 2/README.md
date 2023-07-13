# Práctica 2

En esta práctica, el objetivo es implementar un módulo de software para trabajar con retardos no bloqueantes. Se deben desarrollar funciones auxiliares en el archivo fuente `main.c` y su correspondiente archivo de cabecera `main.h` para utilizar estos retardos no bloqueantes.

## Objetivo

Implementar un módulo de software para trabajar con retardos no bloqueantes en STM nucleo F401RE y adaptación de protoboard con dos led.

![STM nucleo F401RE ](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/861f3a4b-fcfc-4d8b-8d17-5e670c5e611d)


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

## Implementación

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
