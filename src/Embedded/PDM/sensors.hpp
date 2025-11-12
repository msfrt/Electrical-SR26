#include <ReadADC.h>
#include <EasyTimer.h>

// Sensor definitions

// ADCSensor my_sensor(int chip_select, int adc_channel, int sensor_zero_mV, int mV_per_sensor_unit);

// ADC CS teensy pins
#define ADC1_CS 8
#define ADC2_CS 9
#define ADC3_CS 10

// ADCs
ADCChip adc1(ADC1_CS);
ADCChip adc2(ADC2_CS);
ADCChip adc3(ADC3_CS);

// ADC1
ADCSensor pdm_volt_sens(0, 0, 313);
ADCSensor      volt_ch1(1, 0, 313);
ADCSensor      volt_ch2(2, 0, 313);
ADCSensor      volt_ch3(3, 0, 313);
ADCSensor      volt_ch4(4, 0, 313);
ADCSensor      volt_ch5(5, 0, 313);
ADCSensor      volt_ch6(6, 0, 313);
ADCSensor      volt_ch7(7, 0, 313);

// ADC2
ADCSensor             volt_ch8(0, 0, 313);
ADCSensor brakelight_volt_sens(1, 2500, 40);
ADCSensor             Imon_ch1(2, 2500, 40);
ADCSensor             Imon_ch2(3, 2500, 40);
ADCSensor             Imon_ch3(4, 2500, 40);
ADCSensor             Imon_ch4(5, 2500, 40);
ADCSensor             Imon_ch5(6, 2500, 40);
ADCSensor             Imon_ch6(7, 2500, 40);

// ADC3
ADCSensor        Imon_ch7(0, 0, 313);
ADCSensor        Imon_ch8(1, 2500, 40);
ADCSensor        Imon_pdm(2, 2500, 40);
ADCSensor Imon_brakelight(3, 2500, 40);

// this function uses the local timers to determine when to call the ADCSensor sample function
void sample_ADCs(){

  // static timer definitions (keeps them in the local scope & never deleted)
  static EasyTimer sample_timer_1(2000); // 2,000Hz
  static EasyTimer sample_timer_2(1000); // 1,000Hz

  if (sample_timer_1.isup()){
    adc1.sample(pdm_volt_sens,volt_ch1,volt_ch2,volt_ch3,volt_ch4,volt_ch5,volt_ch6,volt_ch7);
    adc2.sample(volt_ch8,Imon_ch1,Imon_ch2,Imon_ch3,Imon_ch4,Imon_ch5,Imon_ch6);
    adc3.sample(Imon_ch7,Imon_ch8,Imon_pdm);
  }

  if (sample_timer_2.isup()){
    adc2.sample(brakelight_volt_sens);
    adc3.sample(Imon_brakelight);
  }
}


// this function must be called in the setup() portion of the main file.
// It initializes the pins for comunication
void initialize_ADCs()
{
  adc1.begin();
  adc2.begin();
  adc3.begin();
}
