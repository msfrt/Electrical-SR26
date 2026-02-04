#include <SPI.h>
#include "bq79618.h"
#include "bq79600.h"

uint8_t readBuff[] = {0x80, 0x00, 0x21, 0x20, 0x00, 0x6C, 0x14};
uint32_t buffSize = sizeof(readBuff);

uint8_t response_frame[(128+6)*TOTALBOARDS]; //store 128 bytes + 6 header bytes for each board
unsigned long lastBlink = 0;
bool ledState = HIGH;
bool wake_sent_in_loop = 0;
void setup() {
  //delayms(10000);
  pinMode(13, OUTPUT);
  digitalWrite(13, ledState);
  Serial.begin(9600);
  while (!Serial); // must remove to function on its own
  Serial.println();

  delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
  Serial.print("program starting...\n");
  SpiWake79600(); //send wake ping to bridge device
  delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
  SpiWake79600(); //send wake ping again to bridge device
  delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
  Serial.print("wake ping sent twice\n"); 
  if(digitalRead(FAULT_PIN) == 0){
    Serial.print("Fault detected\n");
  }

  //commClear();

  bqReadReg(0, 0x2120, response_frame, 1, FRMWRT_SGL_R, 10);
  
  //spiTransmitData(readBuff, buffSize);

  //INITIALIZE BQ79718-Q1 STACK
  bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); //[SEND_WAKE] tone to stack devices

  //Serial.print("wake tone sent to stack devices\n");
  delayms(11.6*TOTALBOARDS); //wake tone duration is ~1.6ms per board + 10ms per board for each device to wake up from shutdown = 11.6ms per 616 board.

  bqWriteReg(0, Bridge_FAULT_RST, 0x22, 1, FRMWRT_SGL_W); //Reset FAULT_COMM and FAULT_SYS on bridge

  //AUTO-ADDRESS
  SpiAutoAddress(); //auto address sequence
  //Serial.print("autoaddress sequence sent\n");

  
}

int channel = 0;            //iterators
int current_board = 0;

unsigned long lastPollTime = 0;
const unsigned long pollInterval = 100; // Poll every 100ms
int point = 0;

void loop() {
  // put your main code here, to run repeatedly:

  if (millis() - lastBlink > 200) { // Blink every 500ms
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(13, ledState);
    //bqReadReg(0, 0x2120, response_frame, 1, FRMWRT_SGL_R, 10);
    //bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W);
    bqReadReg(0, VCELL18_HI, response_frame, 2, FRMWRT_STK_R, 10);
    //commClear();
  }

}








