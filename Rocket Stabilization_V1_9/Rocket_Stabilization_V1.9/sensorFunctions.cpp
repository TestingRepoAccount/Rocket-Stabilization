
#include "sensorFunctions.h"

const int MPU = 0x68; // I2C address of the MPU-6050
const int Mag = 0x1E; //I2C address of the HMC5833L

int16_t iAcX,iAcY,iAcZ,iTmp,iGyX,iGyY,iGyZ,iMgX,iMgY,iMgZ;//int16_t values
float fAcX,fAcY,fAcZ,fGyX,fGyY,fGyZ,fMgX,fMgY,fMgZ;//float values
int GyXoff,GyYoff,GyZoff,AcXoff,AcYoff,AcZoff;
static float rawSense{9];//float values

Adafruit_BMP085 bmp;//Defines the BMP180

//Adafruit_BMP085 bmp;//Defines the BMP180
int alt;//Current Altitude





void initBMP180() //Gets Altitude Ready to go!
{
  Serial.print("Initializing BMP180");
  if (!bmp.begin())
  {
    Serial.println("BMP180 initialization failed!");
    return;
  }
  Serial.println("BMP180 initialization done.");
}

void getAlt(int altoffset)
{
  alt = bmp.readAltitude() - altoffset;
}



//Lets setup these Sensors!
void setupSensors()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x6A);  //Sets I2C_MASTER EN Register
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x37);  //Sets I2c_BYPASS EN, which enables I2c Passthrough from AUX_I2C to I2c
  Wire.write(0x02);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU); //Set Acceleration to +-16g
  Wire.write(0x1C);//Register
  Wire.write(0x18);//Afs = 3
  Wire.endTransmission(); 
  
  Wire.beginTransmission(Mag); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}




//Talks to the sensors over I2C and polls the data and returns it as a array
const float * readGyroAccel(GyXoff,GyYoff,GyZoff,AcXoff,AcYoff,AcZoff)
{
  //Start Recieving Data
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true); // request a total of 14 registers
  iAcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  iAcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  iAcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  iTmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  iGyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  iGyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  iGyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  /* This is offsetting your data, If you find your data to not be centered correctly
   *  find the offsets for your data and add or subract them here
   */
  //Change to Float
  fAcX = iAcX;
  fAcY = iAcY;
  fAcZ = iAcZ;
  fGyX = iGyX;
  fGyY = iGyY;
  fGyZ = iGyZ;

  fGyX += GyXoff //Gyro offset values
  fGyY += GyYoff;
  fGyZ += GyZoff;
  fGyX += AcXoff; //Accelerometer offset values
  fGyY -= AcYoff;
  fGyZ += AcZoff;

  /*Division by the scaling factor as per the datasheet for the MPU6050 */
  fAcX /= 2048.0f;
  fAcY /= 2048.0f;
  fAcZ /= 2048.0f;
  fGyX /= 131;
  fGyY /= 131;
  fGyZ /= 131;

  
  /*Begin Magnetometer Section */
  Wire.beginTransmission(Mag);//Address of HMC5883L Magnetometer
  Wire.write(0x3);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(Mag, 6, true);
  iMgX = Wire.read() << 8 | Wire.read(); //read registar 3 and 4
  iMgZ = Wire.read() << 8 | Wire.read(); //read registar 5 and 6
  iMgY = Wire.read() << 8 | Wire.read(); //read registar 6 and 7
  fMgX = iMgX;
  fMgY = iMgY;
  fMgZ = iMgZ;
  fMgX *= .01;
  fMgY *= .01;
  fMgZ *= .01;
  
  rawSense = {fAcX,fAcY,fAcZ,fGyX,fGyY,fGyZ,fMgX,fMgY,fMgZ};
  return rawSense;
}




