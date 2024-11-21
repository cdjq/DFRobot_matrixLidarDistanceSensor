/*!
 * @file obstacleAvoidance.ino
 * @brief This is a basic obstacle avoidance demo. Running this demo will perform basic obstacle avoidance.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [tangjie](jie.tang@dfrobot.com)
 * @version  V1.0
 * @date  2024-08-14
 * @url https://github.com/DFRobot/DFRobot_matrixLidarDistanceSensor
 */

#include "DFRobot_matrixLidarDistanceSensor.h"

#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  SoftwareSerial mySerial(/*rx =*/4, /*tx =*/5);
  DFRobot_matrixLidarDistanceSensor_UART tof(&mySerial);
#else
  DFRobot_matrixLidarDistanceSensor_UART tof(&Serial1);
#endif

uint16_t buf[2];

void setup(void){
  #if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
    mySerial.begin(115200);
  #elif defined(ESP32)
    Serial1.begin(115200, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
  #else
    Serial1.begin(115200);
  #endif
  Serial.begin(115200);
  while(tof.begin() != 0){
    Serial.println("begin error !!!!!");
  }
  Serial.println("begin success");

  //When using obstacle avoidance, the matrix can only be set to 4*4
  while(tof.getAllDataConfig(eMatrix_4x4) != 0){
    Serial.println("init error !!!!!");
    delay(1000);
  }

 // Set the obstacle avoidance distance to 15 centimeters
  while(tof.configAvoidance(15) != 0){
    Serial.println("init avoid error !!!!!");
    delay(1000);
  }
  Serial.println("init success");
}

void loop(void){
  // Get and return obstacle avoidance suggestions
  tof.requestObstacleSensorData();
  uint8_t dir = tof.getDir();
  uint8_t urgency = tof.getEmergencyFlag();
  Serial.print("Dir: ");
  Serial.print(dir);
  Serial.print("Urgency: ");
  Serial.println(urgency);
  
  Serial.println("------------------------------");
  
  delay(100);
}
