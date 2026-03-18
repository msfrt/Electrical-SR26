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

  // bqReadReg(0, 0x2120, response_frame, 1, FRMWRT_SGL_R, 10);
  
  //spiTransmitData(readBuff, buffSize);
  // bqReadReg(0, DIR0_ADDR, response_frame, 1, FRMWRT_SGL_R, 10);

  //INITIALIZE BQ79718-Q1 STACK
  bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); //[SEND_WAKE] tone to stack devices
  Serial.print("wake tone sent to stack devices\n");
  delayms(11.6*TOTALBOARDS); 
  // bqReadReg(0, CONTROL1, response_frame, 1, FRMWRT_SGL_R, 10);

  // bqWriteReg(0, CONTROL2, 0x02, 1, FRMWRT_SGL_W); // send hardware reset ping second
  // delayms(11.6*TOTALBOARDS); 

  // //bqWriteReg(0, Bridge_FAULT_RST, 0x22, 1, FRMWRT_SGL_W); //Reset FAULT_COMM and FAULT_SYS on bridge

  // bqWriteReg(0, CONTROL1, 0X80, 1, FRMWRT_REV_ALL_W); // 5.  brdcast write reverse 0x80 to address 0x309 (change stack devices direction DIR_SEL =1)
  // delayms(11.6*TOTALBOARDS); // delay
  // bqWriteReg(0, CONTROL1, 0X80, 1, FRMWRT_SGL_W);
  // bqReadReg(0, Bridge_FAULT_RST, response_frame, 1, FRMWRT_SGL_R, 10);
  // bqWriteReg(TOTALBOARDS-1, COMM_CTRL, 0x01, 1, FRMWRT_SGL_W); // 9.  set highest addr board as top of stack
  // bqReadReg(1, FAULT_SUMMARY, response_frame, 1, FRMWRT_SGL_R, 10);

  //AUTO-ADDRESS
  //SpiRingAutoAddress(); //auto address sequence
  SpiChainAutoAddress();
  //Serial.print("autoaddress sequence sent\n");
  commClear();

  bqWriteReg(0, Bridge_FAULT_RST, 0xFF, 1, FRMWRT_SGL_W); //Reset FAULT_COMM and FAULT_SYS on bridge

  bqReadReg(0, DIR0_ADDR, response_frame, 1, FRMWRT_SGL_R, 10);
  
}

int channel = 0;            //iterators
int current_board = 0;

unsigned long lastPollTime = 0;
const unsigned long pollInterval = 100; // Poll every 100ms
int point = 0;

void loop() {
  // put your main code here, to run repeatedly:

  if (millis() - lastBlink > 300) { // Blink every 500ms
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(13, ledState);
    //bqReadReg(0, 0x2120, response_frame, 1, FRMWRT_SGL_R, 10);
    //bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W);
    //bqReadReg(0, VCELL18_HI, response_frame, 2, FRMWRT_STK_R, 10);
    //bqReadReg(0, Bridge_FAULT_RST, response_frame, 1, FRMWRT_SGL_R, 10);
    //bqWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W);
    //commClear();
    //Serial.print("Within loop\n");
  }

}








