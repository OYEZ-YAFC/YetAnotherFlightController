#include <Servo.h>

Servo esc;   // Création de l'objet permettant le contrôle de l'ESC

int val = 0; // 

void setup() {
  esc.attach(10); // On attache l'ESC au port numérique 9 (port PWM obligatoire)
  delay(15);
  //Serial.begin(9600);

  // Initialisation de l'ESC
  //  (certains ESC ont besoin d'une "procédure d'initialisation"
  //   pour devenir opérationnels - voir notice)
  esc.writeMicroseconds(1500);
  delay(7000);
  for (int i=0; i<1200; i+=100){
    esc.writeMicroseconds(i);            // 
    delay(1000);
  }
   // Quelques informations pour l'utilisateur
   //Serial.println("Saisir un nombre entre 0 et 179");
   //Serial.println("(0 = arret - 179 = vitesse maxi");
   //Serial.println(" demarrage a partir de 20)");
   }

void loop() {
  esc.writeMicroseconds(1100);            // 
  delay(1000);
  esc.writeMicroseconds(1300);            // 
  delay(1000);
}