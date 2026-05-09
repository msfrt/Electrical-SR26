#include <EasyTimer.h>
#include <PWMControl.h>
#include <ReadADC.h>
#include <StateCAN.h>
#include <FlexCAN_T4.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <FreqMeasureMulti.h>

#include "CAN/SR26_CAN2.hpp"
#include "can_send.hpp"

// ATCC Module Select - 0 front, 1 back
const int ATCCMS = 1;

FreqMeasureMulti freqRR;
FreqMeasureMulti freqRL;

#define freq_pinRR 2 // ain2 pin25 on J2 RR
#define freq_pinRL 3 // ain3 pin17 on J1 RL

float sumRR=0, sumRL=0;
int countRR=0, countRL=0;
elapsedMillis timeout;

float frequencyToRPM(float freq, int teeth) {
  return (freq * 60.0) / teeth;
}

void readWheelSpeed () {

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