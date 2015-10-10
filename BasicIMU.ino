#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Simple_AHRS.h>

// Create sensor instances.
Adafruit_LSM303_Accel_Unified accel(30301);
Adafruit_LSM303_Mag_Unified   mag(30302);
Adafruit_L3GD20_Unified gyro(30303);

// Create simple AHRS algorithm using the above sensors.
Adafruit_Simple_AHRS          ahrs(&accel, &mag);

void setup()
{
  Serial.begin(115200);
  
  // Initialize the sensors.
  accel.begin();
  mag.begin();
  gyro.begin(GYRO_RANGE_2000DPS);
  
  
  //header row
  Serial.println(F("RP9 IMU Test"));
  Serial.println(F("Pitch Angle| Gyro Y DPS "));
  
}

void loop(void)
{
  sensors_vec_t   orientation;
  sensors_event_t gyro_event;

  // Use the simple AHRS function to get the current orientation.
  if (ahrs.getOrientation(&orientation))
  {
    gyro.getEvent(&gyro_event);
    //data row
    Serial.print(orientation.roll * -1);
    Serial.print(F(" "));
    Serial.print("| "); Serial.print(gyro_event.gyro.y);   Serial.print(" ");
    Serial.println("");
  }
  
  delay(10);
}
