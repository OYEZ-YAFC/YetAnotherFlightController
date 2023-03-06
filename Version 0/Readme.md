# YetAnotherFlightController

## Project Version 0

Investigating the current "drone universe". This file's purpose is to give some details as to what the current "Version 0" folder contains.

#### ./MPU6050_DMP6/

This folder contains a .ino file found on the internet that works together with the MPUTeapot processing file found in the next folder.
This programs reads the data from the MPU captor and sends it via serial to the processing application.

#### ./MPUTeapot/

This folder contains a .pde file found on the internet that works together with the MPU Arduino file found in the previous folder.
The application receives data from the above program through serial and displays a visual representation of the current position of the aircraft based on the captor.

#### ./adjusting_motor_speed/

This folder contains a .ino file of the same name that served as the first test for the 2nd sensor (the MPU6050) that we were given.

#### ./icm20649_test/

This folder contains a .ino file of the same name that served as the first test for the 1st sensor (the ICM20649) that we were given.
