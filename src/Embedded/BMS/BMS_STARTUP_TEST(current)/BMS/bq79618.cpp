#include "bq79618.h"


int currentBoard = 0;
int currentCell = 0;

uint8_t autoaddr_response_frame[(1+6)*TOTALBOARDS];

void clearAfterSend(){
    int dummyBytes = 0;
    Serial.println("Sending dummy bytes");
    SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0)); 
    while(digitalRead(SPI_RDY)==0){
        SPI1.transfer(0xFF);
        dummyBytes++;
    }
    SPI1.endTransaction();
    Serial.print("Dummy bytes sent clearing FIFO after write: ");
    Serial.println(dummyBytes);
}


// Use PROGMEM to store the table in Flash instead of RAM                  
const uint16_t crc16_table[256] PROGMEM = { 
   0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301,
	0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1,
	0xC481, 0x0440, 0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81,
	0x0E40, 0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40, 0x1E00,
	0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1,
	0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641, 0xD201, 0x12C0, 0x1380,
	0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040, 0xF001, 0x30C0, 0x3180, 0xF141,
	0x3300, 0xF3C1, 0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501,
	0x35C0, 0x3480, 0xF441, 0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0,
	0x3E80, 0xFE41, 0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881,
	0x3840, 0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40, 0xE401,
	0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640, 0x2200, 0xE2C1,
	0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041, 0xA001, 0x60C0, 0x6180,
	0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740,
	0xA501, 0x65C0, 0x6480, 0xA441, 0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01,
	0x6FC0, 0x6E80, 0xAE41, 0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1,
	0xA881, 0x6840, 0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80,
	0xBA41, 0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640, 0x7200,
	0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041, 0x5000, 0x90C1,
	0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241, 0x9601, 0x56C0, 0x5780,
	0x9741, 0x5500, 0x95C1, 0x9481, 0x5440, 0x9C01, 0x5CC0, 0x5D80, 0x9D41,
	0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901,
	0x59C0, 0x5880, 0x9841, 0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1,
	0x8A81, 0x4A40, 0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80,
	0x8C41, 0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 };


void SpiWake79600(void) {
    pinMode(MOSI1, OUTPUT);
    pinMode(CS1, OUTPUT);

    digitalWrite(CS1, HIGH); 
    digitalWrite(MOSI1, HIGH);
    delayMicroseconds(100);

    digitalWrite(CS1, LOW); 
    delayMicroseconds(2); 
   
    digitalWrite(MOSI1, LOW);
    delayMicroseconds(2750); 
    digitalWrite(MOSI1, HIGH);

    delayMicroseconds(2);
    digitalWrite(CS1, HIGH);

    delayms(3.5);
    SPI1.setMOSI(MOSI1);
    SPI1.setMISO(MISO1);
    SPI1.setSCK(27);
    SPI1.begin();
    //SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0));
}


uint16_t calculateCRC16(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF; 
    for (size_t i = 0; i < length; ++i) {
        // The Teensy 4.1 handles the table lookup very fast without pgm_read_word
        crc = (crc >> 8) ^ crc16_table[(crc ^ data[i]) & 0xFF];
    }
    return crc;
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
    Serial.print("buildAndSendFrame frame:");
    for(int i = 0; i< frameIndex; i++) {
        if(frame[i] < 0x10) Serial.print("0");
        Serial.print(frame[i], HEX);
    }
    Serial.println();
    return spiTransmitData(frame, frameIndex);
}

void delayus(uint32_t us) {
    delayMicroseconds(us);
}

void delayms(uint32_t ms) {
    delay(ms);
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

BMSErrorCode_t receiveFrame(uint8_t *buffer, size_t expected_length, uint32_t timeout_ms) {
    unsigned long startTime = millis();
    
    if (expected_length == 0) return BMS_OK;

    while (digitalRead(SPI_RDY) == LOW) {
        if ((millis() - startTime) > timeout_ms) {
            Serial.println("SPI Receive Timeout: BQ never signaled READY for read");
            return BMS_ERROR_COMM_TIMEOUT;
        }
        delayMicroseconds(10); // Prevent CPU hogging
    }

    SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0)); 
    digitalWrite(CS1, LOW);
    
    for (size_t i = 0; i < expected_length; i++) {
        // Send dummy 0xFF, the BQ returns the actual data byte
        buffer[i] = SPI1.transfer(0xFF);
    }
    
    digitalWrite(CS1, HIGH);
    SPI1.endTransaction();

    return BMS_OK;
}

