#include "spi.h"



void SpiInit(){
  SPI1.begin();
    //SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, MSBFIRST, SPI_MODE0));
  SPI.begin();
    //SPI.beginTransaction(SPISettings(ADC_FREQ, MSBFIRST, SPI_MODE0));
    //pinMode(CS1, OUTPUT);
    //digitalWrite(CS1, HIGH);

}

uint32_t spiReceiveData(uint16_t * destbuff, uint32_t blocksize)
{

  SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0)); // set transaction settings
    
  digitalWrite(CS1, LOW); // set CS low

  // recieve data into destbuff[]
  for (uint32_t i = 0; i < blocksize; i++) 
  {
    
    destbuff[i] = SPI1.transfer16(0xFFFF); 
  }

  digitalWrite(CS1, HIGH); // release CS
  SPI1.endTransaction(); // end SPI transaction
    
  return 0;
}

uint8_t spiTransmitData(uint8_t* srcbuff, uint32_t blocksize) {

  Serial.print("Sending ");
  Serial.print(blocksize);
  Serial.print(" Bytes\n");
  SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0)); // set transaction settings
    
  digitalWrite(CS1, LOW); // set CS low

  //send buffer over SPI
  //Serial.print("Sending:");
  for (uint32_t i = 0; i < blocksize; i++) {
    SPI1.transfer(srcbuff[i]); 
  }
  Serial.println();
  digitalWrite(CS1, HIGH); // release CS
  SPI1.endTransaction(); // end SPI transaction
    
  return 0;
}

uint32_t spiTransmitAndReceive16(uint32_t blocksize, uint16_t* srcbuff, uint16_t* destbuff) {
    
  SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0)); // set transaction settings
    
  digitalWrite(CS1, LOW); // set CS low

  // sends data in srcbuff[] and recieves data into destbuff[] at the same time
  for (uint32_t i = 0; i < blocksize; i++) {

      destbuff[i] = SPI1.transfer16(srcbuff[i]);
  }

  digitalWrite(CS1, HIGH); // release CS
    
  SPI1.endTransaction(); // end SPI transaction

  return 0;
}

void commClear() {

  digitalWrite(CS1, LOW);
  SPI1.beginTransaction(SPISettings(BRIDGE_FREQ, LSBFIRST, SPI_MODE0));
  pinMode(MOSI1, OUTPUT_OPENDRAIN);
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
  while(1){

    switch(state){
      case 0:
        while (digitalRead(SPI_RDY) == LOW) {

          if ((micros() - waitTime) > timeout_write) {
            waitTime = micros();
            Serial.println("SPI Receive Timeout: BQ never signaled READY for read");
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
        return spiTransmitData(srcbuff, blocksize);
      
    }
  }
}

  
