#include <SD.h>
#include <SPI.h>
/*
 * Author: Jeremy Hall
 * Credit to Kris Winer at Sparkfun Electronics
 * for Mahony and Madgwick Filtering functions.
 * Uses Adafruit BMP085 library for the BMP085 or BMP180
 * (Will be replacing that in the future)
 */
#include <Servo.h>
#include<Wire.h>
#include <Adafruit_BMP085.h>
//#include <I2C.h>

//#define OutputAccel
//#define OutputGyro
//#define OutputMag
//#define OutputQuat
#define OutputYawPitchRoll
//#define OutputAltitude
//#define OutputCalibration


#define GyroMeasError PI * (40.0f / 180.0f)       // gyroscope measurement error in rads/s (shown as 3 deg/s)
#define GyroMeasDrift PI * (0.0f / 180.0f)      // gyroscope measurement drift in rad/s/s (shown as 0.0 deg/s/s)
#define beta sqrt(3.0f / 4.0f) * GyroMeasError   // compute beta
#define zeta sqrt(3.0f / 4.0f) * GyroMeasDrift   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
#define Kp 2.0f * 5.0f // these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
#define Ki 0.0f

float lastUpdate = 0;    // used to calculate integration interval
float Now = 0;           // used to calculate integration interval
float deltat = 0.0f;        // integration interval for both filter schemes
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
float eInt[3] = {0.0f, 0.0f, 0.0f};       // vector to hold integral error for Mahony method


const int MPU=0x68;  // I2C address of the MPU-6050
const int Mag = 0x1E; //I2C address of the HMC5833L
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,MgX,MgY,MgZ; //Raw Data
float yaw, pitch, roll;
double pitchopp, pitchdiff, rollopp, rolldiff;// Variabls for finding oppisite values based on the current position

int rolloffset = -8; //servo 1
int pitchoffset = 8;  //servo 2
int rolloffset1 = 5; //servo 3
int pitchoffset1 = 0; //servo 4
Servo pitchserv, pitchserv1, rollserv, rollserv1;
float pitchOutput, rollOutput;

Adafruit_BMP085 bmp;
int alt;
int altoffset = 221;//offset
const int chipSelect = 4;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  setupSensors();
  initBMP180();
  initSD();
  rollserv.attach(3);//Servo 1
  pitchserv.attach(5);// Servo 2
  rollserv1.attach(6);// Servo 3
  pitchserv1.attach(9);// Servo 4
  
}

void loop(){
//Get Sensor Updates
readGyroAccel();
readMag();
alt = bmp.readAltitude() - altoffset;

//Get Time Data then use a Mahony Filter
Now = micros();
deltat = ((Now - lastUpdate)/1000000.0f); // set integration time by time elapsed since last filter update
MahonyQuaternionUpdate(AcX, AcY, AcZ, GyX*PI/180.0f, GyY*PI/180.0f, GyZ*PI/180.0f, MgX, MgY, MgZ);
//MadgwickQuaternionUpdate(AcX, AcY, AcZ, GyX*PI/180.0f, GyY*PI/180.0f, GyZ*PI/180.0f, MgX, MgY, MgZ);
lastUpdate = micros();

yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   //convert to yaw, pitch and roll
pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
pitch *= 180.0f / PI;
yaw   *= 180.0f / PI; 
roll  *= 180.0f / PI;
// After Converting to Yaw, Pitch and Roll compute what is needed to control the rocket
ComputePitch();
ComputeRoll();
dataLog();

#ifdef OutputAccel
Serial.print("\t");
Serial.print(AcX);
Serial.print("\t");
Serial.print(AcY);
Serial.print("\t");
Serial.println(AcZ);
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
Serial.print(yaw);
Serial.print("\t");
Serial.print(pitch);
Serial.print("\t");
Serial.println(roll);
#endif

#ifdef OutputAltitude
Serial.println(alt);
#endif

#ifdef OutputCalibration
Serial.print(pitch);
Serial.print("\t");
Serial.print(roll);
Serial.print("\t");
Serial.print(pitchOutput);
Serial.print("\t");
Serial.println(rollOutput);
#endif


//Serial.print(deltat);
//Serial.println("filter rate = "); Serial.println(1.0f/deltat, 1);
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
  Wire.write(0x6A);  //Set Half of what is needed for I2CMaster Bypass
  Wire.write(0);     
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x37);  //Set last part of I2CMaster Bypass
  Wire.write(0x02);     
  Wire.endTransmission(true);

  Wire.beginTransmission(Mag); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void ComputeRoll(){
rollOutput = map(roll, -30, 30, 70, 110);
/*calculate oppisite angle for the opp servo*/
rolldiff = 90 - rollOutput;
rollopp = 90 + rolldiff;
rollserv.write(rollOutput + rolloffset);//Servo 1
rollserv1.write(rollopp + rolloffset1);//Servo 4
}

