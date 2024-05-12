#include <math.h>
#include <Servo.h> // Incluye la biblioteca Servo

// Objeto del servo motor
Servo servo;

// Define el pin del servo motor
const int servoPin = 9;

// Variables para la ubicación y fecha/hora
float latitud = 4.609740; // Latitud en grados 
float longitud = -74.081742; // Longitud en grados 
int dia = 1; // Día del año (1 al 365)
int hora; // Hora (se calculará más adelante)
int minuto; // Minuto (se calculará más adelante)
int segundo; // Segundo (se calculará más adelante)

// Variables para la posición del sol
float declinacionSolar;
float alturaSolar;
float azimutSolar;

// Función para calcular la declinación solar (proporcionada anteriormente)
float calcularDeclinacionSolar() {
  // ... (implementa la fórmula aquí)
}

// Función para calcular la altitud solar (proporcionada anteriormente)
float calcularAlturaSolar() {
  // ... (implementa la fórmula aquí)
}

// Función para calcular el azimut solar (proporcionada anteriormente)
float calcularAzimutSolar() {
  // ... (implementa la fórmula aquí)
}

void setup() {
  // Inicia la comunicación serial
  Serial.begin(9600);

  // Conecta el servo motor al pin definido
  servo.attach(servoPin);

  // Calcula la declinación solar inicial
  declinacionSolar = calcularDeclinacionSolar();
}

void loop() {
  // Actualiza la hora actual
  hora = millis() / 3600000;
  minuto = (millis() % 3600000) / 60000;
  segundo = (millis() % 60000) / 1000;

  // Calcula la posición del sol
  declinacionSolar = calcularDeclinacionSolar();
  alturaSolar = calcularAlturaSolar();
  azimutSolar = calcularAzimutSolar();

  // Calcula el ángulo del servo en función del azimut
  float anguloServo = azimutSolar;

  // Limita el ángulo del servo (0 a 180 grados)
  if (anguloServo < 0) {
    anguloServo = 0;
  } else if (anguloServo > 180) {
    anguloServo = 180;
  }

  // Controla el servo motor
  servo.write(anguloServo);

  // Imprime los datos en el monitor serial
  Serial.print("Fecha: ");
  Serial.print(dia);
  Serial.print("/");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.println(segundo);

Serial.print("Declinación solar: ");
Serial.print(declinacionSolar, 2);
Serial.println("°");

Serial.print("Altura solar: ");
Serial.print(alturaSolar, 2);
Serial.println("°");

Serial.print("Azimut solar: ");
Serial.print(azimutSolar, 2);
Serial.println("°");

Serial.print("Ángulo servo: ");
Serial.println(anguloServo);

// Espera un segundo antes de realizar el siguiente ciclo
delay(1000);
}

