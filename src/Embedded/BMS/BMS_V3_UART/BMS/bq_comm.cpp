#include "bq_comm.h"
#include "config.h" 
#include "B0_reg.h" 
#include "bq79600_reg.h" 

static const uint16_t crc16_ibm_table[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

uint16_t calculateCRC16(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF; 
    for (size_t i = 0; i < length; ++i) {
        crc = (crc >> 8) ^ crc16_ibm_table[(crc & 0xFF) ^ data[i]];
    }
    return crc;
}

void bqInitCommunication() {
    BQ_UART_SERIAL.begin(BQ_UART_BAUDRATE, SERIAL_8N1);
    BQ_UART_SERIAL.setTimeout(SERIAL_TIMEOUT_MS); 
}

BMSErrorCode_t sendFrame(const uint8_t *frame, size_t length) {
    for (int i=0; i< length; i++){
        Serial.print(frame[i], HEX);
        }
    Serial.println();
    BQ_UART_SERIAL.write(frame, length);
    BQ_UART_SERIAL.flush(); 
    delayMicroseconds(UART_TX_DELAY_US); 
    return BMS_OK;
}

BMSErrorCode_t receiveFrame(uint8_t *buffer, size_t expected_length, uint32_t timeout_ms) {
    unsigned long startTime = millis();
    size_t bytesRead = 0;
    if (expected_length == 0) return BMS_OK; // Nothing to read

    while (bytesRead < expected_length && (millis() - startTime) < timeout_ms) {
        if (BQ_UART_SERIAL.available()) {
            buffer[bytesRead++] = BQ_UART_SERIAL.read();
        }
    }
    if (bytesRead < expected_length) {
        // BMS_DEBUG_PRINTF("Receive timeout: expected %d, got %d bytes in %lu ms\n", expected_length, bytesRead, millis() - startTime);
        // Clear remaining buffer from UART to prevent old data carryover
        while(BQ_UART_SERIAL.available()) BQ_UART_SERIAL.read();
        return BMS_ERROR_COMM_TIMEOUT;
    }
    return BMS_OK;
}

BMSErrorCode_t buildAndSendFrame(uint8_t deviceID, uint16_t regAddr, const uint8_t *data, uint8_t dataLen, uint8_t frameType) {
    uint8_t frame[MAX_COMMAND_FRAME_SIZE];
    size_t frameIndex = 0;

    uint8_t initByte = 0x80 | (frameType & 0x70); 
    if ((frameType & 0x10) || (frameType == FRMWRT_REV_ALL_W) ) { 
        if (dataLen > 0 && dataLen <= MAX_WRITE_DATA_BYTES) {
            initByte |= (dataLen - 1) & 0x07; 
        } else if (dataLen == 0) { 
            initByte |= 0x00; 
        }
        if (frameType == FRMWRT_REV_ALL_W) initByte = FRMWRT_REV_ALL_W;
    }
    frame[frameIndex++] = initByte;

    if (frameType == FRMWRT_SGL_R || frameType == FRMWRT_SGL_W) {
        frame[frameIndex++] = deviceID;
    }

    frame[frameIndex++] = (regAddr >> 8) & 0xFF;
    frame[frameIndex++] = regAddr & 0xFF;

    if (frameType == FRMWRT_SGL_R || frameType == FRMWRT_STK_R || frameType == FRMWRT_ALL_R) {
        if (dataLen == 0 || dataLen > MAX_READ_DATA_BYTES) return BMS_ERROR_INVALID_RESPONSE; 
        frame[frameIndex++] = dataLen -1; 
    } else if ((frameType & 0x10) || (frameType == FRMWRT_REV_ALL_W)) { 
        if (data != nullptr && dataLen > 0) {
            for (uint8_t i = 0; i < dataLen; ++i) {
                if (frameIndex < MAX_COMMAND_FRAME_SIZE - 2) { 
                    frame[frameIndex++] = data[i];
                } else {
                    Serial.println("Error: Command frame buffer overflow during build.");
                    return BMS_ERROR_UNKNOWN; 
                }
            }
        }
    }
    
    uint16_t crc = calculateCRC16(frame, frameIndex);
    frame[frameIndex++] = crc & 0xFF;        
    frame[frameIndex++] = (crc >> 8) & 0xFF; 

    return sendFrame(frame, frameIndex);
}

BMSErrorCode_t bqWriteReg(uint8_t deviceID, uint16_t regAddr, uint64_t data, uint8_t numBytes, uint8_t frameType) {
    if (numBytes == 0 || numBytes > MAX_WRITE_DATA_BYTES) {
        return BMS_ERROR_INVALID_RESPONSE; 
    }
    uint8_t dataBytes[MAX_WRITE_DATA_BYTES];
    for (int i = 0; i < numBytes; ++i) {
        dataBytes[i] = (data >> (8 * (numBytes - 1 - i))) & 0xFF; 
    }
    return buildAndSendFrame(deviceID, regAddr, dataBytes, numBytes, frameType);
}

BMSErrorCode_t bqReadReg(uint8_t deviceID, uint16_t regAddr, uint8_t *readBuffer, uint8_t numBytesToRead, uint8_t frameType, uint32_t timeout_ms) {
    if (numBytesToRead == 0 || numBytesToRead > MAX_READ_DATA_BYTES) {
        return BMS_ERROR_INVALID_RESPONSE;
    }

    BMSErrorCode_t status = buildAndSendFrame(deviceID, regAddr, nullptr, numBytesToRead, frameType);
    if (status != BMS_OK) return status;

    size_t expectedResponseLength = SINGLE_DEVICE_RESPONSE_OVERHEAD + numBytesToRead;
    uint8_t responseFrame[MAX_SINGLE_DEVICE_RESPONSE_SIZE]; // Use max possible size for a single response
    if (expectedResponseLength > MAX_SINGLE_DEVICE_RESPONSE_SIZE) {
        Serial.println("Error: ReadReg expected response too large for buffer.");
        return BMS_ERROR_UNKNOWN;
    }
    
    status = receiveFrame(responseFrame, expectedResponseLength, timeout_ms);
    if (status != BMS_OK) return status;

    uint16_t received_crc = (uint16_t)(responseFrame[expectedResponseLength - 1] << 8) | responseFrame[expectedResponseLength - 2];
    uint16_t calculated_crc = calculateCRC16(responseFrame, expectedResponseLength - 2);
    if (received_crc != calculated_crc) {
        BMS_DEBUG_PRINTF("ReadReg CRC mismatch! Exp: 0x%04X, Got: 0x%04X for Dev %d, Reg 0x%04X\n", calculated_crc, received_crc, deviceID, regAddr);
        return BMS_ERROR_CRC;
    }

    // TODO: Verify response INIT byte, Device ID (if applicable), and Register Address
    if ((responseFrame[0] & 0x80) == 0x80) { // Check if it's a command frame (bit 7 = 1)
        Serial.println("Error: Expected response frame, got command frame type.");
        return BMS_ERROR_INVALID_RESPONSE;
    }
    if ((frameType == FRMWRT_SGL_R) && (responseFrame[1] != deviceID)) {
        BMS_DEBUG_PRINTF("Error: Response from wrong device ID. Expected %d, Got %d\n", deviceID, responseFrame[1]);
        return BMS_ERROR_INVALID_RESPONSE;
    }
    // Add more checks for REG_ADDR if needed

    memcpy(readBuffer, &responseFrame[4], numBytesToRead); 
    return BMS_OK;
}

BMSErrorCode_t bqBroadcastWrite(uint16_t regAddr, uint64_t data, uint8_t numBytes) {
    return bqWriteReg(0, regAddr, data, numBytes, FRMWRT_ALL_W); 
}

BMSErrorCode_t bqBroadcastRead(uint16_t regAddr, uint8_t *readBuffer, uint8_t numBytesToRead, uint32_t timeout_ms /* = SERIAL_TIMEOUT_MS * TOTAL_BQ_DEVICES */)
{
    /* ---- argument sanity ---- */
    if (readBuffer == nullptr ||
        numBytesToRead == 0 ||
        numBytesToRead > MAX_READ_DATA_BYTES)
        return BMS_ERROR_INVALID_RESPONSE;
#define BMS_DEBUG
    if (regAddr < 0x0000 || regAddr > 0x3FFF) {
        Serial.println(F("[BRD_R] Invalid register address"));
        return BMS_ERROR_INVALID_RESPONSE;
    }
#ifdef BMS_DEBUG
    Serial.print  (F("[BRD_R] reg 0x"));
    Serial.print  (regAddr, HEX);
    Serial.print  (F("  len "));
    Serial.println(numBytesToRead);
#endif

    /* ---- 1. send the ALL_R command frame ---- */
    BMSErrorCode_t st = buildAndSendFrame(
        0, regAddr,
        nullptr,
        numBytesToRead,          /* LEN = bytes to read */
        FRMWRT_ALL_R);           /* broadcast read opcode */
    if (st != BMS_OK) {
#ifdef BMS_DEBUG
        Serial.println(F("[BRD_R] buildAndSendFrame failed"));
#endif
        return st;
    }

    /* ---- 2. receive response frames ---- */
    constexpr size_t HDR_LEN  = 4;     /* INIT, ADDR, CMD, LEN */
    constexpr size_t CRC_LEN  = 2;     /* 16-bit CRC           */
    const     size_t FRAME_LEN  = HDR_LEN + numBytesToRead + CRC_LEN;
    const     size_t TOTAL_LEN  = FRAME_LEN * TOTAL_BQ_DEVICES;

    uint8_t rxBuf[TOTAL_LEN];
    st = receiveFrame(rxBuf, TOTAL_LEN, timeout_ms);
    if (st != BMS_OK) {
#ifdef BMS_DEBUG
        Serial.println(F("[BRD_R] receiveFrame timeout / UART error"));
#endif
        return st;
    }

#ifdef BMS_DEBUG
    Serial.print  (F("[BRD_R] got "));
    Serial.print  (TOTAL_LEN);
    Serial.println(F(" bytes"));
#endif

    /* ---- 3. CRC check + copy data ---- */
    for (size_t dev = 0; dev < TOTAL_BQ_DEVICES; ++dev) {
        size_t off = dev * FRAME_LEN;

        uint16_t crc_rx  = (rxBuf[off + FRAME_LEN - 1] << 8) |
                            rxBuf[off + FRAME_LEN - 2];
        uint16_t crc_cal = calculateCRC16(&rxBuf[off], FRAME_LEN - CRC_LEN);

#ifdef BMS_DEBUG
        Serial.print  (F("  frame["));
        Serial.print  (dev);
        Serial.print  (F("] INIT 0x"));
        Serial.print  (rxBuf[off], HEX);
        Serial.print  (F(" ADDR 0x"));
        Serial.print  (rxBuf[off+1], HEX);
        Serial.print  (F(" CRC "));
        Serial.println(crc_rx == crc_cal ? F("OK") : F("FAIL"));
#endif

        if (crc_rx != crc_cal) return BMS_ERROR_CRC;

        memcpy(readBuffer + dev * numBytesToRead,
               &rxBuf[off + HDR_LEN],
               numBytesToRead);
    }

#ifdef BMS_DEBUG
    Serial.println(F("[BRD_R] success"));
#endif
    return BMS_OK;
}

BMSErrorCode_t bqStackWrite(uint16_t regAddr, uint64_t data, uint8_t numBytes) {
    return bqWriteReg(0, regAddr, data, numBytes, FRMWRT_STK_W); 
}

BMSErrorCode_t bqStackRead(uint16_t regAddr, uint8_t *readBuffer, uint8_t numBytesPerDevice, uint32_t timeout_ms) {
    if (numBytesPerDevice == 0 || numBytesPerDevice > MAX_READ_DATA_BYTES) return BMS_ERROR_INVALID_RESPONSE;

    BMSErrorCode_t status = buildAndSendFrame(0, regAddr, nullptr, numBytesPerDevice, FRMWRT_STK_R); 
    if (status != BMS_OK) return status;

    size_t singleResponseLength = SINGLE_DEVICE_RESPONSE_OVERHEAD + numBytesPerDevice;
    size_t totalExpectedLength = singleResponseLength * NUM_BQ79718_DEVICES;
    
    if (totalExpectedLength > MAX_STACK_RESPONSE_BUFFER_SIZE) {
        Serial.println("Error: StackRead total expected response too large for buffer.");
        return BMS_ERROR_UNKNOWN;
    }
    uint8_t tempResponseFrame[MAX_STACK_RESPONSE_BUFFER_SIZE]; // Use a single large buffer

    status = receiveFrame(tempResponseFrame, totalExpectedLength, timeout_ms);
    if (status != BMS_OK) return status;

    for (int i = 0; i < NUM_BQ79718_DEVICES; ++i) {
        size_t offset = i * singleResponseLength;
        uint16_t received_crc = (uint16_t)(tempResponseFrame[offset + singleResponseLength - 1] << 8) | tempResponseFrame[offset + singleResponseLength - 2];
        uint16_t calculated_crc = calculateCRC16(&tempResponseFrame[offset], singleResponseLength - 2);

        if (received_crc != calculated_crc) {
            BMS_DEBUG_PRINTF("StackRead CRC mismatch for device in response sequence (index %d, reported DevID %d) Reg 0x%04X!\n", i, tempResponseFrame[offset+1], regAddr);
            return BMS_ERROR_CRC;
        }
        // TODO: Verify responseFrame[offset + 0] (INIT byte), responseFrame[offset + 1] (Device ID)
        memcpy(readBuffer + (i * numBytesPerDevice), &tempResponseFrame[offset + 4], numBytesPerDevice);
    }
    return BMS_OK;
}

BMSErrorCode_t bqBroadcastWriteReverse(uint16_t regAddr, uint64_t data, uint8_t numBytes) {
    return bqWriteReg(0, regAddr, data, numBytes, FRMWRT_REV_ALL_W);
}

// This function is used to wake up the BQ79600 bridge device. It is *only* meant to be called during startup either during initialization or after an error. 
// you should probably call a shutdown commands before this one; I won't enforce it here now, but maybe later on if it makes sense. 
BMSErrorCode_t bqWakePing() {
    Serial.println("Waking up BQ79600 bridge...");
    if (BQ_UART_SERIAL) BQ_UART_SERIAL.end(); // If Serial 5 is active, then end it 
    delay(1);
    pinMode(BQ_UART_WAKE_PIN, OUTPUT); // Set the UART line (bit bang) to an output pin
    digitalWrite(BQ_UART_WAKE_PIN, LOW); // then drive it low
    delayMicroseconds(WAKE_PING_DURATION_US); // keep it low for the required duration
    digitalWrite(BQ_UART_WAKE_PIN, HIGH);  // then drive it high to release the BQ79600 from reset
    delay(1); // leave it high for the required duration
    BQ_UART_SERIAL.begin(BQ_UART_BAUDRATE, SERIAL_8N1); // then stop bit banging and start the UART
    BQ_UART_SERIAL.setTimeout(SERIAL_TIMEOUT_MS); // set the timeout for the UART
    delay(1); // Allow UART to settle

    delayMicroseconds(BQ79600_WAKE_TO_ACTIVE_US); 

    return BMS_OK; // if this went OK, then we can return BMS_OK (otherwise it will fail and probably time out)
}

uint8_t autoaddr_response_frame[(1+6)*TOTAL_BQ_DEVICES];
int currentBoard = 0;

BMSErrorCode_t bqAutoAddressStack() {

    // step 1. from datasheet
    bqWakePing(); // wake 79600
    // step 2. from datasheet
    bqWriteReg(0, CONTROL1, 0X80, 1, FRMWRT_SGL_W); // DIR_SEL = 1 (change BQ79600-Q1 direction)

    // step 3. from datasheet
    bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); //  [SEND_WAKE] = 1 (wake up stack devices)
    bqDelayUs(STACK_WAKE_PROPAGATION_DELAY_US); // this is set in the config and as per the datasheet. Probably shoudn't fuck with.
    Serial.print("[SEND_WAKE] sent\n");

    // step 4. from datasheet
    //dummy stack write data 0x00 to registers 0x343 to 0x34A (sync up internal DLL).
    bqWriteReg(0, OTP_ECC_DATAIN1, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN2, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN3, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN4, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN5, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN6, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN7, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN8, 0X00, 1, FRMWRT_STK_W);

    // step 5. from datasheet
    bqWriteReg(0, CONTROL1, 0X80, 1, FRMWRT_REV_ALL_W); // brdcast write reverse 0x80 to address 0x309 (change stack devices direction DIR_SEL =1)
    Serial.print("broadcast write reverse executed\n");

    // step 6. from datasheet
    bqWriteReg(0, COMM_CTRL, 0X02, 1, FRMWRT_ALL_W); // clear previous TOP_STACK communication direction after direction is changed

    // step 7. from datasheet
    bqWriteReg(0, CONTROL1, 0X81, 1, FRMWRT_ALL_W); // (enable stack device auto addressing)
    
    Serial.print("Autoaddresing enabled\n");

    // step 8. from datasheet
    // brdcast Write consecutively to address
    for(currentBoard=0; currentBoard < TOTAL_BQ_DEVICES; currentBoard++)
    {
        bqWriteReg(0, DIR1_ADDR, currentBoard, 1, FRMWRT_ALL_W);
    }

    // step 9. from datasheet
    bqWriteReg(0, COMM_CTRL, 0X02, 1, FRMWRT_ALL_W); // set all devices as stack device

    // step 10. from datasheet    
    bqWriteReg(TOTAL_BQ_DEVICES-1, COMM_CTRL, 0x01, 1, FRMWRT_SGL_W); // set highest addr board as top of stack

    // step 11. from datasheet
    //  dummy stack read (sync up internal DLL)
    Serial.print("about to read registers in SpiAutoAddress\n");
    bqStackRead(OTP_ECC_DATAIN1, autoaddr_response_frame, 2, 10);
    Serial.print("registers read: 1\n");
    bqReadReg(0, OTP_ECC_DATAIN2, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    Serial.print("registers read: 2\n");
    bqReadReg(0, OTP_ECC_DATAIN3, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN4, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN5, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN6, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN7, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN8, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);

    // step 12. from datasheet
    bqReadReg(0, DIR1_ADDR, autoaddr_response_frame, 1, FRMWRT_STK_R, 10); // stack read addresses

    // step 13. from datasheet
    bqReadReg(0, DEV_CONF1, autoaddr_response_frame, 1, FRMWRT_STK_R, 10); // confirm this is 0x14

    Serial.print("DEV_CONF1 = ");
    for(int i=0; i<2; i++){
        Serial.print(autoaddr_response_frame[i], HEX);
    }
    Serial.println(" - should be 0x14");

}

// // This function configures the BQ79718 stack with register writes matching the legacy set_registers() logic.
void configure_stack(uint8_t &reg_val_8bit, BMSErrorCode_t &status, bool &retFlag)
{
//     retFlag = true;
//     Serial.println("Daisy Step 4: Starting detailed BQ79718 stack configurations...");

//     // 1. Mask CUST_CRC so config changes don't flag a fault (FAULT_MSK2 = 0x40)
//     status = bqStackWrite(FAULT_MSK2, 0x40, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_MSK2 (mask CUST_CRC)"); g_bmsData.communicationFault = true; return; }

//     // 2. Mask FAULT_PWR so TSREF_UV doesn't flag a fault (FAULT_MSK1 = 0xFFFE, 2 bytes)
//     status = bqWriteReg(0, FAULT_MSK1, 0xFFFE, 2, FRMWRT_STK_W);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_MSK1 (mask FAULT_PWR)"); g_bmsData.communicationFault = true; return; }

//     // 3. Reset all faults
//     status = bqStackWrite(FAULT_RST2, 0xFF, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_RST2"); g_bmsData.communicationFault = true; return; }
//     status = bqStackWrite(FAULT_RST1, 0xFF, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_RST1"); g_bmsData.communicationFault = true; return; }

//     // 4. Enable TSREF (CONTROL2 = 0x01)
//     status = bqStackWrite(CONTROL2, 0x01, 1);
//     if (status != BMS_OK) { Serial.println("Failed CONTROL2 (TSREF_EN)"); g_bmsData.communicationFault = true; return; }

//     // 5. Configure GPIOs as temp inputs (all = 0x09)
//     status = bqStackWrite(GPIO_CONF1, 0x09, 1);
//     if (status != BMS_OK) { Serial.println("Failed GPIO_CONF1"); g_bmsData.communicationFault = true; return; }
//     status = bqStackWrite(GPIO_CONF2, 0x09, 1);
//     if (status != BMS_OK) { Serial.println("Failed GPIO_CONF2"); g_bmsData.communicationFault = true; return; }
//     status = bqStackWrite(GPIO_CONF3, 0x09, 1);
//     if (status != BMS_OK) { Serial.println("Failed GPIO_CONF3"); g_bmsData.communicationFault = true; return; }
//     status = bqStackWrite(GPIO_CONF4, 0x09, 1);
//     if (status != BMS_OK) { Serial.println("Failed GPIO_CONF4"); g_bmsData.communicationFault = true; return; }

//     // 6. OTUT_THRESH: OV thresh to 80%, UT thresh to 20% (0xDA)
//     //status = bqStackWrite(OTUT_THRESH, 0xDA, 1);
//     //if (status != BMS_OK) { Serial.println("Failed OTUT_THRESH"); g_bmsData.communicationFault = true; return; }

//     // 7. OV_THRESH: Over voltage protection to 4.25V (0x25)
//     status = bqStackWrite(OV_THRESH, 0x25, 1);
//     if (status != BMS_OK) { Serial.println("Failed OV_THRESH"); g_bmsData.communicationFault = true; return; }

//     // 8. UV_THRESH: Under voltage protection to 3.0V (0x24)
//     status = bqStackWrite(UV_THRESH, 0x24, 1);
//     if (status != BMS_OK) { Serial.println("Failed UV_THRESH"); g_bmsData.communicationFault = true; return; }

//     // 9. OVUV_CTRL: voltage controls (0x05)
//     status = bqStackWrite(OVUV_CTRL1, 0x05, 1);
//     if (status != BMS_OK) { Serial.println("Failed OVUV_CTRL"); g_bmsData.communicationFault = true; return; }

//     // 10. OTUT_CTRL: temperature controls (0x05)
//     status = bqStackWrite(1, 0x05, 1);
//     if (status != BMS_OK) { Serial.println("Failed OTUT_CTRL"); g_bmsData.communicationFault = true; return; }

//     // 11. BAL_CTRL1: balance length to 10s (0x01)
//     status = bqStackWrite(BAL_CTRL1, 0x01, 1);
//     if (status != BMS_OK) { Serial.println("Failed BAL_CTRL1"); g_bmsData.communicationFault = true; return; }

//     // 12. BAL_CTRL2: enables auto balancing (0x31)
//     status = bqStackWrite(BAL_CTRL2, 0x31, 1);
//     if (status != BMS_OK) { Serial.println("Failed BAL_CTRL2"); g_bmsData.communicationFault = true; return; }

//     // 13. ACTIVE_CELL: set all cells to active (ACTIVECHANNELS - 6)
//     reg_val_8bit = (uint8_t)(CELLS_PER_SLAVE - 6);
//     status = bqStackWrite(DEV_CONF2, reg_val_8bit, 1);
//     if (status != BMS_OK) { Serial.println("Failed ACTIVE_CELL"); g_bmsData.communicationFault = true; return; }

//     // 14. ADC_CONF1: LPF_ON, LPF = 9ms (0x04)
//     // status = bqStackWrite(ADC_CONF1, 0x04, 1);
//     // if (status != BMS_OK) { Serial.println("Failed ADC_CONF1"); g_bmsData.communicationFault = true; return; }

//     // 15. COMM_TIMEOUT_CONF: sleep after 10s (0x3C)
//     // status = bqStackWrite(COMM_TIMEOUT_CONF, 0x3C, 1);
//     // if (status != BMS_OK) { Serial.println("Failed COMM_TIMEOUT_CONF"); g_bmsData.communicationFault = true; return; }

//     // 16. Reset all faults again (as in legacy code)
//     status = bqStackWrite(FAULT_RST2, 0xFF, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_RST2 (second reset)"); g_bmsData.communicationFault = true; return; }
//     status = bqStackWrite(FAULT_RST1, 0xFF, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_RST1 (second reset)"); g_bmsData.communicationFault = true; return; }

//     // 17. ADC_CTRL1: start main ADC (0x0E)
//     status = bqStackWrite(ADC_CTRL1, 0x0E, 1);
//     if (status != BMS_OK) { Serial.println("Failed ADC_CTRL1"); g_bmsData.communicationFault = true; return; }

//     // 18. ADC_CTRL2: (0x00)
//     status = bqStackWrite(ADC_CTRL2, 0x00, 1);
//     if (status != BMS_OK) { Serial.println("Failed ADC_CTRL2"); g_bmsData.communicationFault = true; return; }

//     // 19. ADC_CTRL3: (0x06)
//     status = bqStackWrite(ADC_CTRL3, 0x06, 1);
//     if (status != BMS_OK) { Serial.println("Failed ADC_CTRL3"); g_bmsData.communicationFault = true; return; }

//     // 20. FAULT_MSK1: unmask all (0x00)
//     status = bqStackWrite(FAULT_MSK1, 0x00, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_MSK1 (unmask)"); g_bmsData.communicationFault = true; return; }

//     // 21. FAULT_MSK2: (0x60)
//     status = bqStackWrite(FAULT_MSK2, 0x60, 1);
//     if (status != BMS_OK) { Serial.println("Failed FAULT_MSK2 (final)"); g_bmsData.communicationFault = true; return; }

//     if (g_bmsData.communicationFault)
//     {
//         Serial.println("Startup Error (Daisy S4): Failure during detailed BQ79718 configuration.");
//         return;
//     }
//     Serial.println("Daisy Step 4: Detailed BQ79718 configurations complete.");

//     delayMicroseconds(20);
//     retFlag = false;
}

BMSErrorCode_t bqSleepDevices() {
    Serial.println("Commanding all devices to SLEEP...");
    BMSErrorCode_t status_stack, status_bridge;
    // CONTROL1 (0x309 from B0_reg.h) bit 2 = GOTO_SLEEP for BQ79718
    status_stack = bqBroadcastWrite(CONTROL1, (1ULL << 2), 1); 
    if (status_stack != BMS_OK) {
        Serial.println("Failed to command BQ79718 stack to SLEEP.");
    }
    // BQ79600_CONTROL1 (0x0309 from bq79600_reg.h) bit 2 = GOTO_SLEEP for BQ79600
    status_bridge = bqWriteReg(BQ79600_BRIDGE_DEVICE_ID, BQ79600_CONTROL1, BQ79600_CTRL1_GOTO_SLEEP_BIT, 1, FRMWRT_SGL_W);
     if (status_bridge != BMS_OK) {
        Serial.println("Failed to command BQ79600 bridge to SLEEP.");
    }
    return (status_stack == BMS_OK && status_bridge == BMS_OK) ? BMS_OK : BMS_ERROR_UNKNOWN;
}

BMSErrorCode_t bqShutdownDevices() {
    Serial.println("Commanding all devices to SHUTDOWN...");
    BMSErrorCode_t status_stack, status_bridge;
    // CONTROL1 (0x309 from B0_reg.h) bit 3 = SHUTDOWN_CMD for BQ79718
    status_stack = bqBroadcastWrite(CONTROL1, (1ULL << 3), 1); 
    if (status_stack != BMS_OK) {
        Serial.println("Failed to command BQ79718 stack to SHUTDOWN.");
    }
    // BQ79600_CONTROL1 (0x0309 from bq79600_reg.h) bit 3 = GOTO_SHUTDOWN for BQ79600
    status_bridge = bqWriteReg(BQ79600_BRIDGE_DEVICE_ID, BQ79600_CONTROL1, BQ79600_CTRL1_GOTO_SHUTDOWN_BIT, 1, FRMWRT_SGL_W);
     if (status_bridge != BMS_OK) {
        Serial.println("Failed to command BQ79600 bridge to SHUTDOWN.");
    }
    return (status_stack == BMS_OK && status_bridge == BMS_OK) ? BMS_OK : BMS_ERROR_UNKNOWN;
}

void bqDelayUs(unsigned int us) {
    delayMicroseconds(us);
}

