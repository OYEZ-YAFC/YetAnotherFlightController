#include <Servo.h>

Servo esc;   // Création de l'objet permettant le contrôle de l'ESC

void setup() {
  esc.attach(10);
  delay(15);
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);


  esc.write(0);
  delay(1000);
  esc.write(84);
  delay(1000);


  /*
  for(int i = 51; i < 130; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    esc.write(i);
    Serial.println(i);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off 
    delay(500);
  }*/

}

void loop() {
  esc.write(90);
  delay(2000);
  esc.write(60);
  delay(2500);
}