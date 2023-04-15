//proportionnelle : l'erreur est multiplier  par un gain
//integral : l'erreur est intégrée et mul par un gain
//derivee : l'erreur est derivée et mul par un gain
// NB  wind each of the i2c cables around a GND cable ==> reduce noise of the i2c comunnication
//servo.write(angle_value)  treats angle_value as an angle to which servo shaft has to be rotated.
//servo.writeMicroseconds(micro_secs)  treats micro_secs as pulse duration for the PWM to be fed to the servo.

/**
 * @file automate-v1-1.ino
 * @author OYEZ team - see readme.md
 * @brief First automaton attempt for the quad motor drone
 * @version 1
 * @date 2023-02-10
 * 
 */

#include <Wire.h> 
#include <Servo.h> //pwm

Servo frontleft_motor; //violet
Servo backright_motor; //gris
//mpu renvoie les données sur 16bits

int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
// valeur renvoyer par l'imu
// filtrer les valeurs renvoyer par le gyroscope et l'accelerometre

//float  angle_accX, angle_accY;
//float angle_gyrX, angle_gyrY;
//float angle_total_x, angle_total_y;

float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];

float elapsed_time, time, time_prev;

int i;

float rad_to_deg = 180/3.141592654;

float PID, pwm_left, pwm_right, error, previous_error;

float pid_p = 0;
float pid_i = 0;
float pid_d = 0;

double kp = 3.44;
double ki = 0.048;
double kd = 1.92;

double throttle = 778; // valeur initial de pwm (gaz)

float desired_angle = 0;

void setup(){
    Wire.begin(); // communication


    Wire.beginTransmission(0x68);//
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(250000);


    frontleft_motor.attach(9) ; //Violet
    backright_motor.attach(10); //Gris

    // armement / start the esc
    frontleft_motor.write(0);
    backright_motor.write(0);

    delay(1000);

    frontleft_motor.writeMicroseconds(1100);  
    backright_motor.writeMicroseconds(1100);

    time = millis();

    //Start counting time in milliseconds
    /*In order to start up the ESCs we have to send a min value
    * of PWM to them before connecting the battery. Otherwise
    * the ESCs won't start up or enter in the configure mode.
    * The min value is 1000us and max is 2000us, REMEMBER!*/
    
    frontleft_motor.writeMicroseconds(1100);
    backright_motor.writeMicroseconds(1000);
    /*delay(1000);
    frontleft_motor.write(0);   
    backright_motor.write(0);*/

    delay(7000);

}

void loop(){

  time_prev = time;
  time = millis();
  elapsed_time = (time - time_prev) / 1100; // /1000
  //the adress for this IMU is 0x68 
  //values of the accelerometer
  /*The tiemStep is the time that elapsed since the previous loop. 
   * This is the value that we will use in the formulas as "elapsedTime" 
   * in seconds. We work in ms so we haveto divide the value by 1000 
   to obtain seconds*/

  /*Reed the values that the accelerometre gives.
   * We know that the slave adress for this IMU is 0x68 in
   * hexadecimal. For that in the RequestFrom and the 
   * begin functions we have to put this value.*/

  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6,true);
  
  /*We have asked for the 0x3B register. The IMU will send a brust of register.
   * The amount of register to read is specify in the requestFrom function.
   * In this case we request 6 registers. Each value of acceleration is made out of
   * two 8bits registers, low values and high values. For that we request the 6 of them  
   * and just make then sum of each pair. For that we shift to the left the high values 
   * register (<<) and make an or (|) operation to add the low values.*/
  
  //Refer to the register map of mpu6050
  Acc_rawX=Wire.read()<<8|Wire.read(); //each value needs two registres
  Acc_rawY=Wire.read()<<8|Wire.read();
  Acc_rawZ=Wire.read()<<8|Wire.read();

  /*---X---*/
  Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
  /*---Y---*/
  Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
  
  /*Now we read the Gyro data in the same way as the Acc data. The adress for the
   * gyro data starts at 0x43. We can see this adresses if we look at the register map
   * of the MPU6050. In this case we request just 4 values. W don¡t want the gyro for 
   * the Z axis (YAW).*/

  //values of the gyroscope
  Wire.beginTransmission(0x68);
  Wire.write(0x43); //Gyro data first adress
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,4,true); //Just 4 registers
  
  Gyr_rawX=Wire.read()<<8|Wire.read(); //Once again we shif and sum
  Gyr_rawY=Wire.read()<<8|Wire.read();


  /*Now in order to obtain the gyro data in degrees/seconda we have to divide first
   the raw value by 131 because that's the value that the datasheet gives us*/
  /*---X---*/
  Gyro_angle[0] = Gyr_rawX/131.0; 
  /*---Y---*/
  Gyro_angle[1] = Gyr_rawY/131.0;
  
  /*Now in order to obtain degrees we have to multiply the degree/seconds
   *value by the elapsedTime.*/
  /*Finnaly we can apply the final filter where we add the acceleration
   *part that afects the angles and ofcourse multiply by 0.98 */

  /*---X axis angle---*/
  Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsed_time) + 0.02*Acceleration_angle[0];
  /*---Y axis angle---*/
  Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsed_time) + 0.02*Acceleration_angle[1];
  

  /*First calculate the error between the desired angle and 
   *the real measured angle*/
  error = Total_angle[1] - desired_angle;
  
  Serial.println (error);
  
  pid_p = kp*error;

  /*The integral part should only act if we are close to the
  desired position but we want to fine tune the error. That's
  why I've made a if operation for an error between -2 and 2 degree.
  To integrate we just sum the previous integral value with the
  error multiplied by  the integral constant. This will integrate (increase)
  the value each loop till we reach the 0 point*/

  if(-3 <error <3){pid_i = pid_i+(ki*error);  }

  pid_d = kd*((error - previous_error)/elapsed_time);
  PID = pid_p + pid_i + pid_d;

  ////////////////////////////////////////////////A faire 
  /*We know taht the min value of PWM signal is 1000us and the max is 2000. So that
  tells us that the PID value can/s oscilate more than -1000 and 1000 because when we
  have a value of 2000us the maximum value taht we could sybstract is 1000 and when
  we have a value of 1000us for the PWM sihnal, the maximum value that we could add is 1000
  to reach the maximum 2000us*/
  if(PID < -1100){PID = -1100;}

  if(PID > 1100){PID = 1100;}
  
  pwm_left = throttle + PID;
  pwm_right = throttle - PID;

  if(pwm_right < 1100){pwm_right = 1100;}
  
  if(pwm_right > 1600){pwm_right=1600;}

  if(pwm_left < 1100){pwm_left= 1100;}

  if(pwm_left > 1600){pwm_left=1600;}

  frontleft_motor.writeMicroseconds(pwm_left);
  backright_motor.writeMicroseconds(pwm_right);
  previous_error = error; //Remember to store the previous error.
  delay(500);
}

