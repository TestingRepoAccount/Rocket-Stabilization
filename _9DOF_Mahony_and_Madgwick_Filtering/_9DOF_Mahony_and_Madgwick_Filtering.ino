#include<Wire.h>
#include <SPI.h>
#include <SD.h>

//#include <I2C.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_HMC5883_U.h>

const int MPU=0x68;  // I2C address of the MPU-6050
const int Mag = 0x1E;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,MgX,MgY,MgZ;
float fAcX,fAcY,fAcZ,fGyX,fGyY,fGyZ,fMgX,fMgY,fMgZ;

float lastUpdate = 0;    // used to calculate integration interval
float Now = 0;           // used to calculate integration interval
//#define OutputAccel
#define OutputGyro
//#define OutputMag
//#define OutputYawPitchRoll
//#define OutputQuat

#define GyroMeasError PI * (40.0f / 180.0f)       // gyroscope measurement error in rads/s (shown as 3 deg/s)
#define GyroMeasDrift PI * (0.0f / 180.0f)      // gyroscope measurement drift in rad/s/s (shown as 0.0 deg/s/s)
#define beta sqrt(3.0f / 4.0f) * GyroMeasError   // compute beta
#define zeta sqrt(3.0f / 4.0f) * GyroMeasDrift   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
#define Kp 2.0f * 5.0f // these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
#define Ki 0.0f
float yaw;
float pitch;
float roll;
float deltat = 0.0f;        // integration interval for both filter schemes
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
float eInt[3] = {0.0f, 0.0f, 0.0f};       // vector to hold integral error for Mahony method
/* Assign a unique ID to this sensor at the same time */
//Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup(){
  Wire.begin();
  setupSensors();
  Serial.begin(9600);
//  mag.begin();
 // Wire.beginTransmission(MPU);
//  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0);     // set to zero (wakes up the MPU-6050)
//  Wire.endTransmission(true);
}

void loop(){

readGyroAccel();
readMag();
  Now = micros();
  deltat = ((Now - lastUpdate)/1000000.0f); // set integration time by time elapsed since last filter update

//MahonyQuaternionUpdate(fAcX, fAcY, fAcZ, fGyX*PI/180.0f, fGyY*PI/180.0f, fGyZ*PI/180.0f, MgX, MgY, MgZ);
lastUpdate = micros();

#ifdef OutputAccel
Serial.print("\t");
Serial.print(fAcX);
Serial.print("\t");
Serial.print(fAcY);
Serial.print("\t");
Serial.println(fAcZ);
#endif

#ifdef OutputGyro
Serial.print("\t");
Serial.print(GyX);
Serial.print("\t");
Serial.print(GyY);
Serial.print("\t");
Serial.println(GyZ);
#endif

#ifdef OutputMag
Serial.print("\t");
Serial.print(MgX);
Serial.print("\t");
Serial.print(MgY);
Serial.print("\t");
Serial.println(MgZ);
#endif

#ifdef OutputQuat
Serial.print("\t");
Serial.print(q[0]);
Serial.print("\t");
Serial.print(q[1]);
Serial.print("\t");
Serial.print(q[2]);
Serial.print("\t");
Serial.print(q[3]);
Serial.println("\t");

#endif

#ifdef OutputYawPitchRoll
yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   
pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
pitch *= 180.0f / PI;
yaw   *= 180.0f / PI; 
yaw   -= 13.8; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
roll  *= 180.0f / PI;
Serial.print(yaw);
Serial.print("\t");
Serial.print(pitch);
Serial.print("\t");
Serial.println(roll);
#endif

//Serial.println(deltat);
//Serial.print("filter rate = "); Serial.println(1.0f/deltat, 1);
}

void setupSensors() {
/*  I2c.write(0x68, 0x6B, 0x00); //Wake Up MPU6050
  I2c.write(0x68, 0x6A, 0x00); //Set I2CMaster Bypass
  I2c.write(0x68, 0x37, 0x02); //Same as above
  */
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6A);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x37);  // PWR_MGMT_1 register
  Wire.write(0x02);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(Mag); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

 Wire.beginTransmission(MPU); //Set Acceleration to +-16g
  Wire.write(0x1C);//Register
  Wire.write(0x18);//Afs = 3
  Wire.endTransmission(); 
  
}

void readGyroAccel(){
  //Start Recieving Data
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//Offset the input data
  fAcX = AcX;
  fAcY = AcY;
  fAcZ = AcZ;
  fGyX = GyX;
  fGyY = GyY;
  fGyZ = GyZ;
  //fAcX -= 800.0f;//FYI I just found what seemed to be the best 
  //fAcZ += 1449.0f;//and got me the most stable data with the noise centered around the 0
  fGyX += 250.0f;//Your values may be different
  fGyY -= 30.0f;
  fGyZ += 40.0f;
//divide it by scaling factor as per datasheet
  fAcX /= 2048.0f;
  fAcY /= 2048.0f;
  fAcZ /= 2048.0f;
  fGyX /= 131;
  fGyY /= 131;
  fGyZ /= 131;
}


void readMag(){
/*sensors_event_t event; 
mag.getEvent(&event);

MgX = event.magnetic.x;
MgY = event.magnetic.y;
MgZ = event.magnetic.z;
*/
  Wire.beginTransmission(Mag);//Address of HMC5883L Magnetometer
  Wire.write(0x3);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(Mag,6,true);
  MgX=Wire.read()<<8|Wire.read();//read registar 3 and 4  
  MgZ=Wire.read()<<8|Wire.read();//read registar 5 and 6
  MgY=Wire.read()<<8|Wire.read();//read registar 6 and 7
  MgX *= .01;
  MgY *= .01;
  MgZ *= .01;
}



