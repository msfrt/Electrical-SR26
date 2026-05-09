#ifndef CAN_SEND_ATCC_HPP
#define CAN_SEND_ATCC_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN2.hpp"

#include "sensors.hpp"

static CAN_message_t msg;

// accounts for 50% of rotor being slots
float voltage_to_rotor_temp(float voltage){
    return pow((0.5*pow((25+273),4)+0.5*pow((voltage+273),4)), (1/4));
}

float voltage_to_sus_pot_val(float voltage){
  return map(voltage, 0, 5, 0, 150);;
}


// message definitions below
void send_ATCC_200(){
  static StateCounter ctr;

  msg.id = 200;
  msg.len = 8;

  ATCCR_boardTemp = 0; //board_temp.value();
  ATCCR_teensyTemp = tempmonGetTemp();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCR_boardTemp.can_value();
  msg.buf[3] = ATCCR_boardTemp.can_value() >> 8;
  msg.buf[4] = ATCCR_teensyTemp.can_value();
  msg.buf[5] = ATCCR_teensyTemp.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1 */

void send_ATCC_201(){
  static StateCounter ctr;

  msg.id = 201;
  msg.len = 8;

  ATCCR_wheelSpeedRR = ATCCR_wheelSpeedRR.value();
  ATCCR_wheelSpeedRL = ATCCR_wheelSpeedRL.value();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCR_wheelSpeedRR.can_value();
  msg.buf[3] = ATCCR_wheelSpeedRR.can_value() >> 8;
  msg.buf[4] = ATCCR_wheelSpeedRR.can_value();
  msg.buf[5] = ATCCR_wheelSpeedRR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1

void send_ATCC_208(){
  static StateCounter ctr;
  //Serial.println("sendingATCC208");

  msg.id = 208;
  msg.len = 8;

  ATCCR_susPot_RL = voltage_to_sus_pot_val(SusPotRL.avg()); //voltage_to_NTC_M12_H_temp(ATCC_coolantTempMotorIn.avg());
  ATCCR_susPot_RR = voltage_to_sus_pot_val(SusPotRR.avg()); //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterIn.avg());
  
  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCCR_susPot_RR.can_value();
  msg.buf[3] = ATCCR_susPot_RR.can_value() >> 8;
  msg.buf[4] = ATCCR_susPot_RL.can_value();
  msg.buf[5] = ATCCR_susPot_RL.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
}

/*
void send_ATCC_302(){
  static StateCounter ctr;

  msg.id = 302;
  msg.len = 8;

  ATCC_angularWheelFreqRL = ATCC_angularWheelFreqFL.value();
  ATCC_angularWheelFreqRR = ATCC_angularWheelFreqFR.value();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_angularWheelFreqRL.can_value();
  msg.buf[3] = ATCC_angularWheelFreqRL.can_value() >> 8;
  msg.buf[4] = ATCC_angularWheelFreqRR.can_value();
  msg.buf[5] = ATCC_angularWheelFreqRR.can_value() >> 8;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can1.write(msg);
} // can1 */

/*
void send_ATCC_303(){
  static StateCounter ctr;
  Serial.println("sendingATCC303");

  msg.id = 302;
  msg.len = 8;

  ATCC_coolantTempMotorIn = 0; //voltage_to_NTC_M12_H_temp(ATCC_coolantTempMotorIn.avg());
  ATCC_coolantTempInverterIn = 0; //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterIn.avg());
  ATCC_coolantTempInverterOut = 0; //voltage_to_NTC_M12_H_temp(ATCC_coolantTempInverterOut.avg());

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = ATCC_coolantTempMotorIn.can_value();
  msg.buf[3] = ATCC_coolantTempMotorIn.can_value() >> 8;
  msg.buf[4] = ATCC_coolantTempInverterIn.can_value();
  msg.buf[5] = ATCC_coolantTempInverterIn.can_value() >> 8;
  msg.buf[6] = ATCC_coolantTempInverterIn.can_value();
  msg.buf[7] = ATCC_coolantTempInverterIn.can_value() >> 8;

  can1.write(msg);
} */

void send_can1(){

  static EasyTimer ATCC_200_timer(10); // 10hz
  if (ATCC_200_timer.isup()){
    send_ATCC_200();
  } 

  static EasyTimer ATCC_201_timer(10); // 10 Hz
  if (ATCC_201_timer.isup()){
    send_ATCC_201();
  }

  static EasyTimer ATCC_208_timer(100); // 100 Hz
  if (ATCC_208_timer.isup()){
    send_ATCC_208();
  }

  /*
  static EasyTimer ATCC_302_timer(1); // 200Hz
  if (ATCC_302_timer.isup()){
    send_ATCC_302();
  } */

}

#endif
