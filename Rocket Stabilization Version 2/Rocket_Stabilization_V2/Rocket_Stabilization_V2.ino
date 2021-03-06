
/*
 * Author: Jeremy Hall
 * Credits to Kris Winer at Sparkfun Electronics
 * for Mahony and Madgwick Filtering functions.
 * Uses Adafruit BMP085 library for the BMP085 or BMP180
 * (Will be replacing that in the future)
 * Credit to Caleb for buying me pizza as payment for some work
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
#include<Wire.h>
//#include <Adafruit_BMP085.h>

/* Variables for the Stabilization System
Customize them to your likings
*/
String data1,data2,data3,data4,data5;
int intdata1,intdata2,intdata3,intdata4;
int DataPosition1 = 0;
int DataPosition2 = 0; 
int DataPosition3 = 0;
int DataPosition4 = 0;
String Datain = "";
bool GNCOnline = true; //the GNC Status of the control algos
const int MPU = 0x68; // I2C address of the MPU-6050
const int Mag = 0x1E; //I2C address of the HMC5833L
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,MgX,MgY,MgZ;//int16_t values
float fAcX,fAcY,fAcZ,fGyX,fGyY,fGyZ,fMgX,fMgY,fMgZ;//float values
float yaw, pitch, roll; //Yaw, Pitch, and Roll that is used in the Stabilization
double pitchopp, pitchdiff, rollopp, rolldiff;// Mathmatical Variables used in determining Servo position.
float pitchOutput, rollOutput; //Output from the adjustment Calculation
bool aborten = false;//Abort Activation Status
int rollAngle, pitchAngle;
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
int Servo1pos = 0; //servo 1
int Servo2pos = 0;  //servo 2
int Servo3pos = 0; //servo 3
int Servo4pos = 0; //servo 4
//Adafruit_BMP085 bmp;//Defines the BMP180
int alt;//Current Altitude
int altoffset = 221;//offset for the altimetry from sea level to your current location
bool ServLock = false;
const int chipSelect = 4; //Chip Select for the SD card logging
/*Variables for the Mahony and Madgwick Filters*/
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
bool MahonyEn = true;
bool MadgwickEn = false;
/* Calibration Values */
int yawOffset = 0;
int pitchOffset = 4.0;
int rollOffset = -5.2;


void setup(){
  Wire.begin();
  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing Sensors");
//  initBMP180();
  setupSensors();
  pinMode(12, OUTPUT);
  Serial.print("Initializing SD card...");
  Servo1.attach(5);
  Servo2.attach(9);
  Servo3.attach(10);
  Servo4.attach(11);
  pinMode(12, OUTPUT);
  // see if the card is present and can be initialized:
 /* if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }*/
  Serial.println("card initialized.");
  Serial.println("Initializing Servos");

}


