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

// PAY ATTENTION TO RESISTOR TOLERANCES!! THEY MATTER!!
// Also don't forget about the cap impedance + tolerance stack

// ADC1
ADCSensor pdm_volt_sens(0, 0, 331); // voltage reading looks good
ADCSensor      volt_ch1(1, 0, 331); // atcc rear, transponder, inverter, energy meter
ADCSensor      volt_ch2(2, 0, 331); // water pumps, c50
ADCSensor      volt_ch3(3, 0, 331); // front boards
ADCSensor      volt_ch4(4, 0, 331); // unused
ADCSensor      volt_ch5(5, 0, 331); // acc fans, shutdown circuit
ADCSensor      volt_ch6(6, 0, 331); // vcu
ADCSensor      volt_ch7(7, 0, 331); // rad fans

// ADC2
ADCSensor             volt_ch8(0, 0, 331); // unused
ADCSensor brakelight_volt_sens(1, 0, 331); // voltage reading looks good
ADCSensor             Imon_ch1(2, 0, 50); // atcc rear, transponder, inverter, energy meter
ADCSensor             Imon_ch2(3, 0, 50); // water pumps, c50
ADCSensor             Imon_ch3(4, 0, 50); // front boards
ADCSensor             Imon_ch4(5, 0, 50); // unused
ADCSensor             Imon_ch5(6, 0, 50); // acc fans, shutdown circuit
ADCSensor             Imon_ch6(7, 0, 50); // vcu

// ADC3
ADCSensor        Imon_ch7(0, 0, 50); // rad fans
ADCSensor        Imon_ch8(1, 0, 50); // unused
ADCSensor        Imon_pdm(2, 2484, 19.46); // this calibration kinda sucks, looks good enough
ADCSensor Imon_brakelight(3, 2514, 166.67); // looks good enough

// this function uses the local timers to determine when to call the ADCSensor sample function
void sample_ADCs(){

  // static timer definitions (keeps them in the local scope & never deleted)
  static EasyTimer sample_timer_1(1000); // 1,000Hz
  // static EasyTimer sample_timer_2(1000); // 1,000Hz

  if (sample_timer_1.isup()){
    adc1.sample(pdm_volt_sens,volt_ch1,volt_ch2,volt_ch3,volt_ch4,volt_ch5,volt_ch6,volt_ch7);
    adc2.sample(volt_ch8,brakelight_volt_sens,Imon_ch1,Imon_ch2,Imon_ch3,Imon_ch4,Imon_ch5,Imon_ch6);
    adc3.sample(Imon_ch7, Imon_ch8, Imon_pdm, Imon_brakelight);
  }

  // if (sample_timer_2.isup()){
  //   adc2.sample(brakelight_volt_sens);
  //   adc3.sample(Imon_brakelight);
  // }
}


// this function must be called in the setup() portion of the main file.
// It initializes the pins for comunication
void initialize_ADCs()
{
  adc1.begin();
  adc2.begin();
  adc3.begin();
}
