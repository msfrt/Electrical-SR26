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

FreqMeasureMulti freqFR;
FreqMeasureMulti freqFL;

#define freq_pinFR 2 // ain2 pin25 on J2 FR
#define freq_pinFL 3 // ain3 pin17 on J1 FL

float sumFR=0, sumFL=0;
int countFR=0, countFL=0;
elapsedMillis timeout;

float frequencyToRPM(float freq, int teeth) {
  return (freq * 60.0) / teeth;
}

void readWheelSpeed () {

  if (freqFR.available()) {
    sumFR = sumFR + freqFR.read();
    countFR = countFR + 1;
  }
  if (freqFL.available()) {
    sumFL = sumFL + freqFL.read();
    countFL = countFL + 1;
  }
  // print results every half second
  if (timeout > 500) {
    if (countFR > 0) {
      ATCCF_wheelSpeedFR = freqFR.countToFrequency(sumFR / countFR);
    } else {
      Serial.print("(no pulses)");
    }
    Serial.print(",  ");
    if (countFL > 0) {
     ATCCF_wheelSpeedFL = freqFL.countToFrequency(sumFL / countFL);
    } else {
      Serial.print("(no pulses)");
    }
    Serial.println();
    sumFR = 0;
    sumFL = 0;
    countFR = 0;
    countFL = 0;
    timeout = 0;
  }

}