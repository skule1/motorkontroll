// vh340 driver vrsjon 3.5.2019 (30.01.2019) fungerer for opplasting



#include "Grove_Motor_Driver_TB6612FNG.h"
#include <Wire.h>

MotorDriver motor;
int pot, pot1;
void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Serial.begin(115200);
  Serial.println("\n");
  Serial.println(__FILE__);
  Serial.print("Kompilert den: ");
  Serial.print(__DATE__);
  Serial.print(" : ");
  Serial.println(__TIME__);
  Serial.println();

  Wire.begin(D2,D1);

  motor.init();
  pinMode(D5, INPUT_PULLUP);  // D5=GIO14
  pinMode(D6, INPUT_PULLUP);  // D6=GIO12
}

void loop() {


  pot1 = analogRead(A0);       // A0 = ADC0

  if (digitalRead(D5) == LOW)  // positiv omrdringing
    pot = map(pot1, 13, 163, 0, 255);
  else if (digitalRead(D6) == LOW)  // negativ omdreining
    pot = map(pot1, 13, 163, 0, -255);
  else  // midtstilt, begge veier
    pot = map(pot1, 13, 163, -255, 255);

  motor.dcMotorRun(MOTOR_CHA, pot);
  // drive 2 dc motors at speed=255, clockwise
  Serial.print("run at speed=");
  Serial.print(pot1);
  Serial.print(" : ");
  Serial.print(pot);
  Serial.print(" : ");
  Serial.print(digitalRead(D5));
  Serial.print(" : ");
  Serial.println(digitalRead(D6));
}