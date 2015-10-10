#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>

// Create sensor instances.
Adafruit_LSM303_Accel_Unified accel(30301);
Adafruit_L3GD20_Unified gyro(30303);

float const PI_F = 3.14159265F;
float roll = 0.0F;

void setup()
{
  Serial.begin(115200);
  
  // Initialize the sensors.
  accel.begin();
  gyro.begin(GYRO_RANGE_2000DPS);
  
  
  //header row
  Serial.println(F("RP9 IMU Test"));
  Serial.println(F("Pitch Angle| Gyro Y DPS "));
  
}

void loop(void)
{
  sensors_event_t accel_event;
  sensors_event_t gyro_event;

  //get the events
  gyro.getEvent(&gyro_event);
  accel.getEvent(&accel_event);
  
  // roll: Rotation around the Y-axis. -180 <= roll <= 180                                          
  // a positive roll angle is defined to be a clockwise rotation about the positive Y-axis
  // this is for the specific orientation of the IMU in the balancing bot.  
  //                                                                                                
  //                    x                                                                           
  //      roll = atan2(---)                                                                         
  //                    z                                                                           
  //                                                                                                
  // where:  x, z are returned value from accelerometer sensor                                      
  roll = (float)atan2(accel_event.acceleration.x, accel_event.acceleration.z);
  //convert to degrees
  roll = roll * 180 / PI_F;
  
  //print the data row
  Serial.print(roll * -1.0F);
  Serial.print(F(" "));
  Serial.print("| "); Serial.print(gyro_event.gyro.y);   Serial.print(" ");
  Serial.println("");
   
  delay(10);
}


