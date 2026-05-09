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
// FL rotor is pin 2 on j2 ain71 channel 6 adc 5
// fr rotor is pin 3 on j2 ain61 channel 2 adc 5

// suspot fr is pin 4 on j2 ain101 channel 7 on adc5
// suspot fl is pin 5 on j2 ain161 channel 5 on adc 4

// rainbow RGB
#include "rainbow_pixels.hpp"

// wheel speed calc
#include "wheel_speed.hpp"

const int GLO_NeoPixel_teensy_pin = 0;
      int GLO_NeoPixel_brightness_percent = 10; // 0 - 100 %
Adafruit_NeoPixel GLO_neopixel(1, GLO_NeoPixel_teensy_pin, NEO_GRB + NEO_KHZ800);

// ATCC Module Select - 0 front, 1 back
const int ATCCMS = 0;

FreqMeasureMulti freqFR;
FreqMeasureMulti freqRL;

#define freq_pinFR 2 // ain2 pin25 on J2 FR
#define freq_pinRL 3 // ain3 pin17 on J1 RL

float sumFR=0, sumRL=0;
int countFR=0, countRL=0;
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
  freqFR.begin(freq_pinFR);
  freqRL.begin(freq_pinRL);
  
  if (freqFR.available()) {
    sumFR = sumFR + freqFR.read();
    countFR = countFR + 1;
  }
  if (freqRL.available()) {
    sumRL = sumRL + freqRL.read();
    countRL = countRL + 1;
  }
  // print results every half second
  if (timeout > 500) {
    if (countFR > 0) {
      ATCCF_wheelSpeedFR = freqFR.countToFrequency(sumFR / countFR);
    } else {
      Serial.print("(no pulses)");
    }
    Serial.print(",  ");
    if (countRL > 0) {
      ATCCF_wheelSpeedFL = freqRL.countToFrequency(sumRL / countRL);
    } else {
      Serial.print("(no pulses)");
    }
    Serial.println();
    sumFR = 0;
    sumRL = 0;
    countFR = 0;
    countRL = 0;
    timeout = 0;
  }
}

void loop() {

  //msu_pixels(GLO_neopixel);

  sample_ADCs();
  log_test_sens();
  //readWheelSpeed();

  //send_can1();
}
