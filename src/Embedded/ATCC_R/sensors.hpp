#ifndef SENSORS_ATCC_HPP
#define SENSORS_ATCC_HPP

#include <ReadADC.h>
#include <EasyTimer.h>

// ADC CS teensy pins
#define ADC1_CS 10
#define ADC2_CS 9
#define ADC3_CS 8
#define ADC4_CS 7
#define ADC5_CS 6
#define ADC6_CS 5

// ADCs
ADCChip adc4(ADC4_CS);
ADCChip adc5(ADC5_CS);

ADCSensor SusPotRL(5,0,1000);
ADCSensor RotorTempRL(2,0,1000);
ADCSensor RotorTempRR(6,0,1000);
ADCSensor SusPotRR(7,0,1000);

void initialize_ADCs()
{
  adc4.begin();
  adc5.begin();
}


void sample_ADCs()
{

  // 100 Hz
  static EasyTimer sample_timer_1(10);
  if (sample_timer_1.isup())
  {
    adc4.sample(SusPotRL);
    adc5.sample(RotorTempRR, RotorTempRL, SusPotRR);
  }
  
}

#endif
