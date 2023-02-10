#include <Servo.h>

Servo esc;   // Création de l'objet permettant le contrôle de l'ESC

void setup() {
  esc.attach(10);
  delay(15);
  Serial.begin(9600);

  for(i = 50; i < 130; i++){
    esc.write(i);
    Serial.println(i);
    delay(1000);
  }
}

void loop() {
  esc.write(105);            // 
  delay(1000);
  esc.write(91);            // 
  delay(2000);
}