BMSErrorCode_t bqReadReg(uint8_t deviceID, uint16_t regAddr, uint8_t *readBuffer, uint8_t numBytesToRead, uint8_t frameType, uint32_t timeout_ms) {

    if (numBytesToRead == 0 || numBytesToRead > MAX_READ_DATA_BYTES) {
        return BMS_ERROR_INVALID_RESPONSE;
    }

    BMSErrorCode_t status = buildAndSendFrame(deviceID, regAddr, nullptr, numBytesToRead, frameType);
    Serial.print("^Read command frame\n");
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

uint8_t dummyReadBuf[MAX_READ_DATA_BYTES];
uint8_t devIDFrame[MAX_READ_DATA_BYTES];

void SpiAutoAddress(){
    // 1. WAKE ping already 
    Serial.print("Starting autoaddress sequence\n");
    Serial.print("SPI_RDY ==");
    Serial.print(digitalRead(SPI_RDY));
    Serial.print("\n");

    bqWriteReg(0, CONTROL1, 0X80, 1, FRMWRT_SGL_W); // 2. DIR_SEL = 1 (change BQ79600-Q1 direction)
    
    Serial.println();
    Serial.print("SPI_RDY ==");
    Serial.print(digitalRead(SPI_RDY));
    Serial.print("\n");

    bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); // 3. [SEND_WAKE] = 1 (wake up stack devices)

    bqWriteReg(0, OTP_ECC_DATAIN1, 0X00, 1, FRMWRT_STK_W); // 4. sync up internal DLL
    bqWriteReg(0, OTP_ECC_DATAIN2, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN3, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN4, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN5, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN6, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN7, 0X00, 1, FRMWRT_STK_W);
    bqWriteReg(0, OTP_ECC_DATAIN8, 0X00, 1, FRMWRT_STK_W);

    Serial.print("SPI_RDY ==");
    Serial.print(digitalRead(SPI_RDY));
    Serial.print("\n");

    bqWriteReg(0, CONTROL1, 0X80, 1, FRMWRT_REV_ALL_W); // 5.  brdcast write reverse 0x80 to address 0x309 (change stack devices direction DIR_SEL =1)

    Serial.print("broadcast write reverse executed\n");

    bqWriteReg(0, COMM_CTRL, 0X00, 1, FRMWRT_ALL_W); // 6. (clear [TOP_STACK] information after communication direction is changed.)

    bqWriteReg(0, CONTROL1, 0X81, 1, FRMWRT_ALL_W); // 7. (enable stack device auto addressing)
    
    Serial.print("Autoaddresing enabled\n");
    
    Serial.print("SPI_RDY ==");
    Serial.print(digitalRead(SPI_RDY));
    Serial.print("\n");

    // 8. brdcast Write consecutively to address
    for(currentBoard=0; currentBoard < TOTALBOARDS; currentBoard++)
    {
        bqWriteReg(0, DIR1_ADDR, currentBoard, 1, FRMWRT_ALL_W);
    }

    bqWriteReg(TOTALBOARDS-1, COMM_CTRL, 0x01, 1, FRMWRT_SGL_W); // 9.  set highest addr board as top of stack

    // 10. dummy stack read (sync up internal DLL)
    Serial.print("about to read registers in SpiAutoAddress\n");
    bqReadReg(0, OTP_ECC_DATAIN1, autoaddr_response_frame, 2, FRMWRT_STK_R, 10);
    Serial.print("registers read: 1\n");
    bqReadReg(0, OTP_ECC_DATAIN2, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    Serial.print("registers read: 2\n");
    bqReadReg(0, OTP_ECC_DATAIN3, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN4, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN5, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN6, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN7, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);
    bqReadReg(0, OTP_ECC_DATAIN8, autoaddr_response_frame, 1, FRMWRT_STK_R, 10);

    bqReadReg(0, DIR1_ADDR, autoaddr_response_frame, 1, FRMWRT_STK_R, 10); // 11. stack read addresses


}


uint16_t volt2Byte(float volt)
{
    return (uint16_t)~((int16_t)((-volt/0.00019073)-1.0));
}

