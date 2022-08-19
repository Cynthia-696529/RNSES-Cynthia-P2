#include <Arduino.h>
const int pinLED = 12; // Pin de conexión LED
void setup() {

  Serial.begin(112500);
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
    digitalWrite(pinLED, HIGH); // Enciende el LED.
    vTaskDelay(200);                 // Espero 200 ms
    digitalWrite(pinLED, LOW);  // Apaga el LED.
    vTaskDelay(200);  
  }
    //vTaskDelete( NULL );
}
