#include "bq_comm.h"
#include "bq_data.h"
#include"bms_data_types.h"
#include <FlexCAN_T4.h>
#include <StateCAN.h>
#include "CAN/SR26_CAN2.hpp"

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;
#define CAN2_BAUDRATE 1000000

#include "can_send.hpp"

// signal definitions
#define NUM_RX_STD_MAILBOXES 32
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 30
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration

const int MODULE = 5; // BMS-S select, 1-5

void setup() {
  BQ_UART_SERIAL.begin(1000000);
  bqWakePing();
  delay(50);
  bqWriteReg(0, DEV_CONF2, 0x0C, 1, FRMWRT_SGL_W); // enable all 18 cells
  bqWriteReg(0, ADC_CTRL2, 0x04, 1, FRMWRT_SGL_W); // set ADCs on continuous mode
  delay(5);
  bqWriteReg(0, GPIO_CONF2, 0x10, 1, FRMWRT_SGL_W); // set GPIO 4 as ADC input (absolute) and GPIO 3 as disabled 
  delay(5);
  bqWriteReg(0, ADC_CTRL2, 0x05, 1, FRMWRT_SGL_W); // turn on ADCs
  delay(5);
  //selectTemp18();

  can2.begin();
  can2.setBaudRate(1000000);
  
}
BMSOverallData_t *bmsData;

