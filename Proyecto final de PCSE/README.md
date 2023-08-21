# Proyecto PCSE: tema de Monitoreo y Visualización de Temperatura “Maestro-Esclavo con STM32”

Este proyecto demuestra la implementación de una comunicación maestro-esclavo entre dos placas STM32 utilizando diferentes protocolos de comunicación. La placa STM32F401RE actúa como maestro y se comunica con la placa STM32F030R8 configurada como esclavo. La comunicación se realiza a través de los protocolos UART y SPI, y los datos de temperatura capturados por un sensor DHT22 se presentan en una pantalla DFR0928.
![WhatsApp Image 2023-08-21 at 6 19 10 PM](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/e71f1611-975d-48ab-99a1-a6d855e5b61f)


## Introducción

En este proyecto, se presenta la implementación y explicación de los protocolos de comunicación UART y SPI, así como la configuración de los pines one wire en placas STM32. Se aborda la comunicación entre dos placas STM32 utilizando los protocolos mencionados y se demuestra cómo transmitir datos de temperatura desde una placa maestro a una placa esclavo, visualizando los resultados en una pantalla DFR0928.

###  Materiales

- Placa STM32 NUCLEO-F401RE (Maestro)
- Placa STM32 STM32F030R8T6 (Esclavo)
- Sensor DHT22 para medición de temperatura y humedad
- Pantalla DFR0928 para visualización de datos
- Cables de conexión


## Objetivos

El objetivo principal de este proyecto es comprender y aplicar los conceptos de comunicación UART y SPI, así como la configuración de pines GPIO en el entorno de desarrollo STM32. Además, se pretende lograr lo siguiente:

- Implementar y configurar la comunicación UART entre dos placas STM32 para transmitir datos de temperatura.
- Utilizar el protocolo SPI y one-wire para enviar datos de temperatura desde la placa maestro a la pantalla DFR0928 en la placa esclavo.
- Demostrar la configuración de pines GPIO para activar sensores y controlar dispositivos externos.
- Realizar una presentación magistral que explique los protocolos implementados, su funcionamiento y su importancia en sistemas embebidos.

## Desarrollo

### Protocolo UART (Universal Asynchronous Receiver-Transmitter)

Se configuraron los pines de transmisión (TX) y recepción (RX) en ambas placas STM32. Se implementaron funciones para enviar y recibir datos a través de UART, permitiendo la comunicación asincrónica entre las placas.

### Protocolo SPI (Serial Peripheral Interface)

Se definieron los pines SCLK, MOSI, MISO y CS en ambas placas para implementar el protocolo SPI. Se enviaron datos de temperatura desde la placa maestro a la pantalla DFR0928 en la placa esclavo utilizando comandos SPI.

### Configuración de One Wire

Se configuraron un pin GPIO como salida para activar el sensor DHT22 y controlar la pantalla DFR0928. Se demostró cómo la configuración de pines es esencial para el control de dispositivos externos.


## Conclusiones

Este proyecto permitió adquirir experiencia práctica en la implementación de protocolos de comunicación UART y SPI, así como en la configuración de pines GPIO en placas STM32. La transmisión de datos en tiempo real y su visualización en la pantalla DFR0928 demostraron la importancia de estos conceptos en sistemas embebidos. El proyecto reafirma la relevancia de los protocolos y la configuración de pines en la comunicación efectiva entre dispositivos electrónicos y su aplicabilidad en diversas aplicaciones.
