#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <FreqMeasureMulti.h>

// bus and message_t definition
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
#define CAN1_BAUDRATE 1000000

// signal definitions
#include "CAN/SR26_CAN2.hpp"

// sensor definitions
#include "sensors.hpp"

// outgoing can message definitions
#include "can_send.hpp"

// brake bias calculation for front ATCC
// #include "bias_calc.hpp"

// rotor temp calculation for ATCC
// #include "rotor_temp_calc.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

// wheel speed calc
#include "wheel_speed.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(0, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

FreqMeasureMulti freqRR;
FreqMeasureMulti freqRL;
float sumRR = 0, sumRL = 0;
int countRR = 0, countRL = 0;

#define freq_pinRR 2 // ain2 pin25 on J2 RR
#define freq_pinRL 3 // ain3 pin17 on J1 RL

void setup() {

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 0, 255, 0); // red
  GLO_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);
  // Serial.println("starting");
  
  //initialize SPI communication
  SPI.begin();

  //initialize the CAN Bus and set its baud rate to 1Mb
  can1.begin();
  can1.setBaudRate(CAN1_BAUDRATE);

  //initialize ADCs
  initialize_ADCs();

  // freqRR.begin(freq_pinRR);
  // freqRL.begin(freq_pinRL);

  GLO_neopixel.setPixelColor(0, 0, 255, 0); // green
  GLO_neopixel.show();

  // while (!Serial) ; // wait for Arduino Serial Monitor
  // delay(10);
  // Serial.println("FreqMeasureMulti Begin");
  // delay(10);
  
}

void loop() {

  // rainbow_pixels(GLO_neopixel);
  
  // if (freqRR.available()) {
  //   sumRR = sumRR + freqRR.read();
  //   countRR = countRR + 1;
  //   Serial.println("countRR: ");
  //   Serial.println(countRR);
  // }
  
  // if (freqRL.available()) {
  //   sumRL = sumRL + freqRL.read();
  //   countRL = countRL + 1;
  // }
  
  sample_ADCs();
  
  // static EasyTimer wheelTimer(100); // 100 Hz
  // if (wheelTimer.isup()){
  //   readWheelSpeed();
  // }

  send_can1();
}
