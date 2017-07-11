/*
 * Author: Jeremy Hall
 * Credits to Kris Winer at Sparkfun Electronics
 * for Mahony and Madgwick Filtering functions.
 * Uses Adafruit BMP085 library for the BMP085 or BMP180
 * (Will be replacing that in the future)
 */

/*Quick Info:
Servos are on the following pins
Servo1: D3
Servo2: D5
Servo3: D6
Servo4: D9
You can easily change these pins in the setup function
*/
#include <SD.h>
#include <SPI.h>
#include <Servo.h>
#include <Adafruit_BMP085.h>
#include "quaternionFilters.h"
#include "sensorFunctions.h"
#include "guidanceFunctions.h"
/* Variables for the Stabilization System
Customize them to your likings
*/
float GyXoff,GyYoff,GyZoff,AcXoff,AcYoff,AcZoff;
const int MPU = 0x68; // I2C address of the MPU-6050
const int Mag = 0x1E; //I2C address of the HMC5833L
float yaw, pitch, roll; //Yaw, Pitch, and Roll that is used in the Stabilization
double pitchopp, pitchdiff, rollopp, rolldiff;// Mathmatical Variables used in determining Servo position.
float pitchOutput, rollOutput; //Output from the adjustment Calculation
int aborten = 0;//Abort Activation Status 0 == off 1 == On
float rawSensor[9];
//File telemetry;
/* Servos are as follows:
Servo 1: Pitch Servo 1
Servo 2: Roll Servo 1
Servo 3: Pitch Servo 2 (Oppisite Side)
Servo 4: Roll Servo 2 (Oppisite Side)
*/
Servo Servo1, Servo2, Servo3, Servo4;
int Servo1offset = 0; //servo 1
int Servo2offset = 7;  //servo 2
int Servo3offset = 0; //servo 3
int Servo4offset = 7; //servo 4
/*
//Adafruit_BMP085 bmp;//Defines the BMP180
int alt;//Current Altitude
*/ 
int altoffset = 221;//offset for the altimetry from sea level to your current location

const int chipSelect = 4; //Chip Select for the SD card logging
/*Variables for the Mahony and Madgwick Filters*/
float lastUpdate = 0;    // used to calculate integration interval
float Now = 0;           // used to calculate integration interval
float deltat = 0.0f;        // integration interval for both filter schemes
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
unsigned long currentMillis;
/*Variables are now setup and ready to go */

/*Define the Debugging Outputs
The Debugging Outputs are as follows
OutputRawAccel: Outputs Raw Accelerometer Data
OutputRawGyro: Output the Raw Gyro data
OutputRawMag: Output Raw Magnetometer Data
OutputFiltQuat: Output Filtered Quaternion Data
Output FiltYawPitchRoll: Output Filtered Yaw Pitch and Roll Data
*/
//#define OutputRawAccel
//#define OutputRawGyro
//#define OutputRawMag
//#define OutputFiltQuat
#define OutputFiltYawPitchRoll
//#define OutputAltitude
//#define OutputCalibration

//Enable Datalogging
//#define Datalog

//Define FIltering Paradigm
//#define Madgwick
#define Mahony
/* Calibration Values */
float PitchOffset = 4.0f;
float RollOffset = -5.2f;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  //while (!Serial) {
 //   ; // wait for serial port to connect. Needed for native USB port only
 // }

  Serial.print("Initializing Sensors");
  initBMP180();
  setupSensors();

  Serial.print("Initializing SD card...");
  Servo1.attach(5);
  Servo2.attach(9);
  Servo3.attach(10);
  Servo4.attach(11);
  pinMode(12, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  Serial.println("Initializing Servos");

}


