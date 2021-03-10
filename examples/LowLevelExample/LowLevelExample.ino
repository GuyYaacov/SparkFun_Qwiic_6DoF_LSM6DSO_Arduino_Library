/******************************************************************************
LowLevelExample.ino

Original Library written for the LSM6DS3 by Marshall Taylor @ SparkFun Electronics
Updated to modern SparkFun practices for the LSM6DS0 by Elias Santistevan @ SparkFun Electronics
March, 2021
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DS0
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DS0_Arduino_Library

Description:
Example using the LSM6DS0 with ONLY read and write methods.  It's up to you to
read the datasheets and get the sensor to behave as you will.

This sketch saves a significant amount of memory because the settings and complex
math (such as floating point variables) don't exist.  The cost of saved memory is
that the values are in 'counts', or raw data from the register.  The user is
responsible for converting these raw values into something meaningful.

Use the register words from SparkFunLSM6DS0.h to manually configure the IC.

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

This code is released under the [MIT License](http://opensource.org/licenses/MIT).

Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFunLSM6DS0.h"
#include "Wire.h"
//#include "SPI.h"

uint16_t errorsAndWarnings = 0;

LSM6DS0Core myIMU( I2C_MODE, 0x6B );
//LSM6DS0Core myIMU( SPI_MODE, 10 );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");
  
  Wire.begin();
  //Call .beginCore() to configure the IMU
  if( myIMU.beginCore() != 0 )
  {
    Serial.print("Error at beginCore().\n");
  }
  else
  {
    Serial.print("\nbeginCore() passed.\n");
  }
  
  uint8_t dataToWrite = 0;  //Temporary variable

  //Setup the accelerometer******************************
  dataToWrite = 0; //Start Fresh!
  dataToWrite |= LSM6DS0_ACC_GYRO_BW_XL_100Hz;
  dataToWrite |= LSM6DS0_ACC_GYRO_FS_XL_8g;
  dataToWrite |= LSM6DS0_ACC_GYRO_ODR_XL_104Hz;

  //Now, write the patched together data
  errorsAndWarnings += myIMU.writeRegister(LSM6DS0_ACC_GYRO_CTRL1_XL, dataToWrite);

  //Set the ODR bit
  errorsAndWarnings += myIMU.readRegister(&dataToWrite, LSM6DS0_ACC_GYRO_CTRL4_C);
  dataToWrite &= ~((uint8_t)LSM6DS0_ACC_GYRO_BW_SCAL_ODR_ENABLED);

}


void loop()
{
  int16_t temp;
  //Get all parameters
  Serial.print("\nAccelerometer Counts:\n");
  Serial.print(" X = ");
  
  //Read a register into the temp variable.
  if( myIMU.readRegisterInt16(&temp, LSM6DS0_ACC_GYRO_OUTX_L_XL) != 0 )
  {
    errorsAndWarnings++;
  }
  Serial.println(temp);
  Serial.print(" Y = ");

  //Read a register into the temp variable.
  if( myIMU.readRegisterInt16(&temp, LSM6DS0_ACC_GYRO_OUTY_L_XL) != 0 )
  {
    errorsAndWarnings++;
  }
  Serial.println(temp);
  Serial.print(" Z = ");

  //Read a register into the temp variable.
  if( myIMU.readRegisterInt16(&temp, LSM6DS0_ACC_GYRO_OUTZ_L_XL) != 0 )
  {
    errorsAndWarnings++;
  }
  Serial.println(temp);
  
  Serial.println();
  Serial.print("Total reported Errors and Warnings: ");
  Serial.println(errorsAndWarnings);
  
  delay(1000);
}
