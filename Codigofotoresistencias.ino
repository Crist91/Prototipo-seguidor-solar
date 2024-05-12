#include <Servo.h>

// Pines analógicos para las dos fotoresistencias
const int fotoresistenciaPin1 = A0;
const int fotoresistenciaPin2 = A1;

// Pin PWM para el servomotor
const int servoPin = 9;

Servo servoMotor;

void setup() {
  // Inicializar el servomotor
  servoMotor.attach(servoPin);
}

void loop() {
  // Leer el valor de las dos fotoresistencias
  int luz1 = analogRead(fotoresistenciaPin1);
  int luz2 = analogRead(fotoresistenciaPin2);

  // Calcular la diferencia entre los valores de luz
  int diferenciaLuz = luz1 - luz2;

  // Convertir la diferencia de luz en un ángulo para el servo (-90 a 90 grados)
  int angulo = map(diferenciaLuz, -1023, 1023, -90, 90);

  // Mover el servo a la posición deseada
  servoMotor.write(angulo);

  // Esperar un tiempo antes de tomar la siguiente lectura
  delay(100); // Ajustar según la frecuencia de muestreo deseada
}
