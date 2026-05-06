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
#define CAN1_BAUDRATE 500000

// signal definitions
#include "CAN/SR26_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"

// sensor definitions
#include "sensors.hpp"

// outgoing can message definitions
#include "can_send.hpp"

// brake bias calculation for front ATCC
#include "bias_calc.hpp"

// rotor temp calculation for ATCC
#include "rotor_temp_calc.hpp"

// rainbow RGB
#include "rainbow_pixels.hpp"

// wheel speed calc
#include "wheel_speed.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

// ATCC Module Select - 0 front, 1 back
const int ATCCMS = 0;

FreqMeasureMulti freqRR;
FreqMeasureMulti freqRL;

#define freq_pinRR 2 // ain2 pin25 on J2 RR
#define freq_pinRL 3 // ain3 pin17 on J1 RL

float sumRR=0, sumRL=0;
int countRR=0, countRL=0;
elapsedMillis timeout;

void setup() {

  // begin Neopixel
  GLO_neopixel.begin();
  GLO_neopixel.setBrightness(map(GLO_NeoPixel_brightness_percent, 0, 100, 0, 255));
  GLO_neopixel.setPixelColor(0, 0, 255, 0); // red
  GLO_neopixel.show();

  // Initialize serial communication
  Serial.begin(112500);
  Serial.println("starting");
  
  //initialize SPI communication
  SPI.begin();

  //initialize the CAN Bus and set its baud rate to 1Mb
  can1.begin();
  can1.setBaudRate(CAN1_BAUDRATE);

  //initialize ADCs
  initialize_ADCs();

  digitalWrite(32, HIGH);

  GLO_neopixel.setPixelColor(0, 0, 255, 0); // green
  GLO_neopixel.show();

  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(10);
  Serial.println("FreqMeasureMulti Begin");
  delay(10);
  freqRR.begin(freq_pinRR);
  freqRL.begin(freq_pinRL);
  
  if (freqRR.available()) {
    sumRR = sumRR + freqRR.read();
    countRR = countRR + 1;
  }
  if (freqRL.available()) {
    sumRL = sumRL + freqRL.read();
    countRL = countRL + 1;
  }
  // print results every half second
  if (timeout > 500) {
    if (countRR > 0) {
      ATCCR_wheelSpeedRR = freqRR.countToFrequency(sumRR / countRR);
    } else {
      Serial.print("(no pulses)");
    }
    Serial.print(",  ");
    if (countRL > 0) {
     ATCCR_wheelSpeedRL = freqRL.countToFrequency(sumRL / countRL);
    } else {
      Serial.print("(no pulses)");
    }
    Serial.println();
    sumRR = 0;
    sumRL = 0;
    countRR = 0;
    countRL = 0;
    timeout = 0;
  }
}

void loop() {

  //msu_pixels(GLO_neopixel);

  sample_ADCs();
  log_test_sens();
  //readWheelSpeed();

  send_can1();
}
