# Práctica 5 - Punto 1: Implementación del Módulo UART

En este punto de la Práctica 5, se requiere implementar un módulo de software para trabajar con la UART (Universal Asynchronous Receiver/Transmitter). La UART es una interfaz de comunicación serie ampliamente utilizada para enviar y recibir datos de forma asíncrona entre dispositivos.

## Estructura del Proyecto

Para comenzar, se debe crear un archivo fuente `API_uart.c` junto con su correspondiente archivo de cabecera `API_uart.h`. Ambos archivos deben ubicarse en el proyecto dentro de las carpetas `/drivers/API/src` y `/drivers/API/inc`, respectivamente. Estas carpetas están destinadas a contener los archivos relacionados con los controladores de bajo nivel (drivers) utilizados en el proyecto.

### Diagrama del Módulo UART

                          API_uart.h                      API_uart.c
                          ┌────────────┐                  ┌────────────┐
                          │            │                  │            │
                          │  uartInit()│<────────────────▶│uartInit()  │
                          │            │                  │            │
                          └────────────┘                  └────────────┘
                                ▲                              ▲
                                │                              │
                                │                              │
                          ┌─────┴───────┐               ┌─────┴───────┐
                          │             │               │             │
                          │uartSendString│◀─────────────│uartSendString│
                          │             │               │             │
                          └─────┬───────┘               └─────┬───────┘
                                │                              │
                                │                              │
                                ▼                              ▼
                          ┌─────┴───────┐               ┌─────┴───────┐
                          │             │               │            │
                          │uartSendStringSize│◀──────────│uartSendStringSize│
                          │            │                │            │
                          └────────────┘                └────────────┘

## API_uart.h - Prototipos de Funciones Públicas

En el archivo `API_uart.h`, se deben colocar los prototipos de las funciones públicas que estarán disponibles para el resto del programa que utilice el módulo UART. En este caso, las funciones públicas son las siguientes:

```c
bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
```

## API_uart.c - Implementación de las Funciones

En el archivo API_uart.c, se ubicarán los prototipos de las funciones privadas y la implementación de todas las funciones del módulo, tanto privadas como públicas. Aquí es donde realmente se define el comportamiento de cada función del módulo UART.

### Función uartInit()

La función uartInit() es responsable de realizar toda la inicialización de la UART. Además, debe imprimir por la terminal serie un mensaje que indique los parámetros de configuración utilizados para la comunicación UART.

La función uartInit() debe devolver:

- true: si la inicialización es exitosa.
- false: si la inicialización no es exitosa.

Esta función es crucial, ya que garantiza que la UART esté correctamente configurada para permitir la transmisión y recepción de datos.

### Función uartSendString()

La función uartSendString(uint8_t *pstring) recibe un puntero a un string que se desea enviar por la UART completo, hasta el caracter de finalización '\0'. Esta función debe utilizar la función de la HAL HAL_UART_Transmit(...) para transmitir el string a través de la UART.

La transmisión de strings es una operación común en las comunicaciones serie, y esta función facilita el envío de mensajes o datos a otros dispositivos o terminales conectados.

### Función uartSendStringSize()
La función uartSendStringSize(uint8_t * pstring, uint16_t size) recibe un puntero a un string que se desea enviar por la UART y un entero que indica la cantidad de caracteres que se deben enviar. La función debe utilizar la función HAL_UART_Transmit(...) para transmitir el string.

Esta función es útil cuando se quiere enviar solo una parte de un string o cuando se quiere controlar la cantidad de caracteres enviados.
