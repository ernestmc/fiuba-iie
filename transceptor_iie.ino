#include <TimerOne.h>

// Pin de entrada al ADC: 14 = A0
#define ENTRADA_ADC A0
// Frecuencia de muestreo en Hz
#define FREC_MUESTREO 4000
// Periodo de muestreo en us
#define MICROS_MUESTREO ((unsigned long)1e6 / FREC_MUESTREO)
// Semiperiodo de parpadeo del led en ms
#define SEMIPERIODO_LED 300

void setup() {
  // Configurar timer de muestreo a 4kHz --> 250 us)
  Timer1.initialize(MICROS_MUESTREO);
  Timer1.attachInterrupt(takeSample);
  
  // Configurar UART para comunicación serie
  Serial.begin(57600);
  
  // Configurar LED como salida
  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long tiempo_actual;
unsigned long tiempo_anterior = 0;
int estado_led = LOW;

void loop() {
  tiempo_actual = millis();
  if (tiempo_actual - tiempo_anterior > SEMIPERIODO_LED) {
    tiempo_anterior = tiempo_actual;
    estado_led = !estado_led;
  }  
  digitalWrite(LED_BUILTIN, estado_led);
}

void takeSample() {
  uint8_t muestra;
  // Leer en ADC
  muestra = analogRead(ENTRADA_ADC) >> 2;
  // Enviar el dato por la UART
  Serial.write(muestra);
}

void serialEvent() {
  uint8_t muestra;
  // Leer el dato recibido
  muestra = Serial.read();
  // Enviarlo al conversor digital-analógico
 writeDAC(muestra); 
}

void writeDAC(uint8_t dato) {
  // Escribir el dato en el puerto de salida
}

