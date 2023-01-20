#include <Wire.h>
#include <MPU6050.h>

#define motor1_pin1 2
#define motor1_pin2 3
#define motor2_pin1 4
#define motor2_pin2 5

MPU6050 gy_521;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int motor1_speed;
int motor2_speed;

void setup ( )
{
  Wire.begin( );

  Serial.begin(9600); // initializing serial
  Serial.println("Initializing.....");

  Serial.println ("Initializing MPU and testing connections");
  gy_521.initialize ( );
  Serial.println(gy_521.testConnection( ) ? "Successfully Connected" : "Connection failed");
  delay(2000);
  Serial.print("Reading Values");
  delay(2000);
  }

void loop ( )
{
  gy_521.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, -125, 125);

  motor1_speed = 125+ax; //To move first motor
  motor2_speed = 125-ax; //To move second motor

  Serial.print ("M1= ");
  Serial.print (motor1_speed, DEC);

  Serial.print ("\tM2 = ");
  Serial.println (motor2_speed, DEC);

  delay(300);
  analogWrite (motor1_pin2, motor1_speed);
  analogWrite (motor2_pin2, motor2_speed);
  delay (300);
}