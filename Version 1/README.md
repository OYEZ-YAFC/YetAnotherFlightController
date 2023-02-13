# Yet Another Flight Controller - V1


## Security and disclaimers

Drones are not toys, and thus must be handled with care. We cannot be held responsible for any arm caused by following the hereafter procedures.

This projet, version 1, is made with a custom-made quadcopter using the following components :
- a custom-made frame (see picture?where?) ;
- #motors reference ;
- #esc reference ;
- a 1200W battery (accurate?) ;
- an arduino uno(nano) card ;
- plastic propellers ;
- a MPU6050 sensor for motion tracking ;

It is not required to use the exact same components for this document to be of any help, its purpose is to demonstrate how an arduino-controlled drone can be made, and provide explanations regarding how to make it fly from scratch.


## How do drones work ?

Drones are miniature embedded-systems. In order for a drone to fly, it is necessary that it possesses the required physical and logical components. Find below a list of all these components with an explanation on what they are used for :

- Main frame: it provides a structural support for the drone and the internal components. The material used can vary from drone to drone ;

- Propeller: a device with radiating blades, with usually one affixed to each motor. Through the use of physical properties, it creates a thrust to propel the drone through the air ;

- Motor: a device that makes the propellers spin so that the drone can fly ;

- ESC (Electronic Speed Controller): a physical component dedicated to controling one or several motors. Brushless motors cannot be made to work with simple signals, they require specific impulsions to spin properly. It is through the ESC that the speed of the motors can be adjusted ;

- Power Supply : motors require a power supply to be activated. The amount of power varies based on the motors ;

- "Code": drones require a piece of software that controls what it does. This code usually contains two main elements :
  - a Flight Controller: it is the piece of software that coordinates the drone's components to allow it to fly and not immediately fall on the ground. It is often done though the use of PID controllers for drones and small embedded systems ;
  - an Autopilot: it is the piece of software that dictates what the drone does. It implements functions that renders the drone controllable. Some autopilots allow a drone to be autonomous, while others make it controllable through the use of a remote controller.


## The arming process 

For safety reasons, the motors of a drone are not active on startup. To enable them, it is necessary to *arm* them. Arming motors refers to the action of sending the correct "unlock signal" to the ESC that controls them, the value of that signal is not fixed and varies based on the ESC, but it can usually be found in the its datasheet. It is frequent to find the following states in modern drones :

- Disarmed: the drone can be powered on, but the motors are deactivated, possibly not even powered through the ESC. In this state, the motors cannot spin the propellers ;

- Pre-armed: the motors are powered on, but cannot spin yet. Only some actuators and non-dangerous electronics to allow the arming procedure to be executed ;

- Armed: the vehicle is fully powered. Motors/propellers can generate thrust (*danger*).

The arming process is a critical safety feature that helps prevent accidents and protects both the drone and its operator. Not every drones posses the intermediate pre-arm state, and while the arming process *can* be deactivated, under most circumstances it should be kept on.



## How to Arm, PreArm : 
The arming value determine under wich conditions the motors will spin. We started by replacing the propellers by cardboard pieces. 

You can usually find this information in the data sheet or manual of the motor, if not this is typically accomplished through the use of a switch or button on the drone's remote control or through software settings on the flight controller. 
  
Here are the steps we followed :

Starting by Writing the code, a loop around the range of arming values
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

We connect the flight controller, and set a timer exactly when pluging the battery. When the drone is armed, the ESC sends a signal to the motors to start spinning, and this produce a beeping sound. After the beep the motors start rotating.
   
We ran multiple tests, to finally get 84 as the arming value. This is the final code :

```cpp
motor.write(0); // disarmed drone
delay(1000);
motor.write(84);  // the armament value, the motors are now spining
delay(1000);
motor.write(0)  // we disarm the drone to safely remove the battery
```    
