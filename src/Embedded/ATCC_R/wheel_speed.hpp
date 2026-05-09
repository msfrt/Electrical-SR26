#ifndef WHEEL_SPEED_HPP
#define WHEEL_SPEED_HPP

#include <FreqMeasureMulti.h>
#include <EasyTimer.h>
#include "sensors.hpp"

extern FreqMeasureMulti freqRR;
extern FreqMeasureMulti freqRL;

extern float sumRR, sumRL;
extern int countRR, countRL;

#define WHEEL_TEETH 47.0

void readWheelSpeed(){

    if (countRR > 0) {
        ATCCR_wheelSpeedRR = freqRR.countToFrequency(sumRR / countRR) / WHEEL_TEETH; 
    } else {
        ATCCR_wheelSpeedRR = 0;
    }
  
    if (countRL > 0) {
        ATCCR_wheelSpeedRL = freqRL.countToFrequency(sumRL / countRL) / WHEEL_TEETH;
    } else {
        ATCCR_wheelSpeedRL = 0;
    }

    sumRR = 0; sumRL = 0;
    countRR = 0; countRL = 0;

}

#endif