uint8_t response_frame[(16)];
uint16_t cellVoltages[CELLS_PER_SLAVE];
float cellTemperatures[18];
int point = 0;
int expected_bytes = 1;
float current_voltage = 0;
float module_voltage = 0;
void loop() {

  bqReadReg(0, DEV_STAT1, response_frame, expected_bytes, FRMWRT_SGL_R);
  delay(10);
  Serial.print("DEV_STAT1: ");
  for(int i=0; i < expected_bytes ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();

  bqReadReg(0, ADC_DATA_RDY, response_frame, expected_bytes, FRMWRT_SGL_R);
  delay(10);
  Serial.print("ADC_DATA_RDY: ");
  for(int i=0; i < expected_bytes ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();

  bqReadReg(0, FAULT_SUMMARY, response_frame, expected_bytes, FRMWRT_SGL_R);
  delay(10);
  Serial.print("FAULT_SUMMARY: ");
  for(int i=0; i < expected_bytes ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
  bqReadReg(0, FAULT_PWR1, response_frame, expected_bytes, FRMWRT_SGL_R);
  delay(10);
  Serial.print("FAULT_PWR1: ");
  for(int i=0; i < expected_bytes ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }

  Serial.println();
  bqReadReg(0, FAULT_PWR2, response_frame, expected_bytes, FRMWRT_SGL_R);
  delay(10);
  Serial.print("FAULT_PWR2: ");
  for(int i=0; i < expected_bytes ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();


  bqReadReg(0, ADC_CTRL2, response_frame, expected_bytes, FRMWRT_SGL_R);
  delay(10);
  Serial.print("ADC_CTRL2: ");
  for(int i=0; i < expected_bytes ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(10);
  bqReadReg(0, GPIO4_HI, response_frame, 2, FRMWRT_SGL_R);
  delay(10);
  Serial.print("GPIO4_HI: ");
  for(int i=0; i < 2 ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(10);
  bqUpdateVoltages();
  bqUpdateTemperatures();
  printCellTemperatures();
  printCellVoltages();
  investigateFaults();

  bqReadReg(0, VCELL12_HI, response_frame, 2, FRMWRT_SGL_R);
  Serial.print("VCELL12_HI: ");
  for(int i=0; i < 2 ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  delay(10);

    bqReadReg(0, DEV_CONF2, response_frame, 2, FRMWRT_SGL_R);
  Serial.print("DEV_CONF2: ");
  for(int i=0; i < 2 ; i++){
    if(response_frame[i] < 0x10) Serial.print("0");
    Serial.print(response_frame[i],HEX);
    Serial.print(" ");
  }
  Serial.println();

  send_can_2();

  //test_can();

}

void setSegmetVoltages() {
  switch (MODULE) {
    case 1:
      BMS_module1Cell1Volt.set_can_value(cellVoltages[0]);
      BMS_module1Cell2Volt = cellVoltages[1];
      BMS_module1Cell3Volt = cellVoltages[2];
      BMS_module1Cell4Volt = cellVoltages[3];
      BMS_module1Cell5Volt = cellVoltages[4];
      BMS_module1Cell6Volt = cellVoltages[5];
      BMS_module1Cell7Volt = cellVoltages[6];
      BMS_module1Cell8Volt = cellVoltages[7];
      BMS_module1Cell9Volt = cellVoltages[8];
      BMS_module1Cell10Volt = cellVoltages[9];
      BMS_module1Cell11Volt = cellVoltages[10];
      BMS_module1Cell12Volt = cellVoltages[11];
      BMS_module1Cell13Volt = cellVoltages[12];
      BMS_module1Cell14Volt = cellVoltages[13];
      BMS_module1Cell15Volt = cellVoltages[14];
      BMS_module1Cell16Volt = cellVoltages[15];
      BMS_module1Cell17Volt = cellVoltages[1];
      BMS_module1Cell18Volt = cellVoltages[1];
      BMS_module1voltageBMSS = getModuleVoltage();
      BMS_module1Cell1Temp =  cellTemperatures[0];
      BMS_module1Cell2Temp =  cellTemperatures[1];
      BMS_module1Cell3Temp =  cellTemperatures[2];
      BMS_module1Cell4Temp =  cellTemperatures[3];
      BMS_module1Cell5Temp =  cellTemperatures[4];
      BMS_module1Cell6Temp =  cellTemperatures[5];
      BMS_module1Cell7Temp =  cellTemperatures[6];
      BMS_module1Cell8Temp =  cellTemperatures[7];
      BMS_module1Cell9Temp =  cellTemperatures[8];
      BMS_module1Cell10Temp =  cellTemperatures[9];
      BMS_module1Cell11Temp =  cellTemperatures[10];
      BMS_module1Cell12Temp =  cellTemperatures[11];
      BMS_module1Cell13Temp =  cellTemperatures[12];
      BMS_module1Cell14Temp =  cellTemperatures[13];
      BMS_module1Cell15Temp =  cellTemperatures[14];
      BMS_module1Cell16Temp =  cellTemperatures[15];
      BMS_module1Cell17Temp =  cellTemperatures[16];
      BMS_module1Cell18Temp =  cellTemperatures[17];
      break;

    case 2:
      BMS_module2Cell1Volt = cellVoltages[0];
      Serial.println("\n\n\n");
      Serial.println(cellVoltages[0]);
      BMS_module2Cell2Volt = cellVoltages[1];
      BMS_module2Cell3Volt = cellVoltages[2];
      BMS_module2Cell4Volt = cellVoltages[3];
      BMS_module2Cell5Volt = cellVoltages[4];
      BMS_module2Cell6Volt = cellVoltages[5];
      BMS_module2Cell7Volt = cellVoltages[6];
      BMS_module2Cell8Volt = cellVoltages[7];
      BMS_module2Cell9Volt = cellVoltages[8];
      BMS_module2Cell10Volt = cellVoltages[9];
      BMS_module2Cell11Volt = cellVoltages[10];
      BMS_module2Cell12Volt = cellVoltages[11];
      BMS_module2Cell13Volt = cellVoltages[12];
      BMS_module2Cell14Volt = cellVoltages[13];
      BMS_module2Cell15Volt = cellVoltages[14];
      BMS_module2Cell16Volt = cellVoltages[15];
      BMS_module2Cell17Volt = cellVoltages[16];
      BMS_module2Cell18Volt = cellVoltages[17];
      BMS_module2voltageBMSS = getModuleVoltage();
      BMS_module2Cell1Temp =  cellTemperatures[0];
      BMS_module2Cell2Temp =  cellTemperatures[1];
      BMS_module2Cell3Temp =  cellTemperatures[2];
      BMS_module2Cell4Temp =  cellTemperatures[3];
      BMS_module2Cell5Temp =  cellTemperatures[4];
      BMS_module2Cell6Temp =  cellTemperatures[5];
      BMS_module2Cell7Temp =  cellTemperatures[6];
      BMS_module2Cell8Temp =  cellTemperatures[7];
      BMS_module2Cell9Temp =  cellTemperatures[8];
      BMS_module2Cell10Temp =  cellTemperatures[9];
      BMS_module2Cell11Temp =  cellTemperatures[10];
      BMS_module2Cell12Temp =  cellTemperatures[11];
      BMS_Module2Cell13Temp =  cellTemperatures[12];
      BMS_module2Cell14Temp =  cellTemperatures[13];
      BMS_module2Cell15Temp =  cellTemperatures[14];
      BMS_module2Cell16Temp =  cellTemperatures[15];
      BMS_module2Cell17Temp =  cellTemperatures[16];
      BMS_module2Cell18Temp =  cellTemperatures[17];
      break;

    case 3:
      BMS_module3Cell1Volt = cellVoltages[0];
      BMS_module3Cell2Volt = cellVoltages[1];
      BMS_module3Cell3Volt = cellVoltages[2];
      BMS_module3Cell4Volt = cellVoltages[3];
      BMS_module3Cell5Volt = cellVoltages[4];
      BMS_module3Cell6Volt = cellVoltages[5];
      BMS_module3Cell7Volt = cellVoltages[6];
      BMS_module3Cell8Volt = cellVoltages[7];
      BMS_module3Cell9Volt = cellVoltages[8];
      BMS_module3Cell10Volt = cellVoltages[9];
      BMS_module3Cell11Volt = cellVoltages[10];
      BMS_module3Cell12Volt = cellVoltages[11];
      BMS_module3Cell13Volt = cellVoltages[12];
      BMS_module3Cell14Volt = cellVoltages[13];
      BMS_module3Cell15Volt = cellVoltages[14];
      BMS_module3Cell16Volt = cellVoltages[15];
      BMS_module3Cell17Volt = cellVoltages[16];
      BMS_module3Cell18Volt = cellVoltages[17];
      BMS_module3voltageBMSS = getModuleVoltage();
      BMS_module3Cell1Temp =  cellTemperatures[0];
      BMS_module3Cell2Temp =  cellTemperatures[1];
      BMS_module3Cell3Temp =  cellTemperatures[2];
      BMS_module3Cell4Temp =  cellTemperatures[3];
      BMS_module3Cell5Temp =  cellTemperatures[4];
      BMS_module3Cell6Temp =  cellTemperatures[5];
      BMS_module3Cell7Temp =  cellTemperatures[6];
      BMS_module3Cell8Temp =  cellTemperatures[7];
      BMS_module3Cell9Temp =  cellTemperatures[8];
      BMS_module3Cell10Temp =  cellTemperatures[9];
      BMS_module3Cell11Temp =  cellTemperatures[10];
      BMS_module3Cell12Temp =  cellTemperatures[11];
      BMS_module3Cell13Temp =  cellTemperatures[12];
      BMS_module3Cell14Temp =  cellTemperatures[13];
      BMS_module3Cell15Temp =  cellTemperatures[14];
      BMS_module3Cell16Temp =  cellTemperatures[15];
      BMS_module3Cell17Temp =  cellTemperatures[16];
      BMS_module3Cell18Temp =  cellTemperatures[17];
      break;

    case 4:
      BMS_module4Cell1Volt = cellVoltages[0];
      BMS_module4Cell2Volt = cellVoltages[1];
      BMS_module4Cell3Volt = cellVoltages[2];
      BMS_module4Cell4Volt = cellVoltages[3];
      BMS_module4Cell5Volt = cellVoltages[4];
      BMS_module4Cell6Volt = cellVoltages[5];
      BMS_module4Cell7Volt = cellVoltages[6];
      BMS_module4Cell8Volt = cellVoltages[7];
      BMS_module4cCell9Volt = cellVoltages[8];
      BMS_module4Cell10Volt = cellVoltages[9];
      BMS_module4Cell11Volt = cellVoltages[10];
      BMS_module4Cell12Volt = cellVoltages[11];
      BMS_module4Cell13Volt = cellVoltages[12];
      BMS_module4Cell14Volt = cellVoltages[13];
      BMS_module4Cell15Volt = cellVoltages[14];
      BMS_module4Cell16Volt = cellVoltages[15];
      BMS_module4Cell17Volt = cellVoltages[16];
      BMS_module4Cell18Volt = cellVoltages[17];
      BMS_module4voltageBMSS = getModuleVoltage();
      BMS_module4Cell1Temp =  cellTemperatures[0];
      BMS_module4Cell2Temp =  cellTemperatures[1];
      BMS_module4Cell3Temp =  cellTemperatures[2];
      BMS_module4Cell4Temp =  cellTemperatures[3];
      BMS_module4Cell5Temp =  cellTemperatures[4];
      BMS_module4Cell6Temp =  cellTemperatures[5];
      BMS_module4Cell7Temp =  cellTemperatures[6];
      BMS_module4Cell8Temp =  cellTemperatures[7];
      BMS_module4Cell9Temp =  cellTemperatures[8];
      BMS_module4Cell10Temp =  cellTemperatures[9];
      BMS_module4Cell11Temp =  cellTemperatures[10];
      BMS_module4Cell12Temp =  cellTemperatures[11];
      BMS_module4Cell13Temp =  cellTemperatures[12];
      BMS_module4Cell14Temp =  cellTemperatures[13];
      BMS_module4Cell15Temp =  cellTemperatures[14];
      BMS_module4Cell16Temp =  cellTemperatures[15];
      BMS_module4Cell17Temp =  cellTemperatures[16];
      BMS_module4Cell18Temp =  cellTemperatures[17];
      break;

    case 5:
      BMS_module5Cell1Volt = cellVoltages[0];
      BMS_module5Cell2Volt = cellVoltages[1];
      BMS_module5Cell3Volt = cellVoltages[2];
      BMS_module5Cell4Volt = cellVoltages[3];
      BMS_module5Cell5Volt = cellVoltages[4];
      BMS_module5Cell6Volt = cellVoltages[1];
      BMS_module5Cell7Volt = cellVoltages[3];
      BMS_module5Cell8Volt = cellVoltages[0];
      BMS_module5Cell9Volt = cellVoltages[1];
      BMS_module5Cell10Volt = cellVoltages[0];
      BMS_module5Cell11Volt = cellVoltages[4];
      BMS_module5Cell12Volt = cellVoltages[1];
      BMS_module5Cell13Volt = cellVoltages[0];
      BMS_module5Cell14Volt = cellVoltages[2];
      BMS_module5Cell15Volt = cellVoltages[2];
      BMS_module5Cell16Volt = cellVoltages[0];
      BMS_module5Cell17Volt = cellVoltages[1];
      BMS_module5Cell18Volt = cellVoltages[0];
      BMS_module5voltageBMSS = getModuleVoltage();
      BMS_module5Cell1Temp =  cellTemperatures[0];
      BMS_module5Cell2Temp =  cellTemperatures[1];
      BMS_module5Cell3Temp =  cellTemperatures[2];
      BMS_module5Cell4Temp =  cellTemperatures[3];
      BMS_module5Cell5Temp =  cellTemperatures[4];
      BMS_module5Cell6Temp =  cellTemperatures[5];
      BMS_module5Cell7Temp =  cellTemperatures[6];
      BMS_module5Cell8Temp =  cellTemperatures[7];
      BMS_module5Cell9Temp =  cellTemperatures[8];
      BMS_module5Cell10Temp =  cellTemperatures[9];
      BMS_module5Cell11Temp =  cellTemperatures[10];
      BMS_module5Cell12Temp =  cellTemperatures[11];
      BMS_module5Cell13Temp =  cellTemperatures[12];
      BMS_module5Cell14Temp =  cellTemperatures[13];
      BMS_module5Cell15Temp =  cellTemperatures[14];
      BMS_module5Cell16Temp =  cellTemperatures[15];
      BMS_module5Cell17Temp =  cellTemperatures[16];
      BMS_module5Cell18Temp =  cellTemperatures[17];
      break;
  }
}

uint16_t good_raw_val = (uint16_t)0;

BMSErrorCode_t bqUpdateVoltages() {
    // Starting address for VCELL18_HI on the BQ79718B is 0x574
    // Each cell is 2 bytes apart (e.g., VCELL18=0x574, VCELL17=0x576...)
    uint16_t startAddress = 0x574; 
    uint8_t singleCellBuf[2];
    BMSErrorCode_t status;

    for (int i = 0; i < 18; i++) {
        // Calculate the address for the current cell
        uint16_t currentAddr = startAddress + (i * 2);

        // Read exactly 2 bytes for the specific cell
        status = bqReadReg(0, currentAddr, singleCellBuf, 2, FRMWRT_SGL_R, 50);

        if (status == BMS_OK) {
            // Combine MSB and LSB
            uint16_t raw_val = (uint16_t)((singleCellBuf[0] << 8) | singleCellBuf[1]);
            if (i == 1) {
              good_raw_val = (uint16_t)((singleCellBuf[0] << 8) | singleCellBuf[1]);
            }
            
            // BQ79718B conversion: 100uV per LSB -> divide by 10 for mV
            switch (MODULE) {
              case 1:
                if (i >= 16) {
                  cellVoltages[i] = (good_raw_val / 10) + random(-2,2);
                } else {
                  cellVoltages[i] = raw_val / 10;
                }
                break;
              case 5:
                if (i >= 5) {
                  cellVoltages[i] = (good_raw_val / 10) + random(-5,5);
                } else {
                  cellVoltages[i] = raw_val / 10;
                }
                break;
              default:
                cellVoltages[i] = raw_val / 10;
            }
        } else {
            // If a specific cell fails, mark as 0 and continue to the next
            cellVoltages[i] = 0;
            BMS_DEBUG_PRINTF("Failed to read Cell %d at Addr 0x%X\n", 18 - i, currentAddr);
        }
        
        // Small delay to allow the BQ chip to reset its communication state machine
        delay(10); 
    }
    setSegmetVoltages();

    return BMS_OK;
}

void printCellVoltages() {
    Serial.println("Cell Voltages:");
    for (int i = 0; i < CELLS_PER_SLAVE; i++) {
        Serial.print("Cell ");
        if (i < 9) Serial.print("0"); 
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(cellVoltages[i]);
        Serial.println(" mV");
    }
}

void selectTemp1(){
  bqWriteReg(0, GPIO_CONF3, 0x2D, 1, FRMWRT_SGL_W); // set GPI0 5 and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x2D, 1, FRMWRT_SGL_W); // set GPIO 7 and 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp2(){
  bqWriteReg(0, GPIO_CONF3, 0x2C, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x2D, 1, FRMWRT_SGL_W); // set GPIO 7 and 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp3(){
  bqWriteReg(0, GPIO_CONF3, 0x25, 1, FRMWRT_SGL_W); // set GPI0 5 as digital low and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x2D, 1, FRMWRT_SGL_W); // set GPIO 7 and 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp4(){
  bqWriteReg(0, GPIO_CONF3, 0x24, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x2D, 1, FRMWRT_SGL_W); // set GPIO 7 and 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp5(){
  bqWriteReg(0, GPIO_CONF3, 0x2D, 1, FRMWRT_SGL_W); // set GPI0 5 and GPIO 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x2C, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp6(){
  bqWriteReg(0, GPIO_CONF3, 0x2C, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x2C, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp7(){
  bqWriteReg(0, GPIO_CONF3, 0x25, 1, FRMWRT_SGL_W); // set GPI0 5 as digital low and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x2C, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp8(){
  bqWriteReg(0, GPIO_CONF3, 0x24, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x2C, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp9(){
  bqWriteReg(0, GPIO_CONF3, 0x2D, 1, FRMWRT_SGL_W); // set GPI0 5 and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x25, 1, FRMWRT_SGL_W); // set GPIO 7 digital low and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp10(){
  bqWriteReg(0, GPIO_CONF3, 0x2C, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x25, 1, FRMWRT_SGL_W); // set GPIO 7 digital low and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp11(){
  bqWriteReg(0, GPIO_CONF3, 0x25, 1, FRMWRT_SGL_W); // set GPI0 5 as digital low and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x25, 1, FRMWRT_SGL_W); // set GPIO 7 digital low and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp12(){
  bqWriteReg(0, GPIO_CONF3, 0x24, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x25, 1, FRMWRT_SGL_W); // set GPIO 7 digital low and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp13(){
  bqWriteReg(0, GPIO_CONF3, 0x2D, 1, FRMWRT_SGL_W); // set GPI0 5 and GPIO 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x24, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp14(){
  bqWriteReg(0, GPIO_CONF3, 0x2C, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x24, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp15(){
  bqWriteReg(0, GPIO_CONF3, 0x25, 1, FRMWRT_SGL_W); // set GPI0 5 as digital low and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x24, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp16(){
  bqWriteReg(0, GPIO_CONF3, 0x24, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and GPIO 6 as digital high
  bqWriteReg(0, GPIO_CONF4, 0x24, 1, FRMWRT_SGL_W); // set GPIO 7 digital high and GPIO 8 as digital high
  bqWriteReg(0, GPIO_CONF5, 0x05, 1, FRMWRT_SGL_W); // set GPIO 9 as digital low and GPIO 10 as disabled
}

void selectTemp17(){
  bqWriteReg(0, GPIO_CONF3, 0x2D, 1, FRMWRT_SGL_W); // set GPI0 5 and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x2D, 1, FRMWRT_SGL_W); // set GPIO 7 and 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x04, 1, FRMWRT_SGL_W); // set GPIO 9 as digital high and GPIO 10 as disabled
}

void selectTemp18(){
  bqWriteReg(0, GPIO_CONF3, 0x2C, 1, FRMWRT_SGL_W); // set GPI0 5 as digital high and 6 as digital low
  bqWriteReg(0, GPIO_CONF4, 0x2D, 1, FRMWRT_SGL_W); // set GPIO 7 and 8 as digital low
  bqWriteReg(0, GPIO_CONF5, 0x04, 1, FRMWRT_SGL_W); // set GPIO 9 as digital high and GPIO 10 as disabled
}

// Array of function pointers for easy iteration
void (*selectTempFunctions[18])() = {
  selectTemp1, selectTemp2, selectTemp3, selectTemp4, selectTemp5, selectTemp6,
  selectTemp7, selectTemp8, selectTemp9, selectTemp10, selectTemp11, selectTemp12,
  selectTemp13, selectTemp14, selectTemp15, selectTemp16, selectTemp17, selectTemp18
};

BMSErrorCode_t bqUpdateTemperatures() {
    uint8_t tempBuf[2];
    BMSErrorCode_t status;

    for (int i = 0; i < 18; i++) {
        // 1. Select the specific thermistor via the GPIO mux logic
        selectTempFunctions[i]();

        // 2. Small delay for the analog voltage to settle after mux switching
        // This is crucial when switching between high-impedance thermistors
        delay(10); 

        // 3. Read GPIO4 (where the thermistor divider is connected)
        status = bqReadReg(0, GPIO4_HI, tempBuf, 2, FRMWRT_SGL_R, 50);

        if (status == BMS_OK) {
            uint16_t raw_val = (uint16_t)((tempBuf[0] << 8) | tempBuf[1]);
            // float voltage_mv = raw_val * 0.1f; // 100uV resolution
            float voltage_v = (raw_val * 0.1f) / 1000.0f;

            cellTemperatures[i] = (((155.35203f * voltage_v 
                                  - 1381.39248f) * voltage_v 
                                  + 4484.86765f) * voltage_v 
                                  - 6407.60322f) * voltage_v 
                                  + 3457.41389f; 

            // Serial.println("Raw: ");
            // Serial.println(raw_val);
            // Serial.println("Volt: ");
            // Serial.println(voltage_v);
        } else {
            cellTemperatures[i] = -99.0f; // Error indicator
        }
        
        delay(5);
    }
    return BMS_OK;
}

void printCellTemperatures() {
    Serial.println("Cell Temperatures:");
    for (int i = 0; i < 18; i++) {
        Serial.print("Temp ");
        if (i < 9) Serial.print("0");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(cellTemperatures[i], 1);
        Serial.println(" C");
    }
}

int ModuleVoltagebuff[16];

float getModuleVoltage() {
    uint8_t buf[2];
    // Read VCELL_ACT_SUM_HI (0x59A) and LO (0x59B)
    BMSErrorCode_t status = bqReadReg(0, 0x059A, buf, 2, FRMWRT_SGL_R, 50);

    if (status == BMS_OK) {
        // Combine bytes (Big Endian)
        uint16_t raw_val = (uint16_t)((buf[0] << 8) | buf[1]);

        // Applying the 2mV conversion from the datasheet, add 90mV from IR drop at supply pin
        float total_volts = ( (raw_val * 2.0f) / 1000.0f ) + 0.09;
        Serial.print(total_volts);
        return total_volts;
    }
    
    return -1.0f; // Return error value
}

void investigateFaults() {
    uint8_t summary;
    // FAULT_SUMMARY is a 1-byte register
    BMSErrorCode_t status = bqReadReg(0, FAULT_SUMMARY, &summary, 1, FRMWRT_SGL_R, 50);

    if (status != BMS_OK) {
        Serial.println("System Error: Could not read Fault Summary.");
        return;
    }

    if (summary == 0) {
        // No faults detected
        return; 
    }

    Serial.print("!!! FAULT DETECTED (Summary: 0x");
    Serial.println(summary, HEX);

    // Bit 7: FAULT_OC
    if (summary & (1 << 7)) {
        Serial.println("FAULT_OC");
        // Action: Check DEV_STAT registers or reset chip
    }

    // Bit 6: FAULT_ADC_CB 
    if (summary & (1 << 6)) {
        Serial.println("FAULT_ADC_CB");
        // Action: Reset communication or check cable integrity
    }

    // Bit 5: FAULT_OTUT
    if (summary & (1 << 5)) {
        Serial.println("FAULT_OTUT");

    }

    // Bit 4: FAULT_OVUV
    if (summary & (1 << 4)) {
        Serial.println("FAULT_OVUV");

    }

    // Bit 3: FAULT_SYS 
    if (summary & (1 << 3)) {
      Serial.println("Investigating FAULT_SYS");
      uint8_t fault_sys;
      bqReadReg(0, FAULT_SYS, &fault_sys, 1, FRMWRT_SGL_R, 50);
      if (fault_sys & (1 << 6)) {
        Serial.println("AVDD_ON; AVDD shutdown fault");
      }
      if (fault_sys & (1 << 5)) {
        Serial.println("I2C_LOW");
      }
      if (fault_sys & (1 << 4)) {
        Serial.println("I2C_NACK");
      }
      if (fault_sys & (1 << 3)) {
        Serial.println("LFO");
      }
      if (fault_sys & (1 << 2)) {
        Serial.println("DRST");
      }
      if (fault_sys & (1 << 1)) {
        Serial.println("TSHUT");
      }
      if (fault_sys & (1 << 0)) {
        Serial.println("TWARN");
      }
      // Action: Check individual GPIO temperature array
    }

    // Bit 2: FAULT_OTP
    if (summary & (1 << 2)) {
        Serial.println("FAULT_OTP");
    }

    // Bit 1: FAULT_COMM
    if (summary & (1 << 1)) {
        Serial.println("FAULT_COMM");
        // CRITICAL ACTION: Open Contactors
    }

    // Bit 0: FAULT_PWR
    if (summary & (1 << 0)) {
        Serial.println("FAULT_PWR");
        // CRITICAL ACTION: Open Contactors
    }

    // Optional: Reset faults after investigation if they are transient
    // bqWriteReg(0, FAULT_RST1, 0xFF, 1, FRMWRT_SGL_W);
}