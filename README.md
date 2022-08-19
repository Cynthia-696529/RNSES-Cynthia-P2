# RNSES-Cynthia-P2
## Tabla de contenidos 
* [Información](#info)
* [Tarea 1. Crear dos tareas](#tarea1)
* [Tarea 2. Conectar un sensor inercial por I2C (o SPI)](#tarea2)

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

* Código

```
#include <Arduino.h>

#include <Wire.h> //librería para conectar por I2C
 
//Direccion I2C de la IMU
#define MPU 0x68
 
//Ratios de conversion
#define A_R ((32768.0/2.0)/9.8)
 
 
//MPU-6050 da los valores en enteros de 16 bits
//Valores RAW
int16_t AcX, AcY, AcZ;

const int pinSDA = 17; // Pin de conexión SDA (MPU6050) y pin 17 ESP32
const int pinSCL = 5;  // Pin de conexión SCL (MPU6050) y pin 5 ESP32
const int pinLED = 12; // Pin de conexión LED


void setup() {
  Wire.begin(pinSDA, pinSCL);  // pin 17(GPI17) = SDA , pin 5(GPIO5) = SCL
  Wire.beginTransmission(MPU); // Iniciar transmisión al dispositivo esclavo I2C con la dirección dada.
  Wire.write(0x6B);            // Iniciar MPU
  Wire.endTransmission(true); // Fin de la transmisión
  Serial.begin(112500);   // ojo! con la velocidad
  pinMode(12, OUTPUT);  // se establece el pin como una salida
  xTaskCreate(Tarea1,"Tarea1",1000,NULL,1,NULL);
  xTaskCreate(Tarea2,"Tarea2",1000,NULL,2,NULL);
  
  delay(1000);
}

void loop() {
  delay(1000);
}

void Tarea1( void * parameter )
{
    while(1){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX // DATASHEET
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,6,true);
       
    AcX = Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 reg -> Unimos valor alto con bajo (OBTENEMOS 16bits)
    AcY = Wire.read()<<8|Wire.read();
    AcZ = Wire.read()<<8|Wire.read();  
         
    vTaskDelay (100);
    }
}

void Tarea2( void * parameter)
{
  while(1){
    Serial.println(String(AcX/A_R) + "," + String(AcY/A_R)+ "," + String(AcZ/A_R));
    xTaskCreate(Tarea3,"Tarea3",1000,NULL,3,NULL); 
    vTaskDelay(1000);                 // Espero 200 ms
  }
    //vTaskDelete( NULL );
}

void Tarea3( void * parameter)
{ 
    digitalWrite(pinLED, HIGH); // LED ON
    vTaskDelay(200);                 // Espero 200 ms
    digitalWrite(pinLED, LOW);  // LED OFF
    vTaskDelete( NULL );
}

```

