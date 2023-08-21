![image](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/af76cc32-22f3-457b-8ccc-07d7c153652e)



# Proyecto PCSE: tema de Monitoreo y Visualización de Temperatura “Maestro-Esclavo con STM32”

Este proyecto demuestra la implementación de una comunicación maestro-esclavo entre dos placas STM32 utilizando diferentes protocolos de comunicación. La placa STM32F401RE actúa como maestro y se comunica con la placa STM32F030R8 configurada como esclavo. La comunicación se realiza a través de los protocolos UART y SPI, y los datos de temperatura capturados por un sensor DHT22 se presentan en una pantalla DFR0928.
![WhatsApp Image 2023-08-21 at 6 19 10 PM](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/e71f1611-975d-48ab-99a1-a6d855e5b61f)


## Introducción

En este proyecto, se presenta la implementación y explicación de los protocolos de comunicación UART y SPI, así como la configuración de los pines one wire en placas STM32. Se aborda la comunicación entre dos placas STM32 utilizando los protocolos mencionados y se demuestra cómo transmitir datos de temperatura desde una placa maestro a una placa esclavo, visualizando los resultados en una pantalla DFR0928.

###  Materiales

![image](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/f4eb165a-0563-4c8b-b246-b483456439ed)


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

En este proyecto, se implementó el protocolo SPI para la comunicación con la pantalla DFR0928. Este protocolo es utilizado para transferir datos entre dispositivos, donde un dispositivo maestro (en este caso, una placa STM32) controla la comunicación con uno o varios dispositivos esclavos.

#### Funciones Implementadas

Se crearon varias funciones específicas para la comunicación con la pantalla DFR0928 utilizando el protocolo SPI. Estas funciones permiten seleccionar/deseleccionar el dispositivo, enviar comandos y datos, y realizar un reinicio. Aquí están las funciones esenciales:

- `DFR0928_Select()`: Esta función establece el pin de selección en bajo para activar la comunicación con la pantalla.

- `DFR0928_Unselect()`: Esta función establece el pin de selección en alto para finalizar la comunicación con la pantalla.

- `DFR0928_Reset()`: Mediante esta función, se realiza un reinicio del dispositivo DFR0928 utilizando un pin de reinicio.

- `DFR0928_WriteCommand(uint8_t cmd)`: Esta función envía un comando a la pantalla DFR0928 utilizando el protocolo SPI. Se configura el pin DC (Data/Command) para indicar que se está enviando un comando.

```c
static void DFR0928_Select() {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

void DFR0928_Unselect() {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

static void DFR0928_Reset() {
    HAL_GPIO_WritePin(RT_GPIO_Port, RT_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(RT_GPIO_Port, RT_Pin, GPIO_PIN_SET);
}

static void DFR0928_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&DFR0928_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}

static void DFR0928_WriteData(uint8_t* buff, size_t buff_size) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    HAL_SPI_Transmit(&DFR0928_SPI_PORT, buff, buff_size, HAL_MAX_DELAY);
}

- `DFR0928_WriteData(uint8_t* buff, size_t buff_size)`: Con esta función, se envían datos a la pantalla DFR0928. Se configura el pin DC para indicar que se están enviando datos.

```

### Configuración de One Wire

Se configuraron un pin GPIO como salida para activar el sensor DHT22 y controlar la pantalla DFR0928. Se demostró cómo la configuración de pines es esencial para el control de dispositivos externos. En el proyecto, se utilizó el sensor DHT22 para medir la temperatura y la humedad, la comunicación con este sensor se realizó a través de un protocolo one wire. Además, se implementó una función `microDelay()` para generar pausas temporales necesarias en la comunicación.

#### Inicio de la Comunicación

La función `DHT22_Start()` se encarga de iniciar la comunicación con el sensor DHT22. Aquí se describen los pasos clave de esta función:

```c
uint8_t DHT22_Start(void)
{
  uint8_t Response = 0;
  GPIO_InitTypeDef GPIO_InitStructPrivate = {0};
  GPIO_InitStructPrivate.Pin = DHT22_Pin;
  GPIO_InitStructPrivate.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT22_GPIO_Port, &GPIO_InitStructPrivate); // set the pin as output
  HAL_GPIO_WritePin (DHT22_GPIO_Port, DHT22_Pin, 0);   // pull the pin low
  microDelay (1300);   // wait for 1300us
  HAL_GPIO_WritePin (DHT22_GPIO_Port, DHT22_Pin, 1);   // pull the pin high
  microDelay (30);   // wait for 30us
  GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DHT22_GPIO_Port, &GPIO_InitStructPrivate); // set the pin as input
  microDelay (40);
  if (!(HAL_GPIO_ReadPin (DHT22_GPIO_Port, DHT22_Pin)))
  {
    microDelay (80);
    if ((HAL_GPIO_ReadPin (DHT22_GPIO_Port, DHT22_Pin))) Response = 1;
  }
  pMillis = HAL_GetTick();
  cMillis = HAL_GetTick();
  while ((HAL_GPIO_ReadPin (DHT22_GPIO_Port, DHT22_Pin)) && pMillis + 2 > cMillis)
  {
    cMillis = HAL_GetTick();
  }
  return Response;
}
```
1. Configuración del pin GPIO como salida y ponerlo en bajo para indicar al sensor que se solicita información.
2. Espera de un tiempo específico para permitir que el sensor reconozca la señal de inicio.
3. Poner el pin del sensor en alto durante un corto período y esperar para que el sensor responda.
4. Configurar el pin GPIO como entrada con resistencia pull-up para que el sensor pueda responder.
5. Verificar si el sensor responde, lo que indica que está listo para transmitir datos.

#### Lectura de Datos

La función `DHT22_Read()` se utiliza para leer datos del sensor DHT22. Aquí se detallan los pasos involucrados:

```c
uint8_t DHT22_Read(void)
{
  uint8_t a,b = 0;
  for (a=0;a<8;a++)
  {
    pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while (!(HAL_GPIO_ReadPin (DHT22_GPIO_Port, DHT22_Pin)) && pMillis + 2 > cMillis)
    {  // wait for the pin to go high
      cMillis = HAL_GetTick();
    }
    microDelay (40);   // wait for 40 us
    if (!(HAL_GPIO_ReadPin (DHT22_GPIO_Port, DHT22_Pin)))   // if the pin is low
      b&= ~(1<<(7-a));
    else
      b|= (1<<(7-a));
    pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while ((HAL_GPIO_ReadPin (DHT22_GPIO_Port, DHT22_Pin)) && pMillis + 2 > cMillis)
    {  // wait for the pin to go low
      cMillis = HAL_GetTick();
    }
  }
  return b;
}
```
1. Esperar a que el sensor eleve el nivel de la señal, indicando la transmisión de un bit.
2. Esperar un breve tiempo para permitir que el bit se transmita completamente.
3. Leer el estado del pin del sensor y registrar el bit correspondiente.
4. Esperar a que el sensor baje el nivel de la señal para indicar el final de la transmisión del bit actual.

La correcta configuración de los pines GPIO y el uso de la función `microDelay()` son esenciales para lograr una comunicación efectiva con el sensor DHT22.


## Conclusiones

Este proyecto permitió adquirir experiencia práctica en la implementación de protocolos de comunicación UART y SPI, así como en la configuración de pines GPIO en placas STM32. La transmisión de datos en tiempo real y su visualización en la pantalla DFR0928 demostraron la importancia de estos conceptos en sistemas embebidos. El proyecto reafirma la relevancia de los protocolos y la configuración de pines en la comunicación efectiva entre dispositivos electrónicos y su aplicabilidad en diversas aplicaciones.
