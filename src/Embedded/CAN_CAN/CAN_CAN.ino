#ifndef CAN_CAN
#define CAN_CAN

#include <Adafruit_NeoPixel.h>
#include <BoardTemp.h>
#include <EasyTimer.h>
#include <FlexCAN_T4.h>
#include <StateCAN.h>

#include "Adafruit_GFX.h"
#include "ILI9341_t3n.h"
#include "SPI.h"
#include<string>
using std::string;
#define SPI0_DISP1

// CAN Bus Declaration
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
static CAN_message_t rxmsg;
static CAN_message_t msg;

#define NUM_RX_STD_MAILBOXES 32
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 30
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration

// CAN Message Definitions
#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

void setup() {
  // Initialize serial communication
  Serial.begin(112500);

  can1.begin();
  can1.setBaudRate(500000);
  can2.begin();
  can2.setBaudRate(1000000);
  set_mailboxes();

  // initialize SPI communication
  SPI.begin();
}

void loop() {
  readCan();

  // read any incoming CAN messages
  //Serial.println("Reading CAN:");
  can1.events();
  send_can();
}

void set_mailboxes() {
  // to view mailbox status, you can use the member function mailboxStatus().
  // Don't put it in a fast loop, though, because you may actually affect how
  // the chips moves things around

  can1.setMaxMB(64);  // use all mailboxes of course
  can2.setMaxMB(64);

  for (int i = 0; i < NUM_RX_STD_MAILBOXES; i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, STD);
    can2.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_STD_MAILBOXES;
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES); i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
    can2.setMB((FLEXCAN_MAILBOX)i, RX, EXT);
  }
  for (int i = (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES);
       i < (NUM_RX_STD_MAILBOXES + NUM_RX_EXT_MAILBOXES + NUM_TX_MAILBOXES);
       i++) {
    can1.setMB((FLEXCAN_MAILBOX)i, TX, STD);
    can2.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }

  // be sure to assign at least one mailbox to each message that you want to
  // read. filtering allows us to avoid using clock cycles to read messages that
  // we have no interest in. it also reserves a slot for messages as they are
  // recieved.
  can1.setMBFilter(REJECT_ALL);
  can1.setMBFilter(MB0, C50_gpsSpeed.get_msg_id());
  can1.setMBFilter(MB1, PM_motorSpeed.get_msg_id());
  can1.setMBFilter(MB2, PM_motorTemp.get_msg_id());
  can1.setMBFilter(MB3, PM_dcBusVolt.get_msg_id());
  can1.setMBFilter(MB4, PM_commandedTorque.get_msg_id());
  can1.setMBFilter(MB5, VCU_radFanLDuty.get_msg_id());
  can1.setMBFilter(MB6, VCU_radFanRDuty.get_msg_id());
  can1.setMBFilter(MB7, ATCC_angularWheelFreqRR.get_msg_id());
  can1.setMBFilter(MB8, ATCC_coolantTempInverterOut.get_msg_id());
  can1.setMBFilter(MB9, ATCC_coolantTempInverterIn.get_msg_id());
  can1.setMBFilter(MB10, ATCC_coolantTempMotorIn.get_msg_id());
  can1.setMBFilter(MB11, 0);
  can1.setMBFilter(MB12, 0);
  can1.setMBFilter(MB13, 0);
  can1.setMBFilter(MB14, 0);

  can2.setMBFilter(REJECT_ALL);
  can2.setMBFilter(MB0, BMS_packVolt.get_msg_id());
  can2.setMBFilter(MB1, BMS_packCurr.get_msg_id());
  can2.setMBFilter(MB2, VCU_brakePressureF.get_msg_id());
  can2.setMBFilter(MB3, VCU_brakePressureR.get_msg_id()); 
  can2.setMBFilter(MB4, PDM_fanRightDutyCycle.get_msg_id());
  can2.setMBFilter(MB5, PDM_fanLeftDutyCycle.get_msg_id());
  can2.setMBFilter(MB6, PDM_pdmVoltAvg.get_msg_id());
  can2.setMBFilter(MB7, STMM_seg3ThermValAvg.get_msg_id());
  can2.setMBFilter(MB8, VCU_brakeBias.get_msg_id());
  can2.setMBFilter(MB9, VCU_driveSpeed.get_msg_id());
  can2.setMBFilter(MB10, BMS_maxCellVolt.get_msg_id());
  can2.setMBFilter(MB11, VCU_ShifterState.get_msg_id());
  can2.setMBFilter(MB12, 0);
  can2.setMBFilter(MB13, 0);
  can2.setMBFilter(MB14, 0);
}

void readCan() {
  int count = 0;
  while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN1(rxmsg);
    count++;
  }

  count = 0;
  while (can2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
    decode_raptor_CAN2(rxmsg);
    count++;
  }
}

void send_PDM_401() {
  Serial.println("reading can 1");
  static StateCounter ctr;
  msg.id = 160;
  msg.len = 8;

  msg.buf[0] = ctr.value();
  msg.buf[1] = 0;
  msg.buf[2] = 1;
  msg.buf[3] = 1;
  msg.buf[4] = 1;
  msg.buf[5] = 1;
  msg.buf[6] = 1;
  msg.buf[7] = 1;

  can1.write(msg);
}

void send_can() {
  static EasyTimer PDM_401_timer(1); // 100Hz
  if (PDM_401_timer.isup()){
    send_PDM_401();
  }
}

#endif