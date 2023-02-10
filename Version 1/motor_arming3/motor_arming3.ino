#include <Servo.h>

Servo esc1;
Servo esc2;
Servo esc3;

void setup() {
  esc1.attach(5);
  esc2.attach(6);
  esc3.attach(9);
  delay(15);

  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);

  esc1.write(0);
  esc2.write(0);
  esc3.write(0);
  delay(1000);
  esc1.write(84);
  esc2.write(84);
  esc3.write(84);
  delay(1000);
  esc1.write(0);
  esc2.write(0);
  esc3.write(0);

}

void loop() {
  esc1.write(85);
  esc2.write(85);
  esc3.write(85);
  delay(2000);
  esc1.write(60);
  esc2.write(60);
  esc3.write(60);
  delay(2500);
}