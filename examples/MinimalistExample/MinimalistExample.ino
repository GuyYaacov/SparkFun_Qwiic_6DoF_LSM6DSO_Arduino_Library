/******************************************************************************
MinimalistExample.ino

Original Library written for the LSM6DS3 by Marshall Taylor @ SparkFun Electronics
Updated to modern SparkFun practices for the LSM6DS0 by Elias Santistevan @ SparkFun Electronics
March, 2021
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DS0
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DS0_Arduino_Library

Description:
Most basic example of use.

Example using the LSM6DS0 with basic settings.  This sketch collects Gyro and
Accelerometer data every second, then presents it on the serial monitor.

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

This code is released under the [MIT License](http://opensource.org/licenses/MIT).

Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFunLSM6DSO.h"
#include "Wire.h"
// #include "SPI.h"

LSM6DSO myIMU; //Default constructor is I2C, addr 0x6B
int data; 

void setup() {

  Serial.begin(115200);
  
  //Call .begin() to configure the IMU
  Wire.begin();
  if( !myIMU.begin() )
    Serial.println("Ready.");
  else { 
    Serial.println("Could not communicate with the accelerometer.");
    Serial.println("Freezing.");
    while(1);
  }

  delay(1000);
}


void loop()
{
  
  data = myIMU.getDataReady();

  
  if( (data & ACCEL_DATA_READY) == ACCEL_DATA_READY ){

    Serial.print("\nAccelerometer:\n");
    Serial.print(" X = ");
    Serial.println(myIMU.readFloatAccelX(), 4);
    Serial.print(" Y = ");
    Serial.println(myIMU.readFloatAccelY(), 4);
    Serial.print(" Z = ");
    Serial.println(myIMU.readFloatAccelZ(), 4);

  }

  if( (data & GYRO_DATA_READY) == GYRO_DATA_READY ){

    Serial.print("\nGyroscope:\n");
    Serial.print(" X = ");
    Serial.println(myIMU.readFloatGyroX(), 4);
    Serial.print(" Y = ");
    Serial.println(myIMU.readFloatGyroY(), 4);
    Serial.print(" Z = ");
    Serial.println(myIMU.readFloatGyroZ(), 4);

  }

  if( (data & TEMP_DATA_READY) ==  TEMP_DATA_READY ){

    Serial.print("\nThermometer:\n");
    Serial.print(" Degrees C = ");
    Serial.println(myIMU.readTempF(), 4);

  }
  
  delay(500); //Delay should be at least 1/ODR -> default ODR = 416 
}
