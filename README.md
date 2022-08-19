# RNSES-Cynthia-P2
## Tabla de contenidos 
* [Información](#info)
* [Tarea 1. Crear dos tareas](#technologies)
* [Tarea 2. Conectar un sensor inercial por I2C (o SPI)](#setup)

## Información
Comprender el uso y los conceptos asociados a un sistema operativo en tiempo real (RTOS)

Sistema FreeRTOS: https://www.freertos.org/Documentation/RTOS_book.html

## Tarea 1
Crear un programa que cree dos tareas, una que parpadee un LED cada 200 ms y otra que envíe un “hola mundo” por la UART cada segundo. https://github.com/uagaviria/ESP32_FreeRtos

* Código

```
#include <Arduino.h>
const int pinLED = 12; // Pin de conexión LED
void setup() {

  Serial.begin(112500); //ojo! con la velocidad
  delay(1000);
  
  pinMode(12, OUTPUT); 
  xTaskCreate(Tarea1,"Tarea1",1000,NULL,1,NULL); //num palabras que se usa como pila de tareas
  xTaskCreate(Tarea2,"Tarea2",1000,NULL,1,NULL);

}

void loop() {
  delay(1000);
}

void Tarea1( void * parameter )
{
    while(1){
      Serial.println("Hola mundo");
      vTaskDelay(1000);
    }
    
    //vTaskDelete( NULL );

}

void Tarea2( void * parameter)
{
  while(1){
    digitalWrite(pinLED, HIGH); //  LED ON.
    vTaskDelay(200);                 // Espero 200 ms
    digitalWrite(pinLED, LOW);  // LED OFF.
    vTaskDelay(200);  
  }
    //vTaskDelete( NULL );
}

```

## Tarea 2 
Conectar un sensor inercial por I2C (o SPI), muestrea la aceleración cada 100 ms y manda los datos cada segundo vía UART (cada vez que se envíe se activa un LED durante 200ms)

*
