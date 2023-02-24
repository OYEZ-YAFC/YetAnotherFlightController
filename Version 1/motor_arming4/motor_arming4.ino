// Arming of 3 motors at once (worked)
// "Please be careful"

#include <Servo.h>


// I2C and MPU module libraries for communication
#include <Wire.h>
#include <MPU6050.h>


Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

//MPU module
MPU6050 capteur;


void setup() {
/*
  Wire.begin();
  capteur.initialize();
  delay(500);*/


  esc1.attach(5);
  esc2.attach(6);
  esc3.attach(9);
  esc4.attach(10);

  esc1.write(84);
  esc2.write(84);
  esc3.write(84);
  esc4.write(84);
  //delay(15);

  //pinMode(LED_BUILTIN, OUTPUT);

/*
  delay(6000);

  for (int i = 0; i<720; i++){
    esc1.write(i/8);
    esc2.write(i/8);
    esc3.write(i/8);
    esc4.write(i/8);
  }
  for (int i = 720; i>0; i--){
    esc1.write(i/8);
    esc2.write(i/8);
    esc3.write(i/8);
    esc4.write(i/8);
  }
  */

  delay(1000);
}

void loop() {
  /*
  for (int i = 360; i<720; i++){
    esc1.write(i/8);
    esc2.write(i/8);
    esc3.write(i/8);
    esc4.write(i/8);
  }
  for (int i = 720; i>360; i--){
    esc1.write(i/8);
    esc2.write(i/8);
    esc3.write(i/8);
    esc4.write(i/8);
  }*/

  esc1.write(75);
  esc2.write(75);
  esc3.write(75);
  esc4.write(75);
  delay(10);
}