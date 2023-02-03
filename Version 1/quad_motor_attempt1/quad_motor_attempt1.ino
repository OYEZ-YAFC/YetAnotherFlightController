#include <Wire.h>
#include <MPU6050.h>

#define motorf_pin1 2
#define motorf_pin2 3
#define motorl_pin1 4
#define motorl_pin2 5
#define motorr_pin1 6
#define motorr_pin2 7
#define motorb_pin1 8
#define motorb_pin2 9

MPU6050 gy_521;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int motorf_speed;
int motorl_speed;
int motorr_speed;
int motorb_speed;

int currentBaseSpeed;
int motorf_offset = 0;
int motorl_offset = 0;
int motorr_offset = 0;
int motorb_offset = 0;

int stationnarySpeed = 125;
int takeOffSpeed = 160;

int timeInMs;



void setup(){
  Wire.begin();

  Serial.begin(9600); // initializing serial
  Serial.println("Initializing.....");

  Serial.println ("Initializing MPU and testing connections");
  gy_521.initialize();
  Serial.println(gy_521.testConnection( ) ? "Successfully Connected" : "Connection failed");
  delay(2000);
  Serial.print("Reading Values");
  delay(2000);

  currentBaseSpeed = 0;
  
  }

void loop(){
  updateMotorSpeed();
  timeInMs = millis();
  if (timeInMs > 4000){
    currentBaseSpeed = stationarySpeed;
  } else if (timeInMs > 2000){
    currentBaseSpeed = takeOffSpeed;
  }
}

void updateMotorSpeed(){
  gy_521.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, -125, 125);
  ay = map(ay, -17000, 17000, -125, 125);

  motorl_speed = currentBaseSpeed + motorl_offset - ax;
  motorr_speed = currentBaseSpeed + motorr_offset + ax;

  motorf_speed = currentBaseSpeed + motorf_offset - ay;
  motorb_speed = currentBaseSpeed + motorb_offset + ay;

  analogWrite(motorf_pin2, motorf_speed);
  analogWrite(motorb_pin2, motorb_speed);
  analogWrite(motorr_pin2, motorr_speed);
  analogWrite(motorl_pin2, motorl_speed);
}