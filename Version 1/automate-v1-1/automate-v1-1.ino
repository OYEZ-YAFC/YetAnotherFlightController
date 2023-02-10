/**
 * @file automate-v1-1.ino
 * @author OYEZ team - see readme.md
 * @brief First automaton attempt for the quad motor drone
 * @version 1
 * @date 2023-02-10
 * 
 */

// ESC library to control the motors
#include <Servo.h>

// I2C and MPU module libraries for communication
#include <Wire.h>
#include <MPU6050.h>



/*
 * Automate states enum
 */
enum {
    IDLE,
    STATIONNARY,
    TAKEOFF,
    FORWARD
} etat = IDLE;


// Declaring the motors object
Servo FLmotor;
Servo FRmotor;
Servo BRmotor;
Servo BLmotor;

// Defining motor pins
#define motorfl_pin1 5  // Front Left (fr) - Blue wire
#define motorfr_pin2 6  // Front Right (fl) - Purple wire
#define motorbr_pin1 9  // Back Right (br) - Green wire
#define motorbl_pin2 10 // Back Left (bl) - Grey wire

// Declaring the MPU module
MPU6050 capteur;

// Variables to store acceleration and gyroscopic values
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Motor values transmitted through the ESC
int motorfl_speed;
int motorfr_speed;
int motorbr_speed;
int motorbl_speed;

// Current base speed used to calculate the motor values (varies depending on the state)
int currentBaseSpeed;

// Specific offset values (is it needed?)
int motorfl_offset = 0;
int motorfr_offset = 0;
int motorbr_offset = 0;
int motorbl_offset = 0;

// Defining specific motor values
int idleSpeed = 0;
int stationnarySpeed = 90;
int takeOffSpeed = 120;

// Declaring a time variable (used in TimeOut)
int timeInMs;

// tests
//int val = 0; // 

void setup() {

    // MPU module SETUP

    Wire.begin();

    Serial.begin(9600); // initializing serial
    Serial.println("Initializing.....");

    Serial.println ("Initializing MPU and testing connections");
    capteur.initialize();
    Serial.println(capteur.testConnection( ) ? "Successfully Connected" : "Connection failed");
    delay(2000);
    //Serial.print("Reading Values");
    //delay(2000);


    // ESC and motors SETUP

    Serial.println("Initializing motors / arming")
    // Attaching the motors to the ESC
    FLmotor.attach(5);
    FRmotor.attach(6);
    BRmotor.attach(9);
    BLmotor.attach(10);
    delay(15);

    // The following code executes the armament procedure
    pinMode(LED_BUILTIN, OUTPUT);

    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    FLmotor.write(0);
    FRmotor.write(0);
    BRmotor.write(0);
    BLmotor.write(0);
    delay(1000);
    FLmotor.write(84);  // 84 is the armament value
    FRmotor.write(84);
    BRmotor.write(84);
    BLmotor.write(84);
    delay(1000);
    FLmotor.write(0);   // Write back 0 for safety measures
    FRmotor.write(0);
    BRmotor.write(0);
    BLmotor.write(0);


    currentBaseSpeed = 0;
}

void loop() {
    timeInMs = millis();

    if (timeInMs > 30000){ // TIMEOUT
        while(1){
            writeAll(0);
            Serial.println("TimeOut");
            delay(1000);
        }
    }   


    switch(etat){
    
        case IDLE:
            currentBaseSpeed = idleSpeed;
            writeAll(0);
        break;;


        case STATIONNARY:
            currentBaseSpeed = stationnarySpeed;
            updateMotorSpeed();
        break;;


        case TAKEOFF:
            currentBaseSpeed = takeOffSpeed;
            updateMotorSpeed();
        break;;


        case FORWARD:
            currentBaseSpeed = 0;
            updateMotorSpeed();
        break;;

  }
}

void updateMotorSpeed(){
  capteur.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, -125, 125);
  ay = map(ay, -17000, 17000, -125, 125);

  motorfl_speed = currentBaseSpeed + motorl_offset - ax;
  motorfr_speed = currentBaseSpeed + motorr_offset + ax;

  motorbr_speed = currentBaseSpeed + motorf_offset - ay;
  motorbl_speed = currentBaseSpeed + motorb_offset + ay;

  analogWrite(motorf_pin2, motorf_speed);
  analogWrite(motorb_pin2, motorb_speed);
  analogWrite(motorr_pin2, motorr_speed);
  analogWrite(motorl_pin2, motorl_speed);
}

void writeAll(int value){
    FLmotor.write(value);
    FRmotor.write(value);
    BRmotor.write(value);
    BLmotor.write(value);
}