void ComputePitch(){

pitchOutput = map(pitch, -30, 30, 70, 110);
/*calculate oppisite angle for the opp servo*/
pitchdiff = 90 - pitchOutput;
pitchopp = 90 + pitchdiff;
pitchserv.write(pitchOutput + pitchoffset);//Original Servo
pitchserv1.write(pitchopp + pitchoffset1);//Op. Servo

}

void initSD(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");
}

void initBMP180(){
  Serial.print("Initializing BMP180");
    if (!bmp.begin()) {
    Serial.println("BMP180 initialization failed!");
    return;
  }
  Serial.println("BMP180 initialization done.");
}

void dataLog(){

  File telemetry = SD.open("datalog.txt", FILE_WRITE);
  if (telemetry){
    telemetry.print(AcX);
    telemetry.print("\t");
    telemetry.print(AcY);
    telemetry.print("\t");
    telemetry.print(AcZ);
    telemetry.print("\t");
    telemetry.print(GyX);
    telemetry.print("\t");
    telemetry.print(GyY);
    telemetry.print("\t");
    telemetry.print(GyZ);
    telemetry.print("\t");
    telemetry.print(MgX);
    telemetry.print("\t");
    telemetry.print(MgY);
    telemetry.print("\t");
    telemetry.print(MgZ);
    telemetry.print("\t");
    telemetry.print(q[0]);
    telemetry.print("\t");
    telemetry.print(q[1]);
    telemetry.print("\t");
    telemetry.print(q[2]);
    telemetry.print("\t");
    telemetry.print(q[3]);
    telemetry.print("\t");
    telemetry.print(yaw);
    telemetry.print("\t");
    telemetry.print(pitch);
    telemetry.print("\t");
    telemetry.print(roll);
    telemetry.print("\t");
    telemetry.println(alt);
    telemetry.close();
  }
 else {
    Serial.println("error opening datalog.txt");
  }

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
/* This is offsetting your data, If you find your data to not be centered correctly
 *  find the offsets for your data and add or subract them here 
 */
  AcX -= 800.0f;//FYI I just found what seemed to be the best 
  AcZ += 1449.0f;//and got me the most stable data with the noise centered around the 0
  GyX += 250.0f;//Your values may be different
  GyY -= 30.0f;
  GyZ += 40.0f;
/*Division by the scaling factor as per the datasheet for the MPU6050 */
  AcX /= 16384.0f;
  AcY /= 16384.0f;
  AcZ /= 16384.0f;
  GyX /= 131.0f;
  GyY /= 131.0f;
  GyZ /= 131.0f;
}


void readMag(){
  Wire.beginTransmission(Mag);//Address of HMC5883L Magnetometer
  Wire.write(0x3);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(Mag,6,true);
  MgX=Wire.read()<<8|Wire.read();//read registar 3 and 4  
  MgZ=Wire.read()<<8|Wire.read();//read registar 5 and 6
  MgY=Wire.read()<<8|Wire.read();//read registar 6 and 7
  MgX *= .01f;
  MgY *= .01f;
  MgZ *= .01f;
}

