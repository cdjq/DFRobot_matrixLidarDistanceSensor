/*!
 * @file get8_8Data.ino
 * @brief This is a demo for retrieving all TOF data. Running this demo will allow you to get all TOF data.
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
uint16_t buf[64];
char report[128];

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
  //config matrix mode
  while(tof.getAllDataConfig(eMatrix_8X8) != 0){
    Serial.println("init error !!!!!");
    delay(1000);
  }
  Serial.println("init success");
}

void loop(void){
  tof.getAllData(buf);
  for (int i = 0; i < 64; i++) {
    snprintf(report, sizeof(report), "Zone : %3d, Distance : %4d mm\r\n",
                 i,
                 buf[i]);
    Serial.print(report);
  }
  Serial.println("------------------------------");
  delay(100);
}
