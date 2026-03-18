#include "spi.h"
#include "bq79618.h"

uint8_t spiTransmitData(uint8_t* srcbuff, uint32_t blocksize) {

  delayms(5);
  Serial.print("Sending ");
  Serial.print(blocksize);
  Serial.print(" Bytes\n");
  SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, MSBFIRST, SPI_MODE0)); // set transaction settings
    
  digitalWrite(CS1, LOW); // set CS low

  //send buffer over SPI
  //Serial.print("Sending:");
  for (uint32_t i = 0; i < blocksize; i++) {
    SPI1.transfer(srcbuff[i]); 
  }
  // for (uint32_t i = blocksize - 1; i > 0; i--){
  //   SPI1.transfer(srcbuff[i]);
  // }
  Serial.println();
  digitalWrite(CS1, HIGH); // release CS
  SPI1.endTransaction(); // end SPI transaction
    
  return 0;
}

void commClear() {

  digitalWrite(CS1, LOW);
  SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE1));
  pinMode(MOSI1, OUTPUT);
  delayNanoseconds(480); 
  digitalWrite(MOSI1, LOW);
  delayNanoseconds(20); 
  SPI1.transfer(0x00);
  delayNanoseconds(20);
  digitalWrite(MOSI1, HIGH);
  SPI1.endTransaction();
  delayNanoseconds(480);
  digitalWrite(CS1, HIGH);
  SPI1.setMOSI(MOSI1);

  //reset spi pins
  SPI1.end();
  SPI1.begin();


  Serial.print("commClear executed\n");
}

// $$ WIP $$
int timeout_write = 250;
unsigned long waitTime = 0;
int start = 0;
int send = 1;

uint8_t spiTransmitDataFSM(uint8_t* srcbuff, uint32_t blocksize) {
  int state = 0;
  unsigned long waitTime = 0;
  Serial.print("Attempting to send frame: ");
  for(int i =0; i < blocksize; i++){
    if(srcbuff[i] < 0x10) Serial.print("0");
    Serial.print(srcbuff[i], HEX);
  }
  Serial.print("\n");
  while(1){

    switch(state){
      case 0:
        while (digitalRead(SPI_RDY) == LOW) {

          if ((micros() - waitTime) > timeout_write) {
            waitTime = micros();
            Serial.println("SPI transmit Timeout: BQ never signaled READY for read");
            commClear();
            break;
          }  
        } 
        if (digitalRead(SPI_RDY) == 1){
          state = 1;
        } else {
          state = 0;
        }
        break;

      case 1:
        Serial.print("Transmit case = 1\n");
        return spiTransmitData(srcbuff, blocksize);
      
    }
  }
}

  
