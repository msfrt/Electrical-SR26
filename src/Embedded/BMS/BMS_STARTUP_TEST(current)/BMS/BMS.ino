#include <SPI.h>
#include "bq79618.h"
#include "bq79600.h"


uint8_t response_frame[(128+6)*TOTALBOARDS]; //store 128 bytes + 6 header bytes for each board
unsigned long lastBlink = 0;
bool ledState = HIGH;
bool wake_sent_in_loop = 0;
void setup() {
  //delayms(10000);
  pinMode(13, OUTPUT);
  digitalWrite(13, ledState);
  Serial.begin(9600);
  while (!Serial);
  Serial.println();

  delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
  Serial.print("program starting...\n");
  SpiWake79600(); //send wake ping to bridge device
  Serial.print("wake ping sent\n");

  Serial.print("SPI_RDY ==");
  Serial.print(digitalRead(SPI_RDY));
  Serial.print("\n");


  //INITIALIZE BQ79718-Q1 STACK
  bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); //[SEND_WAKE] tone to stack devices

  Serial.print("wake tone sent to stack devices\n");
  delayms(11.6*TOTALBOARDS); //wake tone duration is ~1.6ms per board + 10ms per board for each device to wake up from shutdown = 11.6ms per 616 board.

  Serial.print("SPI_RDY ==");
  Serial.print(digitalRead(SPI_RDY));
  Serial.print("\n");

  bqReadReg(0, 0x2120, response_frame, 1, FRMWRT_SGL_R, 10);
  //AUTO-ADDRESS
  //SpiAutoAddress(); //auto address sequence
  Serial.print("autoaddress sequence sent\n");

  
}

int channel = 0;            //iterators
int current_board = 0;

unsigned long lastPollTime = 0;
const unsigned long pollInterval = 100; // Poll every 100ms
int point = 0;

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("loop start\n");
  // if (wake_sent_in_loop == 0){
  //   Serial.print("delaying 10s to send wake ping\n");
  //   delayms(10000);
  //   SpiWake79600(); //send wake ping to bridge device
  //   Serial.print("wake ping sent\n");
  //   wake_sent_in_loop = 1;



  if (millis() - lastBlink > 500) { // Blink every 500ms
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(13, ledState);
    //bqReadReg(0, OTP_ECC_DATAIN2, response_frame, 1, FRMWRT_STK_R, 10);
  }

}


void pollVoltages(){
  channel = 0;
  current_board = 0; 

  delayMicroseconds(192 + 5 * TOTALBOARDS); // Wait for conversion/propagation.

  bqReadReg(0, VCELL18_HI + (18 - ACTIVECHANNELS) * 2, response_frame, ACTIVECHANNELS * 2, 0, FRMWRT_STK_R); // SPI read

  // printing logic
  // Iterate through the boards in the stack
  for (current_board = 0; current_board < (BRIDGEDEVICE == 1 ? TOTALBOARDS - 1 : TOTALBOARDS); current_board++) {
    
      // Board numbering (Top of stack down to Base)
      Serial.print("BOARD ");
      Serial.print(TOTALBOARDS - current_board - 1);
      Serial.print(":\t");

      for (channel = 0; channel < (ACTIVECHANNELS * 2); channel += 2) {
        
          // Calculate the offset in the response_frame array
          // Each board response includes Header(4 bytes) + Data(ACTIVECHANNELS*2 bytes) + CRC(2 bytes) = (Data+6)
          int boardByteStart = (ACTIVECHANNELS * 2 + 6) * current_board;

          // Shift and combine the 8-bit pieces into a 16-bit integer
          // Note: index + 4 skips the header bytes (Device Address, Status, etc.)
          uint16_t rawData = (response_frame[boardByteStart + channel + 4] << 8) | 
                            response_frame[boardByteStart + channel + 5];

          // Convert to Volts (Standard BQ796xx VLSB is ~190.73uV)
          //Serial.print(rawData);
          float cellVoltage = rawData * 0.000190733;

          // Print voltage with 4 decimal places for precision
          Serial.print(cellVoltage, 4); 
          Serial.print("\t");
      }
      Serial.println();
  }
}

void debugFaults() {
    uint8_t faultData[8];
    // Address 0x2000 is FAULT_SUMMARY
    Serial.println("Attempting Force Read of Fault Summary...");
    bqReadReg(0, 0x2000, faultData, 1, 0, FRMWRT_SGL_R);
    
    Serial.print("Fault Summary Register: 0x");
    Serial.println(faultData[3], HEX); 
}

void SpiPingBridge() {
    uint8_t response[16] = {0};
    // Register 0x2001 is PART_ID. For BQ79600, this should return 0x14.
    // We use FRMWRT_SGL_R because we are talking directly to the bridge (ID 0).
    BMSErrorCode_t bytesRead = bqReadReg(0, 0x2001, response, 1, 100, FRMWRT_SGL_R);

    if (bytesRead > 0) {
        Serial.print("Bridge Ping Success! Bytes read: ");
        Serial.println(bytesRead);
        
        // In a Single Read, data starts at index 3 (Header, Addr1, Addr2, DATA...)
        Serial.print("PART_ID (Expected 0x14): 0x");
        Serial.println(response[3], HEX);
    } else {
        Serial.println("Bridge Ping FAILED. Check SPI wiring and Power.");
        Serial.print("PART_ID (Expected 0x14): 0x");
        for (int i = 0; i < 16; i++){
          Serial.print(response[i]);
        }
        Serial.println();
    }
}


