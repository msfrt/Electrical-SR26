#ifndef SENSORS_STMM_HPP
#define SENSORS_STMM_HPP

#include <EasyTimer.h>
#include <ReadADC.h>

// ADC CS(Chip Select) teensy pins
#define ADC1_CS 10
#define ADC2_CS 9

// ADCs
ADCChip adc1(ADC1_CS);
// ADCChip adc2(ADC2_CS); 

//Analog to Digital Convertor input signals

// kept in mV (1000 to convert to V)
ADCSensor gz_raw(0,2477,1);
ADCSensor az_raw(1,2500,1);

ADCSensor gy_raw(2,2464,1);
ADCSensor ay_raw(3,2485,1);

ADCSensor gx_raw(4,2460,1);
ADCSensor ax_raw(5,2491,1);

ADCSensor test(6,0,1);

// 11.75 mV/g, biased at 2.5V
// 0 - 2000Hz frequency response

float voltage_to_g(float v){
    return (v)/11.75;
}

void initialize_ADCs()
{
  adc1.begin();
}

void sample_ADCs_1() {
    // static variable prevents object from deletion when out of scope
    static EasyTimer sample_timer_1(4000); //4000 Hz
    if(sample_timer_1.isup()) {
        adc1.sample(ax_raw, gx_raw, ay_raw, gy_raw, az_raw, gz_raw, test);
    }
    
}

#endif