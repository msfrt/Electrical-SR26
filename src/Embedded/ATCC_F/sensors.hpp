#ifndef SENSORS_ATCC_HPP
#define SENSORS_ATCC_HPP

#include <ReadADC.h>
#include <EasyTimer.h>

#define ADC4_CS 7
#define ADC5_CS 6

ADCChip adc4(ADC4_CS);
ADCChip adc5(ADC5_CS);

ADCSensor SusPotFL(5,0,1000);

ADCSensor RotorTempFR(2,0,1000);
ADCSensor RotorTempFL(6,0,1000);
ADCSensor SusPotFR(7,0,1000);

void initialize_ADCs()
{
  adc4.begin();
  adc5.begin();
}


void sample_ADCs()
{

  // 100 Hz
  static EasyTimer sample_timer_1(100);
  if (sample_timer_1.isup())
  {
    adc4.sample(SusPotFL);
    adc5.sample(RotorTempFR, RotorTempFL, SusPotFR);
  }
  
}

#endif
