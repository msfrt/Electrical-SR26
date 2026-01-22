#include <SPI.h>
#include "bq79616.h"
#include "bq79600.h"

#define MOSI1 12
#define MISO1 39
#define CS1 34
#define BRIDGE_FREQ 6000000

#define MOSI0 11
#define MISO0 12
#define CS0 10
#define ADC_FREQ 3200000


void setup() {
  // put your setup code here, to run once:
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
  SPI1.begin();

    SpiWake79600(); //send wake ping to bridge device
    delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
    SpiWake79600(); //send wake ping to bridge device
    delayus(3500); //tSU(WAKE_SHUT), at least 3.5ms

    //INITIALIZE BQ79616-Q1 STACK
    SpiWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); //send wake tone to stack devices
    delayms(11.6*TOTALBOARDS); //wake tone duration is ~1.6ms per board + 10ms per board for each device to wake up from shutdown = 11.6ms per 616 board.

    //AUTO-ADDRESS
    SpiAutoAddress(); //auto address sequence

    //RESET ANY COMM FAULT CONDITIONS FROM STARTUP
    SpiWriteReg(0, FAULT_RST1, 0xFF, 1, FRMWRT_STK_W); //Reset faults on stacked devices
    SpiWriteReg(0, FAULT_RST2, 0xFF, 1, FRMWRT_STK_W); //Reset faults on stacked devices
    SpiWriteReg(0, Bridge_FAULT_RST, 0x22, 1, FRMWRT_SGL_W); //Reset FAULT_COMM and FAULT_SYS on bridge device

    //ENABLE BQ79616-Q1 MAIN ADC
    SpiWriteReg(0, DEV_CONF2, 0x0C, 1, FRMWRT_STK_W); //set all cells to active
    SpiWriteReg(0, ADC_CTRL1, 0x06, 1, FRMWRT_STK_W);   //continuous run and MAIN_GO
    delayus(5*TOTALBOARDS + 192);                       //5us reclocking per board and 192us for round robin to complete
}

void loop() {
  // put your main code here, to run repeatedly:

}



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
    // 1. Setup SPI Settings (matching your original TI FMTx config)
    // 10MHz, MSB First, SPI Mode 0 (matches your spiREG3 setup)
    SPI1.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    
    // 2. Drive Chip Select Low
    digitalWrite(CS1, LOW); 

    for (uint32_t i = 0; i < blocksize; i++) 
    {
        // 3. Receive by Transmitting a "Dummy" value. 
        // SPI.transfer16 sends 16 bits and simultaneously returns the 16 bits received.
        destbuff[i] = SPI1.transfer16(0x0000); 
    }

    // 4. Release Chip Select
    digitalWrite(CS1, HIGH);
    SPI1.endTransaction();
    
    return 0; // Success
}


uint32_t spiTransmitData(uint16_t* srcbuff, uint32_t blocksize) {
    // 1. Replicate 'dataconfig_t' (Speed, Bit Order, Mode)
    // Teensy 4.1 handles the high-speed clocking (up to 30MHz+ easily)
    SPI1.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    
    // 2. Replicate 'ChipSelect' logic
    digitalWrite(CS1, LOW); 

    for (uint32_t i = 0; i < blocksize; i++) {
        // 3. This one line replaces your while loop, FLG check, and DAT1 write
        SPI1.transfer16(srcbuff[i]); 
    }

    // 4. Replicate 'Chip_Select_Hold = 0' (Release at end of block)
    digitalWrite(CS1, HIGH);
    SPI1.endTransaction();
    
    return 0; // Success flag (equivalent to returning spi->FLG & 0xFF)
}