void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
   {
            float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
            float norm;
            float hx, hy, bx, bz;
            float vx, vy, vz, wx, wy, wz;
            float ex, ey, ez;
            float pa, pb, pc;

            // Auxiliary variables to avoid repeated arithmetic
            float q1q1 = q1 * q1;
            float q1q2 = q1 * q2;
            float q1q3 = q1 * q3;
            float q1q4 = q1 * q4;
            float q2q2 = q2 * q2;
            float q2q3 = q2 * q3;
            float q2q4 = q2 * q4;
            float q3q3 = q3 * q3;
            float q3q4 = q3 * q4;
            float q4q4 = q4 * q4;   

            // Normalise accelerometer measurement
            norm = sqrt(ax * ax + ay * ay + az * az);
            if (norm == 0.0f) return; // handle NaN
            norm = 1.0f / norm;        // use reciprocal for division
            ax *= norm;
            ay *= norm;
            az *= norm;

            // Normalise magnetometer measurement
            norm = sqrt(mx * mx + my * my + mz * mz);
            if (norm == 0.0f) return; // handle NaN
            norm = 1.0f / norm;        // use reciprocal for division
            mx *= norm;
            my *= norm;
            mz *= norm;

            // Reference direction of Earth's magnetic field
            hx = 2.0f * mx * (0.5f - q3q3 - q4q4) + 2.0f * my * (q2q3 - q1q4) + 2.0f * mz * (q2q4 + q1q3);
            hy = 2.0f * mx * (q2q3 + q1q4) + 2.0f * my * (0.5f - q2q2 - q4q4) + 2.0f * mz * (q3q4 - q1q2);
            bx = sqrt((hx * hx) + (hy * hy));
            bz = 2.0f * mx * (q2q4 - q1q3) + 2.0f * my * (q3q4 + q1q2) + 2.0f * mz * (0.5f - q2q2 - q3q3);

            // Estimated direction of gravity and magnetic field
            vx = 2.0f * (q2q4 - q1q3);
            vy = 2.0f * (q1q2 + q3q4);
            vz = q1q1 - q2q2 - q3q3 + q4q4;
            wx = 2.0f * bx * (0.5f - q3q3 - q4q4) + 2.0f * bz * (q2q4 - q1q3);
            wy = 2.0f * bx * (q2q3 - q1q4) + 2.0f * bz * (q1q2 + q3q4);
            wz = 2.0f * bx * (q1q3 + q2q4) + 2.0f * bz * (0.5f - q2q2 - q3q3);  

            // Error is cross product between estimated direction and measured direction of gravity
            ex = (ay * vz - az * vy) + (my * wz - mz * wy);
            ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
            ez = (ax * vy - ay * vx) + (mx * wy - my * wx);
            if (Ki > 0.0f)
            {
                eInt[0] += ex;      // accumulate integral error
                eInt[1] += ey;
                eInt[2] += ez;
            }
            else
            {
                eInt[0] = 0.0f;     // prevent integral wind up
                eInt[1] = 0.0f;
                eInt[2] = 0.0f;
            }

            // Apply feedback terms
            gx = gx + Kp * ex + Ki * eInt[0];
            gy = gy + Kp * ey + Ki * eInt[1];
            gz = gz + Kp * ez + Ki * eInt[2];

            // Integrate rate of change of quaternion
            pa = q2;
            pb = q3;
            pc = q4;
            q1 = q1 + (-q2 * gx - q3 * gy - q4 * gz) * (0.5f * deltat);
            q2 = pa + (q1 * gx + pb * gz - pc * gy) * (0.5f * deltat);
            q3 = pb + (q1 * gy - pa * gz + pc * gx) * (0.5f * deltat);
            q4 = pc + (q1 * gz + pa * gy - pb * gx) * (0.5f * deltat);

            // Normalise quaternion
            norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);
            norm = 1.0f / norm;
            q[0] = q1 * norm;
            q[1] = q2 * norm;
            q[2] = q3 * norm;
            q[3] = q4 * norm;
 
}

void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
        {
            float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
            float norm;
            float hx, hy, _2bx, _2bz;
            float s1, s2, s3, s4;
            float qDot1, qDot2, qDot3, qDot4;

            // Auxiliary variables to avoid repeated arithmetic
            float _2q1mx;
            float _2q1my;
            float _2q1mz;
            float _2q2mx;
            float _4bx;
            float _4bz;
            float _2q1 = 2.0f * q1;
            float _2q2 = 2.0f * q2;
            float _2q3 = 2.0f * q3;
            float _2q4 = 2.0f * q4;
            float _2q1q3 = 2.0f * q1 * q3;
            float _2q3q4 = 2.0f * q3 * q4;
            float q1q1 = q1 * q1;
            float q1q2 = q1 * q2;
            float q1q3 = q1 * q3;
            float q1q4 = q1 * q4;
            float q2q2 = q2 * q2;
            float q2q3 = q2 * q3;
            float q2q4 = q2 * q4;
            float q3q3 = q3 * q3;
            float q3q4 = q3 * q4;
            float q4q4 = q4 * q4;

            // Normalise accelerometer measurement
            norm = sqrt(ax * ax + ay * ay + az * az);
            if (norm == 0.0f) return; // handle NaN
            norm = 1.0f/norm;
            ax *= norm;
            ay *= norm;
            az *= norm;

            // Normalise magnetometer measurement
            norm = sqrt(mx * mx + my * my + mz * mz);
            if (norm == 0.0f) return; // handle NaN
            norm = 1.0f/norm;
            mx *= norm;
            my *= norm;
            mz *= norm;

            // Reference direction of Earth's magnetic field
            _2q1mx = 2.0f * q1 * mx;
            _2q1my = 2.0f * q1 * my;
            _2q1mz = 2.0f * q1 * mz;
            _2q2mx = 2.0f * q2 * mx;
            hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
            hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
            _2bx = sqrt(hx * hx + hy * hy);
            _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
            _4bx = 2.0f * _2bx;
            _4bz = 2.0f * _2bz;

            // Gradient decent algorithm corrective step
            s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
            norm = 1.0f/norm;
            s1 *= norm;
            s2 *= norm;
            s3 *= norm;
            s4 *= norm;

            // Compute rate of change of quaternion
            qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
            qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
            qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
            qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

            // Integrate to yield quaternion
            q1 += qDot1 * deltat;
            q2 += qDot2 * deltat;
            q3 += qDot3 * deltat;
            q4 += qDot4 * deltat;
            norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
            norm = 1.0f/norm;
            q[0] = q1 * norm;
            q[1] = q2 * norm;
            q[2] = q3 * norm;
            q[3] = q4 * norm;

        }
