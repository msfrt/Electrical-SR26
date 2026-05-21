#ifndef WHEEL_SPEED_HPP
#define WHEEL_SPEED_HPP

#include <FreqMeasureMulti.h>
#include <EasyTimer.h>
#include "sensors.hpp"

extern FreqMeasureMulti freqFR;
extern FreqMeasureMulti freqFL;

extern float sumFR, sumFL;
extern int countFR, countFL;

static uint32_t lastPulseTimeFR = 0;
static uint32_t lastPulseTimeFL = 0;

#define WHEEL_TEETH 47.0

void read_wheelSpeed(){

    static EasyTimer wheelTimer(100); // 100 Hz
    if (wheelTimer.isup()){
        uint32_t nowFR = millis();
        uint32_t nowFL = millis();
        
        if (countFR > 0) {
            ATCCF_wheelSpeedFR = (freqFR.countToFrequency(sumFR / countFR) / WHEEL_TEETH) * 6000; 
            lastPulseTimeFR = nowFR;

            sumFR = 0; countFR = 0;
        } else {
            // LOCK-UP DETECTION: No pulses in the last 10ms window
            uint32_t timeSinceLastFR = nowFR - lastPulseTimeFR;

            // If we haven't seen a pulse in 40ms, the wheel is likely locked 
            // or moving slower than ~2-3 mph.
            if (timeSinceLastFR > 40) { 
                ATCCF_wheelSpeedFR = 0; 
            }
        }
    
        if (countFL > 0) {
            ATCCF_wheelSpeedFL = (freqFL.countToFrequency(sumFL / countFL) / WHEEL_TEETH) * 6000;
            lastPulseTimeFL = nowFL;

            sumFL = 0; countFL = 0;
        } else {
            // LOCK-UP DETECTION: No pulses in the last 10ms window
            uint32_t timeSinceLastFL = nowFL - lastPulseTimeFL;

            // If we haven't seen a pulse in 40ms, the wheel is likely locked 
            // or moving slower than ~2-3 mph.
            if (timeSinceLastFL > 40) { 
                ATCCF_wheelSpeedFL = 0; 
            }
        }
                 
    }

}

#endif