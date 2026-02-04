/*
 *  @file bq79616.h
 *
 *  @author Vince Toledo - Texas Instruments Inc.
 *  @date 20-April-2020
 *  @version 1.0 beta version
 *  @note Built with CCS for Hercules Version: 8.1.0.00011
 *  @note Built for TMS570LS1224 (LAUNCH XL2)
 */

/*****************************************************************************
**
**  Copyright (c) 2011-2017 Texas Instruments
**
******************************************************************************/

#ifndef BQ79618_H_
#define BQ79618_H_

#include "spi.h"
#include "gio.h"
//****************************************************
// ***Register defines, choose one of the following***
// ***based on your device silicon revision:       ***
//****************************************************
#include "B0_reg.h"
#include "BMS_typedefs.h"
#include "bq79600.h"

//USER DEFINES
#define TOTALBOARDS 2       //boards in stack, including base device
#define ACTIVECHANNELS 18   //channels to activate
#define BRIDGEDEVICE 1      //
#define MAXBYTES (18*2)     //maximum number of bytes to be read from the devices (for array creation)
#define BAUDRATE 1000000    //device + uC baudrate

#define MAX_COMMAND_FRAME_SIZE 16
#define MAX_WRITE_DATA_BYTES 8
#define MAX_READ_DATA_BYTES 128

// Frame Write Types for BQ796xx series
#define FRMWRT_SGL_R 0x00 // single device read
#define FRMWRT_SGL_W 0x10 // single device write
#define FRMWRT_STK_R 0x20 // stack read
#define FRMWRT_STK_W 0x30 // stack write
#define FRMWRT_ALL_R 0x40 // broadcast read
#define FRMWRT_ALL_W 0x50 // broadcast write
#define FRMWRT_REV_ALL_W 0xE0 // broadcast write with reverse order

// BQ79600 Bridge Device ID
#define BQ79600_BRIDGE_DEVICE_ID 0x00

// Max data bytes in a single write/read operation
#define MAX_WRITE_DATA_BYTES 8
#define MAX_READ_DATA_BYTES 128 

// Max response for a single device: 1(INIT) + 1(DEV_ADDR) + 2(REG_ADDR) + DATA(numBytesToRead) + 2(CRC)
#define SINGLE_DEVICE_RESPONSE_OVERHEAD 6 
#define MAX_SINGLE_DEVICE_RESPONSE_SIZE (MAX_READ_DATA_BYTES + SINGLE_DEVICE_RESPONSE_OVERHEAD)

// Buffer size for stack reads
#define MAX_STACK_RESPONSE_BUFFER_SIZE (MAX_SINGLE_DEVICE_RESPONSE_SIZE * NUM_BQ79616_DEVICES)

// Maximum length of a single command frame to be sent
#define MAX_COMMAND_FRAME_SIZE 16 


#define BMS_DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)

//FUNCTION PROTOTYPES
void SpiAutoAddress();

void SpiWake79600(void);

void SpiCommClear();
int SpiWriteReg(uint8_t bID, uint16_t wAddr, uint64_t dwData, uint8_t bLen, uint8_t bWriteType);
int SpiWriteFrame(uint16_t bID, uint16_t wAddr, uint16_t * pData, uint16_t bLen, uint8_t bWriteType);
int SpiReadReg(uint8_t bID, uint16_t wAddr, uint16_t * pData, uint8_t bLen, uint32_t dwTimeOut, uint8_t bWriteType);

void delayms(uint32_t ms);
void delayus(uint32_t us);

void SpiDisableTimeout_600_616(void);

uint16_t SpiCRC16(const uint8_t *data, size_t length);
float Complement(uint16_t rawData, float multiplier);
bool GetFaultStat();
uint16_t volt2Byte(float volt);

void clearAfterSend();

BMSErrorCode_t bqWriteReg(uint8_t deviceID, uint16_t regAddr, uint64_t data, uint8_t numBytes, uint8_t frameType);
BMSErrorCode_t buildAndSendFrame(uint8_t deviceID, uint16_t regAddr, const uint8_t *data, uint8_t dataLen, uint8_t frameType);
uint16_t calculateCRC16(const uint8_t *data, size_t length);
BMSErrorCode_t bqReadReg(uint8_t deviceID, uint16_t regAddr, uint8_t *readBuffer, uint8_t numBytesToRead, uint8_t frameType, uint32_t timeout_ms);
BMSErrorCode_t receiveFrame(uint8_t *buffer, size_t expected_length, uint32_t timeout_ms);

//SPI variables
// spiDAT1_t dataconfig1_t;
// uint16 FFBuffer[128];

#endif /* BQ79606_H_ */
//EOF
