/*!
 * @file DFRobot_matrixLidarDistanceSensor.h
 * @brief This is the method documentation file for DFRobot_matrixLidarDistanceSensor
 * @copyright   Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0
 * @date  2023-12-7
 * @url https://github.com/DFRobot/DFRobot_matrixLidarDistanceSensor
 */
#ifndef _DFROBOT_MATRIXLIDARDISTANCESENSOR_H_
#define _DFROBOT_MATRIXLIDARDISTANCESENSOR_H_
#include "Arduino.h"
#include "Wire.h"

//#define ENABLE_DBG ///< Enable this macro to view the detailed execution process of the program.
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

 /**
  * @brief Select to get the obstacle position.
  */
typedef enum{
    eLeft, 
    eMiddle,
    eRight,
}eDir_t;

/**
 * @brief matrix selection
 */
typedef enum{
    eMatrix_4x4 = 4,
    eMatrix_8X8 = 8,
}eMatrix_t;

class DFRobot_matrixLidarDistanceSensor{
public:
    
  /**
   * @fn DFRobot_matrixLidarDistanceSensor
   * @brief Constructor for the TOF sensor
   * @param pWire Communication protocol initialization
   */
  DFRobot_matrixLidarDistanceSensor(void);
  
  /**
   * @fn begin
   * @brief Initializes the sensor
   * @return Returns the initialization status
   */
  uint8_t begin(void);

  /**
   * @fn getAllDataConfig
   * @brief Configures the retrieval of all data
   * @param matrix Configuration matrix for sensor sampling
   * @return Returns the configuration status
   * @retval 0 Success
   * @retval 1 Failure
   */
  uint8_t getAllDataConfig(eMatrix_t matrix);

  /**
   * @fn configAvoidance
   * @brief Initializes obstacle avoidance
   * @param wall Configures the obstacle avoidance distance, in centimeters
   */
  uint8_t configAvoidance(uint16_t wall);

  /**
   * @fn getAllData
   * @brief Retrieves all data
   * @param buf Buffer to store the data
   */
  uint8_t getAllData(void *buf);

  /**
   * @fn getFixedPointData
   * @brief Retrieves data for a specific point
   * @param x X coordinate
   * @param y Y coordinate
   * @return Returns the retrieved data
   */
  uint16_t getFixedPointData(uint8_t x, uint8_t y);

  /**
   * @fn requestObstacleSensorData
   * @brief Requests obstacle avoidance data
   * @return Returns the retrieval status
   */
  uint8_t requestObstacleSensorData(void);

  /**
   * @fn getDir
   * @brief Retrieves obstacle avoidance direction suggestions
   * @return Returns the avoidance suggestions
   */
  uint8_t getDir(void);

  /**
   * @fn getEmergencyFlag
   * @brief Retrieves the emergency obstacle avoidance flag
   * @return Returns the obstacle avoidance flag
   */
  uint8_t getEmergencyFlag(void);

  /**
   * @fn getObstacleDistance
   * @brief Requests the distance to obstacles
   * @return Returns the request status
   */
  uint8_t requestObstacleDistance(void); 

  /**
   * @fn getDistance
   * @brief Retrieves the distance
   * @return Returns the distance
   */
  uint16_t getDistance(eDir_t dir);

  uint16_t retDistance(eDir_t dir);
protected:
  /**
   * @fn recvPacket
   * @brief Receive and parse the response data packet
   * 
   * @param cmd       Command to receive packet
   * @param errorCode Receive error code
   * @return Pointer array
   * @n      NULL    indicates receiving packet failed
   * @n      Non-NULL  response packet pointer
   */
  void* recvPacket(uint8_t cmd, uint8_t *errorCode);
  /**
   * @fn init
   * @brief Pure virtual function, interface init
   * 
   * @param freq     Communication frequency
   * @return Init status
   * @n       0    Init succeeded
   * @n      -1    Interface object is null pointer
   * @n      -2    Device does not exist
   */
  virtual int init(void) = 0;
  /**
   * @fn sendPacket
   * @brief I2C interface init
   * 
   * @param pkt    Set I2C communication frequency
   * @param length Set I2C communication frequency
   * @param stop   
   * @n     true   Stop
   * @n     false  Not stop
   */
  virtual void sendPacket(void *pkt, int length, bool stop) = 0;
  /**
   * @fn recvData
   * @brief I2C interface init
   * 
   * @param data    Store the received data cache
   * @param len     Byte number to be read
   * @return Actually read byte number    
   */
  virtual int recvData(void *data, int len) = 0;
    
private:
    uint32_t _timeout; ///< Time of receive timeout
    
};

class DFRobot_matrixLidarDistanceSensor_I2C:public DFRobot_matrixLidarDistanceSensor{
public:

  DFRobot_matrixLidarDistanceSensor_I2C(uint8_t addr = 0x30, TwoWire *pWire = &Wire);
  ~DFRobot_matrixLidarDistanceSensor_I2C();
private:
  TwoWire *_pWire;
  uint8_t _addr;
  int init(void);
  void sendPacket(void *pkt, int length, bool stop);
  int recvData(void *data, int len);

};

class DFRobot_matrixLidarDistanceSensor_UART:public DFRobot_matrixLidarDistanceSensor{
public:
  DFRobot_matrixLidarDistanceSensor_UART(Stream *s);
  ~DFRobot_matrixLidarDistanceSensor_UART();
private:
  uint8_t _state = 0;
  Stream *_s;
  int init(void);
  void sendPacket(void *pkt, int length, bool stop = true);
  int recvData(void *data, int len);
  
};

#endif