void loop()
{
currentMillis = millis();
//Get Sensor Updates
readSense(0,0,0,0,0,0);
  AcX = iAcX;
  AcY = iAcY;
  AcZ = iAcZ;
  GyX = iGyX;
  GyY = iGyY;
  GyZ = iGyZ;
  MgX = iMgX;
  MgY = iMgY;
  MgZ = iMgZ;
  
//getAlt(altoffset);

//DeltaTime Data for the filtering
  Now = micros();
  deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
//Filter Enables
#ifdef Mahony
  MahonyQuaternionUpdate(fAcX, fAcY, fAcZ, fGyX * PI / 180.0f, fGyY * PI / 180.0f, fGyZ * PI / 180.0f, fMgX, fMgY, fMgZ, deltat);
#endif
#ifdef Madgwick
  MadgwickQuaternionUpdate(fAcX, fAcY, fAcZ, fGyX*PI/180.0f, fGyY*PI/180.0f, fGyZ*PI/180.0f, fMgX, fMgY, fMgZ, deltat);
#endif
   q[0] = *getQ();
   q[1] = (*(getQ()+1));
   q[2] = (*(getQ()+2));
   q[3] = (*(getQ()+3));
  lastUpdate = micros();
// Conversion to Yaw, Pitch, and Roll
   yaw = *getYPR();
   pitch = (*(getYPR()+1));
   roll = (*(getYPR()+2));
  pitch += PitchOffset;
  roll += RollOffset;
  //Check if abort has been called
if (aborten == 1){
    abort();
  }
if(aborten == 0){
  ComputePitch();
  ComputeRoll();  
  }
#ifdef Datalog
File dataFile = SD.open("datalog.txt", FILE_WRITE);
if (dataFile){
    dataFile.print(AcX);
    dataFile.print("\t");
    dataFile.print(AcY);
    dataFile.print("\t");
    dataFile.print(AcZ);
    dataFile.print("\t");
    dataFile.print(GyX);
    dataFile.print("\t");
    dataFile.print(GyY);
    dataFile.print("\t");
    dataFile.print(GyZ);
    dataFile.print("\t");
    dataFile.print(MgX);
    dataFile.print("\t");
    dataFile.print(MgY);
    dataFile.print("\t");
    dataFile.print(MgZ);
    dataFile.print("\t");
    dataFile.print(q[0]);
    dataFile.print("\t");
    dataFile.print(q[1]);
    dataFile.print("\t");
    dataFile.print(q[2]);
    dataFile.print("\t");
    dataFile.print(q[3]);
    dataFile.print("\t");
    dataFile.print(yaw);
    dataFile.print("\t");
    dataFile.print(pitch);
    dataFile.print("\t");
    dataFile.print(roll);
    dataFile.print("\t");
    dataFile.print(alt);
    dataFile.print("\t");
    dataFile.println(currentMillis);
    dataFile.close();
  }
 else {
    Serial.println("error opening datalog.txt");
  }
#endif

// The following Lines are for Debugging Functions
#ifdef OutputRawAccel
  Serial.print("\t");
  Serial.print(AcX);
  Serial.print("\t");
  Serial.print(AcY);
  Serial.print("\t");
  Serial.println(AcZ);
#endif

#ifdef OutputRawGyro
  Serial.print("\t");
  Serial.print(GyX);
  Serial.print("\t");
  Serial.print(GyY);
  Serial.print("\t");
  Serial.println(GyZ);
#endif

#ifdef OutputRawMag
  Serial.print("\t");
  Serial.print(MgX);
  Serial.print("\t");
  Serial.print(MgY);
  Serial.print("\t");
  Serial.println(MgZ);
#endif

#ifdef OutputFiltQuat
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

#ifdef OutputFiltYawPitchRoll
  Serial.print(yaw);
  Serial.print("\t");
  Serial.print(pitch);
  Serial.print("\t");
  Serial.println(roll);
#endif

#ifdef OutputAltitude
  Serial.println(alt);
#endif

//Output Calibration is only needed for Calibration of the control function
//Rarely ever needed

#ifdef OutputCalibration
  Serial.print(pitch);
  Serial.print("\t");
  Serial.print(roll);
  Serial.print("\t");
  Serial.print(pitchOutput);
  Serial.print("\t");
  Serial.print(rollOutput);
  Serial.print("\t");
  Serial.println(currentMillis);
#endif

}


void ComputePitch()
{
  pitchOutput = map(pitch, -30, 30, 70, 110);
if (pitchOutput < 70 && pitchOutput > 50){
  pitchOutput = 70;
}
if (pitchOutput > 110 && pitchOutput < 130){
  pitchOutput = 110;
}

if(pitch < -50 && currentMillis > 8000 || pitch > 50 && currentMillis > 5000){
 aborten = 1;
}

  /*calculate oppisite angle for the opp servo*/
  pitchdiff = 90 - pitchOutput;
  pitchopp = 90 + pitchdiff;
//Write to the servos
  Servo2.write(pitchopp + Servo2offset);
  Servo4.write(pitchOutput + Servo4offset);
}

void ComputeRoll()
{

rollOutput = map(roll, -30, 30, 70, 110);
if (rollOutput < 70 && rollOutput > 50){
  rollOutput = 70;
}
if (rollOutput > 110 && rollOutput < 130){
  rollOutput = 110;
}
if(roll < -50 && currentMillis > 8000 || roll > 50 && currentMillis > 5000){
 aborten = 1;
}


  /*calculate oppisite angle for the opp servo*/
  rolldiff = 90 - rollOutput;
  rollopp = 90 + rolldiff;
//Write to the Serovs
  Servo1.write(rollopp + Servo1offset);
  Servo3.write(rollOutput + Servo3offset);
}

void abort(){
  Serial.print("ABORT!");
  Servo1.write(90 + Servo1offset);//Servo 1
  Servo2.write(90 + Servo2offset);//Servo 2
  Servo3.write(90 + Servo3offset);//Servo 3
  Servo4.write(90 + Servo4offset);//Servo 4
  digitalWrite(12, HIGH);
}

#ifdef Datalog
File dataFile = SD.open("datalog.txt", FILE_WRITE);
if (dataFile){
    dataFile.print(AcX);
    dataFile.print("\t");
    dataFile.print(AcY);
    dataFile.print("\t");
    dataFile.print(AcZ);
    dataFile.print("\t");
    dataFile.print(GyX);
    dataFile.print("\t");
    dataFile.print(GyY);
    dataFile.print("\t");
    dataFile.print(GyZ);
    dataFile.print("\t");
    dataFile.print(MgX);
    dataFile.print("\t");
    dataFile.print(MgY);
    dataFile.print("\t");
    dataFile.print(MgZ);
    dataFile.print("\t");
    dataFile.print(q[0]);
    dataFile.print("\t");
    dataFile.print(q[1]);
    dataFile.print("\t");
    dataFile.print(q[2]);
    dataFile.print("\t");
    dataFile.print(q[3]);
    dataFile.print("\t");
    dataFile.print(yaw);
    dataFile.print("\t");
    dataFile.print(pitch);
    dataFile.print("\t");
    dataFile.print(roll);
    dataFile.print("\t");
    dataFile.print(alt);
    dataFile.print("\t");
    dataFile.println(currentMillis);
    dataFile.close();
  }
 else {
    Serial.println("error opening datalog.txt");
  }
#endif


