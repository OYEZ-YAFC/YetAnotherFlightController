# Yet Another Flight Controller
## Drone components : 
Our quadcopter/drone is made up of several componants : 
  - The frame, provides a structural support for the drone and the internal components.
  - Four motors, to spin the propellers of the drone to enable them to fly. 
  - Four propellers for each motor, device with radiating blades.
  - Flight Controller made from an Arduino Uno.
  - One Esc (Electronic speed controllers), controls and adjusts the speed of the motors.
 
## Controlling drone motors :
 ###  "ARM" Configuration :
 Modern quadcopters and other multirotors are equipped with an "Arm" feature to reduce the chance of accidents, by default :
- Disarmed: the drone is in a deactivated, in which the motors will not spin the propellers, there is no power.
- Pre-armed: Motors/propellers are locked but actuators for non-dangerous electronics are powered (e.g. ailerons, flaps etc.).
- Armed: Vehicle is fully powered. Motors/propellers may be turning (dangerous!)
 This is a critical safety feature that helps prevent accidents and protects both the drone and its operator.

 ### How to Arm, PreArm : 
  The arming value determine under wich conditions the motors will spin. We started by replacing the propellers by cardboard pieces. 
  You can usually find this information in the data sheet or manual of the motor, if not this is typically accomplished through the use of a switch or button on the drone's remote control or through software settings on the flight controller. 
  
  Here are the steps we followed :
  - Writing the code ( look for #####filename in Version 1 )
  ```cpp
  for(int i = 51; i < 130; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    esc.write(i);
    Serial.println(i);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off 
    delay(500);
  }
  ```
   We start by setting a timer exactly when we plug the battery, and When the drone is armed, the ESC sends a signal to the motors to start spinning, and this produce a beep. After the beep the motors start rotating.
   
   We tested the values multiple times, to finally get 84 as the arming value. This is the final code :
   ```cpp
    motor.write(0); // disarmed drone
    delay(1000);
    motor.write(84);  // the armament value, the motors are now spining
    delay(1000);
    motor.write(0)  // we disarm the drone to safely remove the battery
    
