/**
   @file RAK12014_Distance_Detection.ino
   @author rakwireless.com
   @brief Distance detection by laser
   @version 0.1
   @date 2021-8-28
   @copyright Copyright (c) 2020
**/


#include <Wire.h>
#include <vl53l0x_class.h>      // Click to install library: http://librarymanager/All#stm32duino_vl53l0x
VL53L0X sensorB_vl53l0x(&Wire, WB_IO2); 
VL53L0X sensorC_vl53l0x(&Wire, WB_IO4); 


void setup() {
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  
  pinMode(WB_IO4, OUTPUT);
  digitalWrite(WB_IO4, HIGH);
  
  int statusB, statusC;

  // Initialize serial for output.
  Serial.begin(115200);

  // Initialize I2C bus.
  Wire.begin();

  // Configure VL53L0X component.
  sensorB_vl53l0x.begin();
  sensorC_vl53l0x.begin();

  // Switch off VL53L0X component.
  sensorB_vl53l0x.VL53L0X_Off();
  sensorC_vl53l0x.VL53L0X_Off();

  // Initialize VL53L0X component.
  statusB = sensorB_vl53l0x.InitSensor(0x30);
  if(statusB)
  {
    Serial.println("Init sensorB_vl53l0x failed...");
  }
  statusC = sensorC_vl53l0x.InitSensor(0x32);
  if(statusC)
  {
    Serial.println("Init sensorC_vl53l0x failed...");
  }
}


void loop() {
  // Read Range.
  uint32_t distanceB, distanceC;
  int statusB,statusC;

  statusB = sensorB_vl53l0x.GetDistance(&distanceB);
  statusC = sensorC_vl53l0x.GetDistance(&distanceC);

  if (statusB == VL53L0X_ERROR_NONE)
  {
    // Output data.
    char report[64];
    snprintf(report, sizeof(report), "| Distance B[mm]: %ld |", distanceB);
    Serial.println(report);
  }
  if (statusC == VL53L0X_ERROR_NONE)
  {
    // Output data.
    char report[64];
    snprintf(report, sizeof(report), "| Distance C[mm]: %ld |", distanceC);
    Serial.println(report);
  }
  delay(300);
}