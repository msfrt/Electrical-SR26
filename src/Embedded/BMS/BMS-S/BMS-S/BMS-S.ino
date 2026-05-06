#include "bq_comm.h"
#include "bq_data.h"
#include"bms_data_types.h"
#include <FlexCAN_T4.h>
#include "can_send.hpp"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> cbus2;

static CAN_message_t msg;
#define CAN2_BAUDRATE 1000000

// signal definitions
#include "CAN/raptor_CAN2.hpp"

const int MODULE = 2; // BMS-S select, 1-5

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
  
}
BMSOverallData_t *bmsData;

uint8_t response_frame[(16)];
uint16_t cellVoltages[CELLS_PER_SLAVE];
int point = 0;
int expected_bytes = 1;
float current_voltage = 0;
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

}


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
            
            // BQ79718B conversion: 100uV per LSB -> divide by 10 for mV
            cellVoltages[i] = raw_val / 10;
        } else {
            // If a specific cell fails, mark as 0 and continue to the next
            cellVoltages[i] = 0;
            BMS_DEBUG_PRINTF("Failed to read Cell %d at Addr 0x%X\n", 18 - i, currentAddr);
        }
        
        // Small delay to allow the BQ chip to reset its communication state machine
        delay(10); 
    }

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

float cellTemperatures[18];

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
            float voltage_mv = raw_val * 0.1f; // 100uV resolution

            // 4. Simple conversion logic 
            // Using your 626.2mV = 20C reference. 
            // Adjust the scaling factor (0.1) based on your specific NTC Beta value
            cellTemperatures[i] = 20.0f + (626.2f - voltage_mv) * 0.1f; 
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
