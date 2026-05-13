#ifndef WHEEL_SPEED_HPP
#define WHEEL_SPEED_HPP

#include <FreqMeasureMulti.h>
#include <EasyTimer.h>
#include "sensors.hpp"

extern FreqMeasureMulti freqRR;
extern FreqMeasureMulti freqRL;

extern float sumRR, sumRL;
extern int countRR, countRL;

static uint32_t lastPulseTimeRR = 0;
static uint32_t lastPulseTimeRL = 0;

#define WHEEL_TEETH 47.0

void read_wheelSpeed(){

    static EasyTimer wheelTimer(100); // 100 Hz
    if (wheelTimer.isup()){
        uint32_t nowRR = millis();
        uint32_t nowRL = millis();
        
        if (countRR > 0) {
            ATCCR_wheelSpeedRR = (freqRR.countToFrequency(sumRR / countRR) / WHEEL_TEETH) * 6000; 
            lastPulseTimeRR = nowRR;

            sumRR = 0; countRR = 0;
        } else {
            // LOCK-UP DETECTION: No pulses in the last 10ms window
            uint32_t timeSinceLastRR = nowRR - lastPulseTimeRR;

            // If we haven't seen a pulse in 40ms, the wheel is likely locked 
            // or moving slower than ~2-3 mph.
            if (timeSinceLastRR > 40) { 
                ATCCR_wheelSpeedRR = 0; 
            }
        }
    
        if (countRL > 0) {
            ATCCR_wheelSpeedRL = freqRL.countToFrequency(sumRL / countRL) / WHEEL_TEETH * 6000;
            lastPulseTimeRL = nowRL;

            sumRL = 0; countRL = 0;
        } else {
            // LOCK-UP DETECTION: No pulses in the last 10ms window
            uint32_t timeSinceLastRL = nowRL - lastPulseTimeRL;

            // If we haven't seen a pulse in 40ms, the wheel is likely locked 
            // or moving slower than ~2-3 mph.
            if (timeSinceLastRL > 40) { 
                ATCCR_wheelSpeedRL = 0; 
            }
        }
                 
    }

}

#endif