void loop()
{
  
while (Serial1.available() > 0) {
Datain = Serial1.readStringUntil('\n'); // read serial data into a string
Serial.println(Datain);//debugging not to worry
char DataArray[Datain.length()];// make a array the length of the datain to make life simple
Datain.toCharArray(DataArray, 50);// Make an array so we can search it
for (int i = 0; i < Datain.length(); i++){// iterate through the length of it
  if (DataArray[i] == ','){// search for a comma
    if (DataPosition1 == 0){//if this is 0 then this is the first comma
      DataPosition1 = i;//note the position of the comma
    }
    else if (DataPosition1 != 0 && DataPosition2 == 0){// if its this then its the second comma
      DataPosition2 = i;// put it as such
    }
    else if (DataPosition1 != 0 && DataPosition2 != 0 && DataPosition3 == 0){//same as others but for third
      DataPosition3 = i;//put it as such
    }
  }
}// now we are going to substring the main data string based on the position of the commas to get the variables
data1 = Datain.substring(0,DataPosition1);//take the position and get the first variable
data2 = Datain.substring(DataPosition1 + 1, DataPosition2);//get the second
data3 = Datain.substring(DataPosition2 + 1, DataPosition3);// get the third
data4 = Datain.substring(DataPosition3 + 1, DataPosition4);// get the fourth
data5 = Datain.substring(DataPosition4 + 1, Datain.length());//get the fifth
DataPosition1 = 0;
DataPosition2 = 0;
DataPosition3 = 0;
DataPosition4 = 0;

  if (data1 == "GNCON"){
    Serial1.println("GNC is ON");
    GNCOnline = true;
  }
    if (data1 == "GNCOFF"){
    Serial1.println("GNC is OFF");
    GNCOnline = false;
  }
    if (data1 == "SERVOPOS"){
    intdata1 = data2.toInt();
    intdata2 = data3.toInt();
    intdata3 = data4.toInt();
    intdata4 = data5.toInt();
    Serial1.print("Servo Position set to: ");
    Serial1.print(intdata1);
    Serial1.print(",");
    Serial1.print(intdata2);
    Serial1.print(",");
    Serial1.print(intdata3);
    Serial1.print(",");
    Serial1.println(intdata4);
    Servo1pos = intdata1;
    Servo2pos = intdata2;
    Servo3pos = intdata3;
    Servo4pos = intdata4;
  }
    if (data1 == "SERVOFFSET"){
    intdata1 = data2.toInt();
    intdata2 = data3.toInt();
    intdata3 = data4.toInt();
    intdata4 = data5.toInt();
    Serial1.print("Servo Offset is set at: ");
    Serial1.print(intdata1);
    Serial1.print(",");
    Serial1.print(intdata2);
    Serial1.print(",");
    Serial1.print(intdata3);
    Serial1.print(",");
    Serial1.println(intdata4);
    Servo1offset = intdata1;
    Servo2offset = intdata2;
    Servo3offset = intdata3;
    Servo4offset = intdata4;
  }
    if (data1 == "CAL"){
    Serial1.println("Calibrating");//Still need to make a calibration routine
  }
    if (data1 == "YPROFFSET"){
    intdata1 = data2.toInt();
    intdata2 = data3.toInt();
    intdata3 = data4.toInt();
    Serial1.print("Yaw Pitch and Roll Offset is set at: ");
    Serial1.print(intdata1);
    Serial1.print(",");
    Serial1.print(intdata2);
    Serial1.print(",");
    Serial1.println(intdata3);
    yawOffset = intdata1;
    pitchOffset = intdata2;
    rollOffset = intdata3;
  }
    if (data1 == "GNCANGLE"){
    intdata2 = data2.toInt();
    intdata3 = data3.toInt();
    Serial1.print("GNC Angle is set at: ");
    Serial1.print(intdata2);
    Serial1.print(",");
    Serial1.println(intdata3);
    pitchAngle = intdata2;
    rollAngle = intdata3;
  }
    if (data1 == "YPROUT"){
    Serial1.print("Yaw Pitch and Roll is at: ");
    Serial1.print(yaw);
    Serial1.print(",");
    Serial1.print(pitch);
    Serial1.print(",");
    Serial1.println(roll);
  }
    if (data1 == "GNCOUT"){
    Serial1.print("GNC Correction is set at: ");
    Serial1.print(pitchOutput);
    Serial1.print(",");
    Serial1.println(rollOutput);
  }
    if (data1 == "SERVLOCK"){
    Serial1.println("Servos are Locked");
    ServLock = true;
  }
    if (data1 == "SERVUNLOCK"){
    Serial1.println("Servos are Unlocked");
    ServLock = false;
  }
    if (data1 == "STAT"){
    Serial1.println("Launch Status is No Go!");
  }
    if (data1 == "ARM"){
    Serial1.println("Launch Status is No Go! Cannot Arm!");
  }
    if (data1 == "GOGO"){
    Serial1.println("Launch is disabled!");
  }
    if (data1 == "NOGO"){
    Serial1.println("Abort!");
    aborten = true;
  }
  data1 = "";
  data2 = "";
  data3 = "";
  data4 = "";
}


if (GNCOnline == true && aborten == false){
currentMillis = millis();
//Get Sensor Updates
  readGyroAccel();
  readMag();
//  getAlt();
//DeltaTime Data for the filtering
  Now = micros();
  deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
//Filter Enables
  if (MahonyEn == true){
    MahonyUpdate();
  }
  if (MadgwickEn == true){
    MadgwickUpdate();
  }
  ComputePitch();
  ComputeRoll();  
}

if (aborten == true){
  Abort();
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
  Serial.println(GNCOnline);
#endif
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


/*void initBMP180() //Gets Altitude Ready to go!
{
  Serial.print("Initializing BMP180");
  if (!bmp.begin())
  {
    Serial.println("BMP180 initialization failed!");
    return;
  }
  Serial.println("BMP180 initialization done.");
}
*/
void readGyroAccel()
{
  //Start Recieving Data
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  /* This is offsetting your data, If you find your data to not be centered correctly
   *  find the offsets for your data and add or subract them here
   */
  //Change to Float
  fAcX = AcX;
  fAcY = AcY;
  fAcZ = AcZ;
  fGyX = GyX;
  fGyY = GyY;
  fGyZ = GyZ;
  
  fGyX += 250.0f; //Gyro Offset Values
  fGyY -= 32.0f;
  fGyZ += 39.0f;
  /*Division by the scaling factor as per the datasheet for the MPU6050 */
  fAcX /= 2048.0f;
  fAcY /= 2048.0f;
  fAcZ /= 2048.0f;
  fGyX /= 131;
  fGyY /= 131;
  fGyZ /= 131;
}

void readMag()
{
  Wire.beginTransmission(Mag);//Address of HMC5883L Magnetometer
  Wire.write(0x3);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(Mag, 6, true);
  MgX = Wire.read() << 8 | Wire.read(); //read registar 3 and 4
  MgZ = Wire.read() << 8 | Wire.read(); //read registar 5 and 6
  MgY = Wire.read() << 8 | Wire.read(); //read registar 6 and 7
  fMgX = MgX;
  fMgY = MgY;
  fMgZ = MgZ;
  fMgX *= .01;
  fMgY *= .01;
  fMgZ *= .01;
}

/*void getAlt()
{
  alt = bmp.readAltitude() - altoffset;
}
*/
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
  Servo2pos = pitchopp;
  Servo4pos = pitchOutput;
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
  Servo1pos = rollopp;
  Servo3pos = rollOutput;
}

void Abort(){
  Serial.print("ABORT!");
  Servo1.write(90 + Servo1offset);//Servo 1
  Servo2.write(90 + Servo2offset);//Servo 2
  Servo3.write(90 + Servo3offset);//Servo 3
  Servo4.write(90 + Servo4offset);//Servo 4
  digitalWrite(12, HIGH);
}
void writeServos(){
  if(aborten == false && ServLock == false){
  Servo1.write(Servo1pos + Servo1offset);//Servo 1
  Servo2.write(Servo2pos + Servo2offset);//Servo 2
  Servo3.write(Servo3pos + Servo3offset);//Servo 3
  Servo4.write(Servo4pos + Servo4offset);//Servo 4
  }
}
void MahonyUpdate(){
  MahonyQuaternionUpdate(fAcX, fAcY, fAcZ, fGyX * PI / 180.0f, fGyY * PI / 180.0f, fGyZ * PI / 180.0f, fMgX, fMgY, fMgZ);
  lastUpdate = micros();
// Conversion to Yaw, Pitch, and Roll
  yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   //convert to yaw, pitch and roll
  pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
  roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
  pitch *= 180.0f / PI;
  yaw   *= 180.0f / PI;
  roll  *= 180.0f / PI;
  pitch += pitchOffset;
  roll += rollOffset;
  //Check if abort has been called
}

void MadgwickUpdate(){
  MadgwickQuaternionUpdate(fAcX, fAcY, fAcZ, fGyX*PI/180.0f, fGyY*PI/180.0f, fGyZ*PI/180.0f, fMgX, fMgY, fMgZ);
  lastUpdate = micros();
// Conversion to Yaw, Pitch, and Roll
  yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   //convert to yaw, pitch and roll
  pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
  roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
  pitch *= 180.0f / PI;
  yaw   *= 180.0f / PI;
  roll  *= 180.0f / PI;
  pitch += pitchOffset;
  roll += rollOffset;
  //Check if abort has been called
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
  norm = 1.0f / norm;
  ax *= norm;
  ay *= norm;
  az *= norm;

  // Normalise magnetometer measurement
  norm = sqrt(mx * mx + my * my + mz * mz);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;
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
  norm = 1.0f / norm;
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
  norm = 1.0f / norm;
  q[0] = q1 * norm;
  q[1] = q2 * norm;
  q[2] = q3 * norm;
  q[3] = q4 * norm;

}

