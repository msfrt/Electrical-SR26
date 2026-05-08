#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <SPI.h>



//pin and freq definitions
#define MOSI1 26
#define MISO1 39
#define CS1 34
#define SCK1 27
#define SPI_RDY  32
#define BRIDGE_FREQ 3000000

#define MOSI0 11
#define MISO0 12
#define CS0 10
#define ADC_FREQ 3200000

void SpiInit();
uint32_t spiReceiveData(uint16_t * destbuff, uint32_t blocksize);
uint8_t spiTransmitData(uint8_t* srcbuff, uint32_t blocksize);
uint32_t spiTransmitAndReceive16(uint32_t blocksize, uint16_t* srcbuff, uint16_t* destbuff);
void SpiAutoAddress();
void commClear();
uint8_t spiTransmitDataFSM(uint8_t* srcbuff, uint32_t blocksize);

#endif