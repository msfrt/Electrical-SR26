#ifndef SENSORS_ATCC_HPP
#define SENSORS_ATCC_HPP

#include <ReadADC.h>
#include <EasyTimer.h>

// ADC CS teensy pins
#define ADC1_CS 10
#define ADC2_CS 6
#define ADC3_CS 5

// ADCs
ADCChip adc1(ADC1_CS);
ADCChip adc2(ADC2_CS);
ADCChip adc3(ADC3_CS);

// front sensors
ADCSensor test10(0,0,1000);
ADCSensor test11(1,0,1000);
ADCSensor test12(2,0,1000);
ADCSensor test13(3,0,1000);
ADCSensor test14(4,0,1000);
ADCSensor test15(5,0,1000);
ADCSensor test16(6,0,1000);
ADCSensor test17(7,0,1000);

ADCSensor test20(0,0,1000);
ADCSensor test21(1,0,1000);
ADCSensor test22(2,0,1000);
ADCSensor test23(3,0,1000);
ADCSensor test24(4,0,1000);
ADCSensor test25(5,0,1000);
ADCSensor test26(6,0,1000);
ADCSensor test27(7,0,1000);

ADCSensor test30(0,0,1000);
ADCSensor test31(1,0,1000);
ADCSensor test32(2,0,1000);
ADCSensor test33(3,0,1000);
ADCSensor test34(4,0,1000);
ADCSensor test35(5,0,1000);
ADCSensor test36(6,0,1000);
ADCSensor test37(7,0,1000);

void initialize_ADCs()
{
  adc1.begin();
  adc2.begin();
  adc3.begin();
}


void sample_ADCs()
{

  // 100 Hz
  static EasyTimer sample_timer_1(100);
  if (sample_timer_1.isup())
  {
    adc1.sample(test10, test11, test12, test13, test14, test15, test16, test17);
    adc2.sample(test20, test21, test22, test23, test24, test25, test26, test27);
    adc3.sample(test30, test31, test32, test33, test34, test35, test36, test37);
  }
  
}

#endif
