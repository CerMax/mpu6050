#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
 
  mpu.calibrateGyro();

  
  mpu.setThreshold(3);
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  timer = millis();

  Vector norm = mpu.readNormalizeGyro();
  
  pitch = pitch + norm.YAxis * timeStep;

  Serial.print(" Pitch = ");
  Serial.println(pitch);
 

  delay((timeStep*1000) - (millis() - timer));

  if(pitch > 20) {
    digitalWrite(LED_BUILTIN, HIGH); 
    Serial.print(" Pitch = ");
    Serial.println(pitch);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW); 
  }
}
