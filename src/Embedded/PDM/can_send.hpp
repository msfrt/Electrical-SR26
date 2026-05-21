#ifndef CAN_MESSAGES_HPP
#define CAN_MESSAGES_HPP

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include "CAN/SR26_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"


// external definitions
// extern int OBDFLAG_oil_pressure;
// extern int OBDFLAG_oil_temp;
// extern int OBDFLAG_fuel_pressure;

static CAN_message_t msg;

// send message definitions

void send_PDM_400() {
  static StateCounter ctr;
  msg.id = 400;
  msg.len = 8;

  PDM_teensyTemp = tempmonGetTemp(); // built-in teensy function;

  // Serial.println("Msg 400 Sent");

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_teensyTemp.can_value();
  msg.buf[3] = 0;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  // should have cooling button go direct to PDM in the future I think

  can2.write(msg);
}

void send_PDM_401() {
  static StateCounter ctr;
  msg.id = 401;
  msg.len = 8;

  PDM_pdmCurrentAvg = Imon_pdm.avg();
  PDM_pdmCurrentMax = Imon_pdm.max();
  PDM_pdmCurrentMin = Imon_pdm.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_pdmCurrentAvg.can_value();
  msg.buf[3] = PDM_pdmCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_pdmCurrentMax.can_value();
  msg.buf[5] = PDM_pdmCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_pdmCurrentMin.can_value();
  msg.buf[7] = PDM_pdmCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_402() {
  static StateCounter ctr;
  msg.id = 402;
  msg.len = 8;

  PDM_pdmVoltAvg = pdm_volt_sens.avg();
  PDM_pdmVoltMax = pdm_volt_sens.max();
  PDM_pdmVoltMin = pdm_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_pdmVoltAvg.can_value();
  msg.buf[3] = PDM_pdmVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_pdmVoltMax.can_value();
  msg.buf[5] = PDM_pdmVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_pdmVoltMin.can_value();
  msg.buf[7] = PDM_pdmVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_403() {
  static StateCounter ctr;
  msg.id = 403;
  msg.len = 8;

  PDM_ch1CurrentAvg = Imon_ch1.avg();
  PDM_ch1CurrentMax = Imon_ch1.max();
  PDM_ch1CurrentMin = Imon_ch1.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch1CurrentAvg.can_value();
  msg.buf[3] = PDM_ch1CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch1CurrentMax.can_value();
  msg.buf[5] = PDM_ch1CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch1CurrentMin.can_value();
  msg.buf[7] = PDM_ch1CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_404() {
  static StateCounter ctr;
  msg.id = 404;
  msg.len = 8;

  PDM_ch1VoltAvg = volt_ch1.avg();
  PDM_ch1VoltMax = volt_ch1.max();
  PDM_ch1VoltMin = volt_ch1.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch1VoltAvg.can_value();
  msg.buf[3] = PDM_ch1VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch1VoltMax.can_value();
  msg.buf[5] = PDM_ch1VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch1VoltMin.can_value();
  msg.buf[7] = PDM_ch1VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_405() {
  static StateCounter ctr;
  msg.id = 405;
  msg.len = 8;

  PDM_ch2CurrentAvg = Imon_ch2.avg();
  PDM_ch2CurrentMax = Imon_ch2.max();
  PDM_ch2CurrentMin = Imon_ch2.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch2CurrentAvg.can_value();
  msg.buf[3] = PDM_ch2CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch2CurrentMax.can_value();
  msg.buf[5] = PDM_ch2CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch2CurrentMin.can_value();
  msg.buf[7] = PDM_ch2CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_406() {
  static StateCounter ctr;
  msg.id = 406;
  msg.len = 8;

  PDM_ch2VoltAvg = volt_ch2.avg();
  PDM_ch2VoltMax = volt_ch2.max();
  PDM_ch2VoltMin = volt_ch2.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch2VoltAvg.can_value();
  msg.buf[3] = PDM_ch2VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch2VoltMax.can_value();
  msg.buf[5] = PDM_ch2VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch2VoltMin.can_value();
  msg.buf[7] = PDM_ch2VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_407() {
  static StateCounter ctr;
  msg.id = 407;
  msg.len = 8;

  PDM_ch3CurrentAvg = Imon_ch3.avg();
  PDM_ch3CurrentMax = Imon_ch3.max();
  PDM_ch3CurrentMin = Imon_ch3.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch3CurrentAvg.can_value();
  msg.buf[3] = PDM_ch3CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch3CurrentMax.can_value();
  msg.buf[5] = PDM_ch3CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch3CurrentMin.can_value();
  msg.buf[7] = PDM_ch3CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_408() {
  static StateCounter ctr;
  msg.id = 408;
  msg.len = 8;

  PDM_ch3VoltAvg = volt_ch3.avg();
  PDM_ch3VoltMax = volt_ch3.max();
  PDM_ch3VoltMin = volt_ch3.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch3VoltAvg.can_value();
  msg.buf[3] = PDM_ch3VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch3VoltMax.can_value();
  msg.buf[5] = PDM_ch3VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch3VoltMin.can_value();
  msg.buf[7] = PDM_ch3VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_409() {
  static StateCounter ctr;
  msg.id = 409;
  msg.len = 8;

  PDM_ch4CurrentAvg = Imon_ch4.avg();
  PDM_ch4CurrentMax = Imon_ch4.max();
  PDM_ch4CurrentMin = Imon_ch4.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch4CurrentAvg.can_value();
  msg.buf[3] = PDM_ch4CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch4CurrentMax.can_value();
  msg.buf[5] = PDM_ch4CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch4CurrentMin.can_value();
  msg.buf[7] = PDM_ch4CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_410() {
  static StateCounter ctr;
  msg.id = 410;
  msg.len = 8;

  PDM_ch4VoltAvg = volt_ch4.avg();
  PDM_ch4VoltMax = volt_ch4.max();
  PDM_ch4VoltMin = volt_ch4.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch4VoltAvg.can_value();
  msg.buf[3] = PDM_ch4VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch4VoltMax.can_value();
  msg.buf[5] = PDM_ch4VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch4VoltMin.can_value();
  msg.buf[7] = PDM_ch4VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_411() {
  static StateCounter ctr;
  msg.id = 411;
  msg.len = 8;

  PDM_ch5CurrentAvg = Imon_ch5.avg();
  PDM_ch5CurrentMax = Imon_ch5.max();
  PDM_ch5CurrentMin = Imon_ch5.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch5CurrentAvg.can_value();
  msg.buf[3] = PDM_ch5CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch5CurrentMax.can_value();
  msg.buf[5] = PDM_ch5CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch5CurrentMin.can_value();
  msg.buf[7] = PDM_ch5CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_412() {
  static StateCounter ctr;
  msg.id = 412;
  msg.len = 8;

  PDM_ch5VoltAvg = volt_ch5.avg();
  PDM_ch5VoltMax = volt_ch5.max();
  PDM_ch5VoltMin = volt_ch5.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch5VoltAvg.can_value();
  msg.buf[3] = PDM_ch5VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch5VoltMax.can_value();
  msg.buf[5] = PDM_ch5VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch5VoltMin.can_value();
  msg.buf[7] = PDM_ch5VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_413() {
  static StateCounter ctr;
  msg.id = 413;
  msg.len = 8;

  PDM_ch6CurrentAvg = Imon_ch6.avg();
  PDM_ch6CurrentMax = Imon_ch6.max();
  PDM_ch6CurrentMin = Imon_ch6.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch6CurrentAvg.can_value();
  msg.buf[3] = PDM_ch6CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch6CurrentMax.can_value();
  msg.buf[5] = PDM_ch6CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch6CurrentMin.can_value();
  msg.buf[7] = PDM_ch6CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_414() {
  static StateCounter ctr;
  msg.id = 414;
  msg.len = 8;

  PDM_ch6VoltAvg = volt_ch6.avg();
  PDM_ch6VoltMax = volt_ch6.max();
  PDM_ch6VoltMin = volt_ch6.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch6VoltAvg.can_value();
  msg.buf[3] = PDM_ch6VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch6VoltMax.can_value();
  msg.buf[5] = PDM_ch6VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch6VoltMin.can_value();
  msg.buf[7] = PDM_ch6VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_415() {
  static StateCounter ctr;
  msg.id = 415;
  msg.len = 8;

  PDM_ch7CurrentAvg = Imon_ch7.avg();
  PDM_ch7CurrentMax = Imon_ch7.max();
  PDM_ch7CurrentMin = Imon_ch7.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch7CurrentAvg.can_value();
  msg.buf[3] = PDM_ch7CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch7CurrentMax.can_value();
  msg.buf[5] = PDM_ch7CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch7CurrentMin.can_value();
  msg.buf[7] = PDM_ch7CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_416() {
  static StateCounter ctr;
  msg.id = 416;
  msg.len = 8;

  PDM_ch7VoltAvg = volt_ch7.avg();
  PDM_ch7VoltMax = volt_ch7.max();
  PDM_ch7VoltMin = volt_ch7.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch7VoltAvg.can_value();
  msg.buf[3] = PDM_ch7VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch7VoltMax.can_value();
  msg.buf[5] = PDM_ch7VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch7VoltMin.can_value();
  msg.buf[7] = PDM_ch7VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_417() {
  static StateCounter ctr;
  msg.id = 417;
  msg.len = 8;

  PDM_ch8CurrentAvg = Imon_ch8.avg();
  PDM_ch8CurrentMax = Imon_ch8.max();
  PDM_ch8CurrentMin = Imon_ch8.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch8CurrentAvg.can_value();
  msg.buf[3] = PDM_ch8CurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch8CurrentMax.can_value();
  msg.buf[5] = PDM_ch8CurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_ch8CurrentMin.can_value();
  msg.buf[7] = PDM_ch8CurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_418() {
  static StateCounter ctr;
  msg.id = 418;
  msg.len = 8;

  PDM_ch8VoltAvg = volt_ch8.avg();
  PDM_ch8VoltMax = volt_ch8.max();
  PDM_ch8VoltMin = volt_ch8.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_ch8VoltAvg.can_value();
  msg.buf[3] = PDM_ch8VoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_ch8VoltMax.can_value();
  msg.buf[5] = PDM_ch8VoltMax.can_value() >> 8;
  msg.buf[6] = PDM_ch8VoltMin.can_value();
  msg.buf[7] = PDM_ch8VoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_419() {
  static StateCounter ctr;
  msg.id = 419;
  msg.len = 8;

  PDM_brakelightCurrentAvg = Imon_brakelight.avg();
  PDM_brakelightCurrentMax = Imon_brakelight.max();
  PDM_brakelightCurrentMin = Imon_brakelight.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_brakelightCurrentAvg.can_value();
  msg.buf[3] = PDM_brakelightCurrentAvg.can_value() >> 8;
  msg.buf[4] = PDM_brakelightCurrentMax.can_value();
  msg.buf[5] = PDM_brakelightCurrentMax.can_value() >> 8;
  msg.buf[6] = PDM_brakelightCurrentMin.can_value();
  msg.buf[7] = PDM_brakelightCurrentMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_420() {
  static StateCounter ctr;
  msg.id = 420;
  msg.len = 8;

  PDM_brakelightVoltAvg = brakelight_volt_sens.avg();
  PDM_brakelightVoltMax = brakelight_volt_sens.max();
  PDM_brakelightVoltMin = brakelight_volt_sens.min();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_brakelightVoltAvg.can_value();
  msg.buf[3] = PDM_brakelightVoltAvg.can_value() >> 8;
  msg.buf[4] = PDM_brakelightVoltMax.can_value();
  msg.buf[5] = PDM_brakelightVoltMax.can_value() >> 8;
  msg.buf[6] = PDM_brakelightVoltMin.can_value();
  msg.buf[7] = PDM_brakelightVoltMin.can_value() >> 8;

  can2.write(msg);
}

void send_PDM_421(){
  static StateCounter ctr;
  msg.id = 421;
  msg.len = 8;

  PDM_fanLeftDutyCycle = fan_left.actual();
  PDM_fanRightDutyCycle = fan_right.actual();
  PDM_wp1DutyCycle = water_pump1.actual();
  PDM_wp2DutyCycle = water_pump2.actual();

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = PDM_fanLeftDutyCycle.can_value();
  msg.buf[3] = PDM_fanRightDutyCycle.can_value();
  msg.buf[4] = PDM_wp1DutyCycle.can_value();
  msg.buf[5] = PDM_wp2DutyCycle.can_value();
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_PDM_422(){
  msg.id = 422;
  msg.len = 8;

  auto time = millis();
  msg.buf[1] = time;
  msg.buf[2] = time >> 8;
  msg.buf[3] = time >> 16;
  msg.buf[4] = time >> 24;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  can2.write(msg);
}

void send_can2(){

  static EasyTimer PDM_400_timer(10); // 10Hz
  if (PDM_400_timer.isup()){
    send_PDM_400();
  }

  static EasyTimer PDM_401_timer(10); // 10Hz
  if (PDM_401_timer.isup()){
    send_PDM_401();
  }

  static EasyTimer PDM_402_timer(10); // 10Hz
  if (PDM_402_timer.isup()){
    send_PDM_402();
  }

  static EasyTimer PDM_403_timer(10); // 10Hz
  if (PDM_403_timer.isup()){
    send_PDM_403();
  }

  static EasyTimer PDM_404_timer(10); // 10Hz
  if (PDM_404_timer.isup()){
    send_PDM_404();
  }

  static EasyTimer PDM_405_timer(10); // 10Hz
  if (PDM_405_timer.isup()){
    send_PDM_405();
  }

  static EasyTimer PDM_406_timer(10); // 10Hz
  if (PDM_406_timer.isup()){
    send_PDM_406();
  }

  static EasyTimer PDM_407_timer(10); // 10Hz
  if (PDM_407_timer.isup()){
    send_PDM_407();
  }

  static EasyTimer PDM_408_timer(10); // 10Hz
  if (PDM_408_timer.isup()){
    send_PDM_408();
  }

  static EasyTimer PDM_409_timer(10); // 10Hz
  if (PDM_409_timer.isup()){
    send_PDM_409();
  }

  static EasyTimer PDM_410_timer(10); // 10Hz
  if (PDM_410_timer.isup()){
    send_PDM_410();
  }

  static EasyTimer PDM_411_timer(10); // 10Hz
  if (PDM_411_timer.isup()){
    send_PDM_411();
  }

  static EasyTimer PDM_412_timer(10); // 10Hz
  if (PDM_412_timer.isup()){
    send_PDM_412();
  }

  static EasyTimer PDM_413_timer(10); // 10Hz
  if (PDM_413_timer.isup()){
    send_PDM_413();
  }

  static EasyTimer PDM_414_timer(10); // 10Hz
  if (PDM_414_timer.isup()){
    send_PDM_414();
  }

  static EasyTimer PDM_415_timer(10); // 10Hz
  if (PDM_415_timer.isup()){
    send_PDM_415();
  }

  static EasyTimer PDM_416_timer(10); // 10Hz
  if (PDM_416_timer.isup()){
    send_PDM_416();
  }

  static EasyTimer PDM_417_timer(10); // 10Hz
  if (PDM_417_timer.isup()){
    send_PDM_417();
  }

  static EasyTimer PDM_418_timer(10); // 10Hz
  if (PDM_418_timer.isup()){
    send_PDM_418();
  }

  static EasyTimer PDM_419_timer(10); // 10Hz
  if (PDM_419_timer.isup()){
    send_PDM_419();
  }

  static EasyTimer PDM_420_timer(10); // 10Hz
  if (PDM_420_timer.isup()){
    send_PDM_420();
  }

  static EasyTimer PDM_421_timer(100); // 100Hz
  if (PDM_421_timer.isup()){
    send_PDM_421();
  }

  static EasyTimer PDM_422_timer(10); // 10Hz
  if (PDM_422_timer.isup()){
    send_PDM_422();
  }

}

#endif
