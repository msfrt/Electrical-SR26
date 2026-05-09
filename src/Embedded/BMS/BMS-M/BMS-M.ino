#include "contactordriver.h"

#include <FlexCAN_T4.h>
#include <EasyTimer.h>
#include <BoardTemp.h>
#include <StateCAN.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"
#include "CAN/elcon.hpp"

#include "ReadADC.h"
#include <SPI.h>


#define NUM_RX_STD_MAILBOXES 32
#define NUM_RX_EXT_MAILBOXES 2
#define NUM_TX_MAILBOXES 30
#define MAX_CAN_FRAME_READ_PER_CYCLE 5  // Limit per loop iteration
#define BMS_STATUS_SWITCH 9 


int IS_CHARGING = 1;  // 0 = not charging, 1 = charging, temporary


// CAN Bus Declaration
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can3;
static CAN_message_t rxmsg;

#include "can_send.hpp"

int val =0;




ADCChip adc1(10);
ADCSensor sens0(0, 0, 1);
ADCSensor sens1(1, 0, 1);
ADCSensor sens2(2, 0, 1);
ADCSensor sens3(3, 0, 1);

void setup(){
  // Initialize serial communication
    disableAllCont();
    Serial.begin(112500);

    // initialize SPI communication
    SPI.begin();

    // initialize ADCs
    adc1.begin();

    //initialize the CAN Bus and set its baud rate to 1Mb
    can1.begin();
    can1.setBaudRate(500000);
    can2.begin();
    can2.setBaudRate(1000000);
    can3.begin();
    can3.setBaudRate(250000);
    set_mailboxes();
    digitalWrite(BMS_STATUS_SWITCH, HIGH);
    //contactorInit();
    //runDischarge(); 
    //runPrecharge(); 
    //enableAirPlus();
    //digitalWrite(2, HIGH);
    //digitalWrite(EN1_2, HIGH);
    // digitalWrite(7, HIGH);
    // digitalWrite(4, HIGH);    
    //digitalWrite(29, HIGH);  
    if (IS_CHARGING = 1) { // close contactors early before sending CAN to charger
        runOperational();
        delay(1000);
    }
}


void loop(){

    adc1.sample(sens0, sens1, sens2, sens3); // read TS current sensor 

    switch(IS_CHARGING){
        case 1:
            runOperational();
            delay(1000); // send every 1sec
            send_BMS_1806E5F4();
            break;
        
        case 0:
            read_CAN();
            if (VCU_vehicleState.can_value() == 0) {
                printf("VCU-ShifterState = 0\n");
                runDischarge();
            } else if(VCU_vehicleState.can_value() == 1){
                printf("VCU-ShifterState = 1\n");
                runPrecharge();
            } else if(VCU_vehicleState.can_value() == 2){
                printf("VCU-ShifterState = 2\n");
                runOperational();
            } else if(VCU_vehicleState.can_value() == 3){
                printf("VCU-ShifterState = 3\n");
                runOperational();
            } else if(VCU_vehicleState.can_value() == 4){
                printf("VCU-ShifterState = 4\n");
                runDischarge();
            } else if(VCU_vehicleState.can_value() == 5){
                printf("VCU-ShifterState = 5\n");
                runDischarge();
            } else if(VCU_vehicleState.can_value() == 6){
                printf("VCU-ShifterState = 6\n");
                runDischarge();
            } 
            break;
    }

    // read_CAN();
    // if (VCU_vehicleState.can_value() == 0) {
    //     printf("VCU-ShifterState = 0\n");
    //     runDischarge();
    // } else if(VCU_vehicleState.can_value() == 1){
    //     printf("VCU-ShifterState = 1\n");
    //     runPrecharge();
    // } else if(VCU_vehicleState.can_value() == 2){
    //     printf("VCU-ShifterState = 2\n");
    //     runOperational();
    // } else if(VCU_vehicleState.can_value() == 3){
    //     printf("VCU-ShifterState = 3\n");
    //     runOperational();
    // } else if(VCU_vehicleState.can_value() == 4){
    //     printf("VCU-ShifterState = 4\n");
    //     runDischarge();
    // } else if(VCU_vehicleState.can_value() == 5){
    //     printf("VCU-ShifterState = 5\n");
    //     runDischarge();
    // } else if(VCU_vehicleState.can_value() == 6){
    //     printf("VCU-ShifterState = 6\n");
    //     runDischarge();
    // } 

    //Serial.println(VCU_vehicleState.can_value());
    //else {
    //     runDischarge();
    // }

}

void set_mailboxes() {
    can2.setMaxMB(64);
    can2.enableFIFO();
    can2.setMB(MB4, RX, STD);
    can2.setMB(MB5, RX, STD);
    can2.setMB(MB6, RX, STD);
    can2.setMB(MB7, RX, STD);
    can2.setMB(MB8, RX, STD);
    can2.setMB(MB9, RX, STD);
    can2.setMB(MB10, RX, STD);
    can2.setMB(MB11, RX, STD);
    can2.setMB(MB12, RX, EXT);
    can2.setMB(MB13, RX, EXT);
    can2.setMB(MB14, RX, EXT);
    can2.setMB(MB15, RX, EXT);

    can3.setMaxMB(64);
    can3.enableFIFO();
    can3.setMB(MB4, RX, STD);
    can3.setMB(MB5, RX, STD);
    can3.setMB(MB6, RX, STD);
    can3.setMB(MB7, RX, STD);
    can3.setMB(MB8, RX, STD);
    can3.setMB(MB9, RX, STD);
    can3.setMB(MB10, RX, STD);
    can3.setMB(MB11, RX, STD);
    can3.setMB(MB12, RX, EXT);
    can3.setMB(MB13, RX, EXT);
    can3.setMB(MB14, RX, EXT);
    can3.setMB(MB15, RX, EXT);
}

void read_CAN() {
    int count = 0;
    count = 0;

    while (can1.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
        decode_raptor_CAN1(rxmsg);
        count++;
    }

    while (can2.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
        decode_SR26_CAN2(rxmsg);
        count++;
    }
        while (can3.read(rxmsg) && count < MAX_CAN_FRAME_READ_PER_CYCLE) {
        decode_elcon(rxmsg);
        count++;
    }
}

// void contactorStage(int case){
//     switch (case){
//         case 1: // precharge
//         runPrecharge();
//         break;
//         case 2:
        

//     }
// }
