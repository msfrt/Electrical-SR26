#include "contactordriver.h"

#include <FlexCAN_T4.h>
#include <EasyTimer.h>

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

#define PACK_VOLTAGE_UPPER_LIMIT 378 // 4.2V for all 90 cells
#define PACK_VOLTAGE_LOWER_LIMIT 225 // 2.5V for all 90 cells

bool CHARGING = false;
bool VALID_VOLTAGE_RANGE = false;

// CAN Bus Declaration
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can3;
static CAN_message_t rxmsg;

#include "can_send.hpp"

int val = 0;

//adc declaration
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

    //initialize the CAN Busses
    can1.begin();
    can1.setBaudRate(500000);
    can2.begin();
    can2.setBaudRate(1000000);
    can3.begin();
    can3.setBaudRate(250000);
    set_mailboxes();

    // BMS status should update with battery voltage and temperature
    digitalWrite(BMS_STATUS_SWITCH, HIGH); // set BMS status good

}

void loop(){

    adc1.sample(sens0, sens1, sens2, sens3); // read TS current sensor 

    read_CAN();

    checkAllBatterySafetyLimits();

    /////////////// CHARGING FLAG /////////////////
    if (OutputVoltage.value() <= PACK_VOLTAGE_UPPER_LIMIT && 
        OutputVoltage.value() >= PACK_VOLTAGE_LOWER_LIMIT){
        
        VALID_VOLTAGE_RANGE = true;
    } else {
        VALID_VOLTAGE_RANGE = false;
    }

    if (VCU_vehicleState.can_value() == 0 && VALID_VOLTAGE_RANGE){
        CHARGING = true;
    } else {
        CHARGING = false;
    }
    /////////////// CHARGING FLAG /////////////////

    ///////////// CONTACTOR STATES ///////////////
    if (VCU_vehicleState.can_value() == 0) {
        if (CHARGING){
            runOperational();
        } else {
            runDischarge();
        }
    } else if(VCU_vehicleState.can_value() == 1){
        runPrecharge();
    } else if(VCU_vehicleState.can_value() == 2){
        runOperational();
    } else if(VCU_vehicleState.can_value() == 3){
        runOperational();
    } else if(VCU_vehicleState.can_value() == 4){
        runDischarge();
    } else if(VCU_vehicleState.can_value() == 5){
        runDischarge();
    } else if(VCU_vehicleState.can_value() == 6){
        runDischarge();
    }
    ///////////// CONTACTOR STATES ///////////////

    sumPackVoltage();
    send_can2(); // summed info CANbus
    send_can3(); // charger CANbus
    
}

void set_mailboxes() {

    // should implement a mailbox on CAN1

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

void sumPackVoltage(){
    float module1Volt = 0;
    float module2Volt = 0;
    float module3Volt = 0;
    float module4Volt = 0;
    float module5Volt = 0;
    float PackVoltage = 0;

    module1Volt = BMS_module1voltageBMSS.can_value();
    module2Volt = BMS_module2voltageBMSS.can_value();
    module3Volt = BMS_module3voltageBMSS.can_value();
    module4Volt = BMS_module4voltageBMSS.can_value();
    module5Volt = BMS_module5voltageBMSS.can_value();

    PackVoltage = module1Volt + module2Volt + module3Volt + module4Volt + module5Volt;

    //set pack voltage for CAN
    BMS_packmVoltage = PackVoltage;
    //set pack SOC for CAN
    BMS_packSOC = get_battery_percentage(PackVoltage);

}

float get_battery_percentage(float voltage) {
    // Look-up table based on graph: {Voltage, Percentage}

    typedef struct {
        float v;
        float p;
    } CurvePoint;

    static const CurvePoint lut[] = {
        {369.0f, 100.0f},
        {360.0f, 95.0f},
        {358.2f, 90.0f},
        {356.4f, 85.0f},
        {354.6f, 80.0f},
        {346.5f, 75.0f},
        {344.7f, 70.0f},
        {342.0f, 65.0f},
        {338.4f, 60.0f},
        {333.9f, 55.0f},
        {330.3f, 50.0f},
        {324.9f, 45.0f},
        {321.3f, 40.0f},
        {316.8f, 35.0f},
        {314.1f, 30.0f},
        {309.6f, 25.0f},
        {304.2f, 20.0f},
        {299.7f, 15.0f},
        {284.4f, 10.0f},
        {256.5f, 5.0f}, // End of visible curve line
    };
    
    const int numPoints = sizeof(lut) / sizeof(lut[0]);

    // Handle out-of-bounds
    if (voltage >= lut[0].v) return 100.0f;
    
    // Handle out-of-bounds
    if (voltage <= lut[numPoints - 1].v) return 0.0f;

    // Linear Interpolation
    for (int i = 0; i < numPoints - 1; i++) {
        // Find the segment the voltage falls into
        if (voltage <= lut[i].v && voltage > lut[i+1].v) {
            float v_high = lut[i].v;
            float v_low  = lut[i+1].v;
            float p_high = lut[i].p;
            float p_low  = lut[i+1].p;

            // Calculate interpolation
            return p_low + (voltage - v_low) * (p_high - p_low) / (v_high - v_low);
        }
    }

    return 0.0f;
}


void checkAllBatterySafetyLimits() {
    bool faultDetected = false;

    // Array of all 90 cell voltage signals
    StateSignal* allCellVolts[] = {
        // Module 1
        &BMS_module1Cell1Volt, &BMS_module1Cell2Volt, &BMS_module1Cell3Volt, &BMS_module1Cell4Volt, &BMS_module1Cell5Volt, &BMS_module1Cell6Volt,
        &BMS_module1Cell7Volt, &BMS_module1Cell8Volt, &BMS_module1Cell9Volt, &BMS_module1Cell10Volt, &BMS_module1Cell11Volt, &BMS_module1Cell12Volt,
        &BMS_module1Cell13Volt, &BMS_module1Cell14Volt, &BMS_module1Cell15Volt, &BMS_module1Cell16Volt, &BMS_module1Cell17Volt, &BMS_module1Cell18Volt,
        // Module 2
        &BMS_module2Cell1Volt, &BMS_module2Cell2Volt, &BMS_module2Cell3Volt, &BMS_module2Cell4Volt, &BMS_module2Cell5Volt, &BMS_module2Cell6Volt,
        &BMS_module2Cell7Volt, &BMS_module2Cell8Volt, &BMS_module2Cell9Volt, &BMS_module2Cell10Volt, &BMS_module2Cell11Volt, &BMS_module2Cell12Volt,
        &BMS_module2Cell13Volt, &BMS_module2Cell14Volt, &BMS_module2Cell15Volt, &BMS_module2Cell16Volt, &BMS_module2Cell17Volt, &BMS_module2Cell18Volt,
        // Module 3
        &BMS_module3Cell1Volt, &BMS_module3Cell2Volt, &BMS_module3Cell3Volt, &BMS_module3Cell4Volt, &BMS_module3Cell5Volt, &BMS_module3Cell6Volt,
        &BMS_module3Cell7Volt, &BMS_module3Cell8Volt, &BMS_module3Cell9Volt, &BMS_module3Cell10Volt, &BMS_module3Cell11Volt, &BMS_module3Cell12Volt,
        &BMS_module3Cell13Volt, &BMS_module3Cell14Volt, &BMS_module3Cell15Volt, &BMS_module3Cell16Volt, &BMS_module3Cell17Volt, &BMS_module3Cell18Volt,
        // Module 4
        &BMS_module4Cell1Volt, &BMS_module4Cell2Volt, &BMS_module4Cell3Volt, &BMS_module4Cell4Volt, &BMS_module4Cell5Volt, &BMS_module4Cell6Volt,
        &BMS_module4Cell7Volt, &BMS_module4Cell8Volt, &BMS_module4cCell9Volt, &BMS_module4Cell10Volt, &BMS_module4Cell11Volt, &BMS_module4Cell12Volt,
        &BMS_module4Cell13Volt, &BMS_module4Cell14Volt, &BMS_module4Cell15Volt, &BMS_module4Cell16Volt, &BMS_module4Cell17Volt, &BMS_module4Cell18Volt,
        // Module 5
        &BMS_module5Cell1Volt, &BMS_module5Cell2Volt, &BMS_module5Cell3Volt, &BMS_module5Cell4Volt, &BMS_module5Cell5Volt, &BMS_module5Cell6Volt,
        &BMS_module5Cell7Volt, &BMS_module5Cell8Volt, &BMS_module5Cell9Volt, &BMS_module5Cell10Volt, &BMS_module5Cell11Volt, &BMS_module5Cell12Volt,
        &BMS_module5Cell13Volt, &BMS_module5Cell14Volt, &BMS_module5Cell15Volt, &BMS_module5Cell16Volt, &BMS_module5Cell17Volt, &BMS_module5Cell18Volt
    };

    // Array of all 90 cell temperature signals
    StateSignal* allCellTemps[] = {
        // Module 1
        &BMS_module1Cell1Temp, &BMS_module1Cell2Temp, &BMS_module1Cell3Temp, &BMS_module1Cell4Temp, &BMS_module1Cell5Temp, &BMS_module1Cell6Temp,
        &BMS_module1Cell7Temp, &BMS_module1Cell8Temp, &BMS_module1Cell9Temp, &BMS_module1Cell10Temp, &BMS_module1Cell11Temp, &BMS_module1Cell12Temp,
        &BMS_module1Cell13Temp, &BMS_module1Cell14Temp, &BMS_module1Cell15Temp, &BMS_module1Cell16Temp, &BMS_module1Cell17Temp, &BMS_module1Cell18Temp,
        // Module 2
        &BMS_module2Cell1Temp, &BMS_module2Cell2Temp, &BMS_module2Cell3Temp, &BMS_module2Cell4Temp, &BMS_module2Cell5Temp, &BMS_module2Cell6Temp,
        &BMS_module2Cell7Temp, &BMS_module2Cell8Temp, &BMS_module2Cell9Temp, &BMS_module2Cell10Temp, &BMS_module2Cell11Temp, &BMS_module2Cell12Temp,
        &BMS_Module2Cell13Temp, &BMS_module2Cell14Temp, &BMS_module2Cell15Temp, &BMS_module2Cell16Temp, &BMS_module2Cell17Temp, &BMS_module2Cell18Temp,
        // Module 3
        &BMS_module3Cell1Temp, &BMS_module3Cell2Temp, &BMS_module3Cell3Temp, &BMS_module3Cell4Temp, &BMS_module3Cell5Temp, &BMS_module3Cell6Temp,
        &BMS_module3Cell7Temp, &BMS_module3Cell8Temp, &BMS_module3Cell9Temp, &BMS_module3Cell10Temp, &BMS_module3Cell11Temp, &BMS_module3Cell12Temp,
        &BMS_module3Cell13Temp, &BMS_module3Cell14Temp, &BMS_module3Cell15Temp, &BMS_module3Cell16Temp, &BMS_module3Cell17Temp, &BMS_module3Cell18Temp,
        // Module 4
        &BMS_module4Cell1Temp, &BMS_module4Cell2Temp, &BMS_module4Cell3Temp, &BMS_module4Cell4Temp, &BMS_module4Cell5Temp, &BMS_module4Cell6Temp,
        &BMS_module4Cell7Temp, &BMS_module4Cell8Temp, &BMS_module4Cell9Temp, &BMS_module4Cell10Temp, &BMS_module4Cell11Temp, &BMS_module4Cell12Temp,
        &BMS_module4Cell13Temp, &BMS_module4Cell14Temp, &BMS_module4Cell15Temp, &BMS_module4Cell16Temp, &BMS_module4Cell17Temp, &BMS_module4Cell18Temp,
        // Module 5
        &BMS_module5Cell1Temp, &BMS_module5Cell2Temp, &BMS_module5Cell3Temp, &BMS_module5Cell4Temp, &BMS_module5Cell5Temp, &BMS_module5Cell6Temp,
        &BMS_module5Cell7Temp, &BMS_module5Cell8Temp, &BMS_module5Cell9Temp, &BMS_module5Cell10Temp, &BMS_module5Cell11Temp, &BMS_module5Cell12Temp,
        &BMS_module5Cell13Temp, &BMS_module5Cell14Temp, &BMS_module5Cell15Temp, &BMS_module5Cell16Temp, &BMS_module5Cell17Temp, &BMS_module5Cell18Temp
    };

    int totalCells = 90; // 5 modules * 18 cells

    // 1. Check all Voltages
    for (int i = 0; i < totalCells; i++) {
        float v = allCellVolts[i]->can_value();
        if (v < 2.5 || v > 4.2) {
            faultDetected = true;
            break; // Stop checking voltages if a fault is already found
        }
    }

    // 2. Check all Temperatures (only if a voltage fault hasn't already tripped it)
    if (!faultDetected) {
        for (int i = 0; i < totalCells; i++) {
            float t = allCellTemps[i]->can_value();
            
            // Fault if < 1C, OR if it's > 40C (but strictly <= 600C to ignore disconnected sensors)
            if (t < 1.0 || (t > 40.0 && t <= 600.0)) {
                faultDetected = true;
                break; // Stop checking temps if a fault is found
            }
        }
    }

    // 3. Trigger the hardware switch if any fault was detected
    if (faultDetected) {
        digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault 
    }
}



// void checkVoltFault(){

//   Serial.print("Mod1cell1 value: ");
//   Serial.println(BMS_module1Cell1Volt.can_value());
//     // MODULE 1 VOLTAGES
//     if (BMS_module1Cell1Volt.can_value() > 4.2) {
//         digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
//         Serial.print("Module1Cell1V > 4.2\n");
//     } else if (BMS_module1Cell1Volt.can_value() < 2.5) {
//         digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
//         Serial.print("Module1Cell1V < 2.5\n");
//     }

//     if (BMS_module1Cell2Volt.can_value() > 4.2) {
//         digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
//         Serial.print("Module1Cell2V > 4.2\n");
//     } else if (BMS_module1Cell2Volt.can_value() < 2.5) {
//         digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
//         Serial.print("Module1Cell2V < 2.5\n");
//     }

//     if (BMS_module1Cell3Volt.can_value() > 4.2) {
//         digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
//         Serial.print("Module1Cell3V > 4.2\n");
//     } else if (BMS_module1Cell3Volt.can_value() < 2.5) {
//         digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
//         Serial.print("Module1Cell3V < 2.5\n");
//     }

    // if (BMS_module1Cell4Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell4V > 4.2\n");
    // } else if (BMS_module1Cell4Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell4V < 2.5\n");
    // }

    // if (BMS_module1Cell5Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell5V > 4.2\n");
    // } else if (BMS_module1Cell5Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell5V < 2.5\n");
    // }

    // if (BMS_module1Cell6Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell6V > 4.2\n");
    // } else if (BMS_module1Cell6Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell6V < 2.5\n");
    // }

    // if (BMS_module1Cell7Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell7V > 4.2\n");
    // } else if (BMS_module1Cell7Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell7V < 2.5\n");
    // }

    // if (BMS_module1Cell8Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell8V > 4.2\n");
    // } else if (BMS_module1Cell8Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell8V < 2.5\n");
    // }

    // if (BMS_module1Cell9Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell9V > 4.2\n");
    // } else if (BMS_module1Cell9Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell9V < 2.5\n");
    // }

    // if (BMS_module1Cell10Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell10V > 4.2\n");
    // } else if (BMS_module1Cell10Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell10V < 2.5\n");
    // }

    // if (BMS_module1Cell11Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell11V > 4.2\n");
    // } else if (BMS_module1Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell11V < 2.5\n");
    // }

    // if (BMS_module1Cell12Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell12V > 4.2\n");
    // } else if (BMS_module1Cell12Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell12V < 2.5\n");
    // }

    // if (BMS_module1Cell13Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell13V > 4.2\n");
    // } else if (BMS_module1Cell13Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell13V < 2.5\n");
    // }

    // if (BMS_module1Cell14Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell14V > 4.2\n");
    // } else if (BMS_module1Cell14Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell14V < 2.5\n");
    // }

    // if (BMS_module1Cell15Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell15V > 4.2\n");
    // } else if (BMS_module1Cell15Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell15V < 2.5\n");
    // }

    // if (BMS_module1Cell16Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module16Cell1V > 4.2\n");
    // } else if (BMS_module1Cell16Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell16V < 2.5\n");
    // }

    // if (BMS_module1Cell17Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell17V > 4.2\n");
    // } else if (BMS_module1Cell17Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell17V < 2.5\n");
    // }

    // if (BMS_module1Cell18Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell18V > 4.2\n");
    // } else if (BMS_module1Cell18Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module1Cell18V < 2.5\n");
    // }

    //     // MODULE 2 VOLTAGES
    // if (BMS_module2Cell1Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module12Cell1V > 4.2\n");
    // } else if (BMS_module2Cell1Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell1V < 2.5\n");
    // }

    // if (BMS_module2Cell2Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell2V > 4.2\n");
    // } else if (BMS_module2Cell2Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell2V < 2.5\n");
    // }

    // if (BMS_module2Cell3Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell3V > 4.2\n");
    // } else if (BMS_module2Cell3Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell3V < 2.5\n");
    // }

    // if (BMS_module2Cell4Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell4V > 4.2\n");
    // } else if (BMS_module2Cell4Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell4V < 2.5\n");
    // }

    // if (BMS_module2Cell5Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell5V > 4.2\n");
    // } else if (BMS_module2Cell5Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell5V < 2.5\n");
    // }

    // if (BMS_module2Cell6Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell6V > 4.2\n");
    // } else if (BMS_module2Cell6Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell6V < 2.5\n");
    // }

    // if (BMS_module2Cell7Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell7V > 4.2\n");
    // } else if (BMS_module2Cell7Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell7V < 2.5\n");
    // }

    // if (BMS_module2Cell8Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell8V > 4.2\n");
    // } else if (BMS_module2Cell8Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell8V < 2.5\n");
    // }

    // if (BMS_module2Cell9Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell9V > 4.2\n");
    // } else if (BMS_module2Cell9Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell9V < 2.5\n");
    // }

    // if (BMS_module2Cell10Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell10V > 4.2\n");
    // } else if (BMS_module2Cell10Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell10V < 2.5\n");
    // }

    // if (BMS_module2Cell11Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell11V > 4.2\n");
    // } else if (BMS_module2Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell11V < 2.5\n");
    // }

    // if (BMS_module2Cell12Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell12V > 4.2\n");
    // } else if (BMS_module2Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell11V < 2.5\n");
    // }

    // if (BMS_module2Cell13Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell13V > 4.2\n");
    // } else if (BMS_module2Cell13Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell13V < 2.5\n");
    // }

    // if (BMS_module2Cell14Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell14V > 4.2\n");
    // } else if (BMS_module2Cell14Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell14V < 2.5\n");
    // }

    // if (BMS_module2Cell15Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell15V > 4.2\n");
    // } else if (BMS_module2Cell15Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell14V < 2.5\n");
    // }

    // if (BMS_module2Cell16Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell16V > 4.2\n");
    // } else if (BMS_module2Cell16Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell16V < 2.5\n");
    // }

    // if (BMS_module2Cell17Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell17V > 4.2\n");
    // } else if (BMS_module2Cell17Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell17V < 2.5\n");
    // }

    // if (BMS_module2Cell18Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell18V > 4.2\n");
    // } else if (BMS_module2Cell18Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module2Cell18V < 2.5\n");
    // }

    // // MODULE 3 VOLTAGES
    // if (BMS_module3Cell1Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell1V > 4.2\n");
    // } else if (BMS_module3Cell1Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell1V < 2.5\n");
    // }

    // if (BMS_module3Cell2Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell2V > 4.2\n");
    // } else if (BMS_module3Cell2Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell2V < 2.5\n");
    // }

    // if (BMS_module3Cell3Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell3V > 4.2\n");
    // } else if (BMS_module3Cell3Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell3V < 2.5\n");
    // }

    // if (BMS_module3Cell4Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell4V > 4.2\n");
    // } else if (BMS_module3Cell4Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell4V < 2.5\n");
    // }

    // if (BMS_module3Cell5Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell5V > 4.2\n");
    // } else if (BMS_module3Cell5Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell5V < 2.5\n");
    // }

    // if (BMS_module3Cell6Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell6V > 4.2\n");
    // } else if (BMS_module3Cell6Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell6V < 2.5\n");
    // }

    // if (BMS_module3Cell7Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell7V > 4.2\n");
    // } else if (BMS_module3Cell7Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell7V < 2.5\n");
    // }

    // if (BMS_module3Cell8Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell8V > 4.2\n");
    // } else if (BMS_module3Cell8Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell8V < 2.5\n");
    // }

    // if (BMS_module3Cell9Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell9V > 4.2\n");
    // } else if (BMS_module3Cell9Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell9V < 2.5\n");
    // }

    // if (BMS_module3Cell10Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell10V > 4.2\n");
    // } else if (BMS_module3Cell10Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell10V < 2.5\n");
    // }

    // if (BMS_module3Cell11Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell11V > 4.2\n");
    // } else if (BMS_module3Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell11V < 2.5\n");
    // }

    // if (BMS_module3Cell12Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell12V > 4.2\n");
    // } else if (BMS_module3Cell12Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell12V < 2.5\n");
    // }

    // if (BMS_module3Cell13Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell13V > 4.2\n");
    // } else if (BMS_module3Cell13Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell13V < 2.5\n");
    // }

    // if (BMS_module3Cell14Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell14V > 4.2\n");
    // } else if (BMS_module3Cell14Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell14V < 2.5\n");
    // }

    // if (BMS_module3Cell15Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell15V > 4.2\n");
    // } else if (BMS_module3Cell15Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell15V < 2.5\n");
    // }

    // if (BMS_module3Cell16Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell16V > 4.2\n");
    // } else if (BMS_module3Cell16Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell16V < 2.5\n");
    // }

    // if (BMS_module3Cell17Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell17V > 4.2\n");
    // } else if (BMS_module3Cell17Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell17V < 2.5\n");
    // }

    // if (BMS_module3Cell18Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell18V > 4.2\n");
    // } else if (BMS_module3Cell18Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module3Cell18V < 2.5\n");
    // }

    // // MODULE 4 VOLTAGES
    // if (BMS_module4Cell1Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell1V > 4.2\n");
    // } else if (BMS_module4Cell1Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell1V < 2.5\n");
    // }

    // if (BMS_module4Cell2Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell2V > 4.2\n");
    // } else if (BMS_module4Cell2Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell2V < 2.5\n");
    // }

    // if (BMS_module4Cell3Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell3V > 4.2\n");
    // } else if (BMS_module4Cell3Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell3V < 2.5\n");
    // }

    // if (BMS_module4Cell4Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell4V > 4.2\n");
    // } else if (BMS_module4Cell4Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell4V < 2.5\n");
    // }

    // if (BMS_module4Cell5Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell5V > 4.2\n");
    // } else if (BMS_module4Cell5Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell5V < 2.5\n");
    // }

    // if (BMS_module4Cell6Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell6V > 4.2\n");
    // } else if (BMS_module4Cell6Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell6V < 2.5\n");
    // }

    // if (BMS_module4Cell7Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell7V > 4.2\n");
    // } else if (BMS_module4Cell7Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell7V < 2.5\n");
    // }

    // if (BMS_module4Cell8Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell8V > 4.2\n");
    // } else if (BMS_module4Cell8Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell8V < 2.5\n");
    // }

    // if (BMS_module4cCell9Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell9V > 4.2\n");
    // } else if (BMS_module4cCell9Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell9V < 2.5\n");
    // }

    // if (BMS_module4Cell10Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell10V > 4.2\n");
    // } else if (BMS_module4Cell10Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell10V < 2.5\n");
    // }

    // if (BMS_module4Cell11Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell11V > 4.2\n");
    // } else if (BMS_module4Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell11V < 2.5\n");
    // }

    // if (BMS_module4Cell12Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell12V > 4.2\n");
    // } else if (BMS_module4Cell12Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell12V < 2.5\n");
    // }

    // if (BMS_module4Cell13Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell13V > 4.2\n");
    // } else if (BMS_module4Cell13Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell13V < 2.5\n");
    // }

    // if (BMS_module4Cell14Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell14V > 4.2\n");
    // } else if (BMS_module4Cell14Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell14V < 2.5\n");
    // }

    // if (BMS_module4Cell15Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell15V > 4.2\n");
    // } else if (BMS_module4Cell15Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell15V < 2.5\n");
    // }

    // if (BMS_module4Cell16Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell16V > 4.2\n");
    // } else if (BMS_module4Cell16Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell16V < 2.5\n");
    // }

    // if (BMS_module4Cell17Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell17V > 4.2\n");
    // } else if (BMS_module4Cell17Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell17V < 2.5\n");
    // }

    // if (BMS_module4Cell18Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell18V > 4.2\n");
    // } else if (BMS_module4Cell18Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module4Cell18V < 2.5\n");
    // }

    // // MODULE 5 VOLTAGES
    // if (BMS_module5Cell1Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell1V > 4.2\n");
    // } else if (BMS_module5Cell1Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell1V < 2.5\n");
    // }

    // if (BMS_module5Cell2Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell2V > 4.2\n");
    // } else if (BMS_module5Cell2Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell2V < 2.5\n");
    // }

    // if (BMS_module5Cell3Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell3V > 4.2\n");
    // } else if (BMS_module5Cell3Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell3V < 2.5\n");
    // }

    // if (BMS_module5Cell4Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell4V > 4.2\n");
    // } else if (BMS_module5Cell4Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell4V < 2.5\n");
    // }

    // if (BMS_module5Cell5Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell5V > 4.2\n");
    // } else if (BMS_module5Cell5Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell5V < 2.5\n");
    // }

    // if (BMS_module5Cell6Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell6V > 4.2\n");
    // } else if (BMS_module5Cell6Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell6V < 2.5\n");
    // }

    // if (BMS_module5Cell7Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell7V > 4.2\n");
    // } else if (BMS_module5Cell7Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell7V < 2.5\n");
    // }

    // if (BMS_module5Cell8Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell8V > 4.2\n");
    // } else if (BMS_module5Cell8Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell8V < 2.5\n");
    // }

    // if (BMS_module5Cell9Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell9V > 4.2\n");
    // } else if (BMS_module5Cell9Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell9V < 2.5\n");
    // }

    // if (BMS_module5Cell10Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell10V > 4.2\n");
    // } else if (BMS_module5Cell10Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell10V < 2.5\n");
    // }

    // if (BMS_module5Cell11Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module6Cell11V > 4.2\n");
    // } else if (BMS_module5Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell11V < 2.5\n");
    // }

    // if (BMS_module5Cell12Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell12V > 4.2\n");
    // } else if (BMS_module5Cell11Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module6Cell12V < 2.5\n");
    // }

    // if (BMS_module5Cell13Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell13V > 4.2\n");
    // } else if (BMS_module5Cell13Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell13V < 2.5\n");
    // }

    // if (BMS_module5Cell14Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell14V > 4.2\n");
    // } else if (BMS_module5Cell14Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell4V < 2.5\n");
    // }

    // if (BMS_module5Cell15Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell15V > 4.2\n");
    // } else if (BMS_module5Cell15Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell15V < 2.5\n");
    // }

    // if (BMS_module5Cell16Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell16V > 4.2\n");
    // } else if (BMS_module5Cell16Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell16V < 2.5\n");
    // }

    // if (BMS_module5Cell17Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell17V > 4.2\n");
    // } else if (BMS_module5Cell17Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell17V < 2.5\n");
    // }

    // if (BMS_module5Cell18Volt.can_value() > 4.2) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell18V > 4.2\n");
    // } else if (BMS_module5Cell18Volt.can_value() < 2.5) {
    //     digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    //     Serial.print("Module5Cell18V < 2.5\n");
    // }

}

void checkTempFault(){

  // MODULE 1 TEMPS
  if (BMS_module1Cell1Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell1Temp > 60");
  }

  if (BMS_module1Cell2Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell2Temp > 60");
  }

  if (BMS_module1Cell3Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell3Temp > 60");
  }

  if (BMS_module1Cell4Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell4Temp > 60");
  }

  if (BMS_module1Cell5Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell5Temp > 60");
  }

  if (BMS_module1Cell6Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell6Temp > 60");
  }

  if (BMS_module1Cell7Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell7Temp > 60");
  }

  if (BMS_module1Cell8Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell8Temp > 60");
  }

  if (BMS_module1Cell9Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell9Temp > 60");
  }

  if (BMS_module1Cell10Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell10Temp > 60");
  }

  if (BMS_module1Cell11Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell11Temp > 60");
  }

  if (BMS_module1Cell12Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell12Temp > 60");
  }

  if (BMS_module1Cell13Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell13Temp > 60");
  }

  if (BMS_module1Cell14Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell14Temp > 60");
  }

  if (BMS_module1Cell15Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell15Temp > 60");
  }

  if (BMS_module1Cell16Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell16Temp > 60");
  }

  if (BMS_module1Cell17Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell17Temp > 60");
  }

  if (BMS_module1Cell18Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module1Cell18Temp > 60");
  }

    // MODULE 2 TEMPS
  if (BMS_module2Cell1Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell1Temp > 60");
  }

  if (BMS_module2Cell2Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell2Temp > 60");
  }

  if (BMS_module2Cell3Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell3Temp > 60");
  }

  if (BMS_module2Cell4Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell4Temp > 60");
  }

  if (BMS_module2Cell5Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell5Temp > 60");
  }

  if (BMS_module2Cell6Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell6Temp > 60");
  }

  if (BMS_module2Cell7Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell7Temp > 60");
  }

  if (BMS_module2Cell8Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell8Temp > 60");
  }

  if (BMS_module2Cell9Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell9Temp > 60");
  }

  if (BMS_module2Cell10Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell10Temp > 60");
  }

  if (BMS_module2Cell11Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell11Temp > 60");
  }

  if (BMS_module2Cell12Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell12Temp > 60");
  }

  if (BMS_Module2Cell13Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell13Temp > 60");
  }

  if (BMS_module2Cell14Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell14Temp > 60");
  }

  if (BMS_module2Cell15Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell15Temp > 60");
  }

  if (BMS_module2Cell16Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell16Temp > 60");
  }

  if (BMS_module2Cell17Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell17Temp > 60");
  }

  if (BMS_module2Cell18Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module2Cell18Temp > 60");
  }

  // MODULE 3 TEMPS
  if (BMS_module3Cell1Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell1Temp > 60");
  }

  if (BMS_module3Cell2Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell2Temp > 60");
  }

  if (BMS_module3Cell3Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell3Temp > 60");
  }

  if (BMS_module3Cell4Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell4Temp > 60");
  }

  if (BMS_module3Cell5Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell5Temp > 60");
  }

  if (BMS_module3Cell6Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell6Temp > 60");
  }

  if (BMS_module3Cell7Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell7Temp > 60");
  }

  if (BMS_module3Cell8Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell8Temp > 60");
  }

  if (BMS_module3Cell9Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell9Temp > 60");
  }

  if (BMS_module3Cell10Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell10Temp > 60");
  }

  if (BMS_module3Cell11Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell11Temp > 60");
  }

  if (BMS_module3Cell12Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell12Temp > 60");
  }

  if (BMS_module3Cell13Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell13Temp > 60");
  }

  if (BMS_module3Cell14Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell14Temp > 60");
  }

  if (BMS_module3Cell15Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell15Temp > 60");
  }

  if (BMS_module3Cell16Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell16Temp > 60");
  }

  if (BMS_module3Cell17Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell17Temp > 60");
  }

  if (BMS_module3Cell18Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module3Cell18Temp > 60");
  }

    // MODULE 4 TEMPS
  if (BMS_module4Cell1Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell1Temp > 60");
  }

  if (BMS_module4Cell2Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell2Temp > 60");
  }

  if (BMS_module4Cell3Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell3Temp > 60");
  }

  if (BMS_module4Cell4Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell4Temp > 60");
  }

  if (BMS_module4Cell5Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell5Temp > 60");
  }

  if (BMS_module4Cell6Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell6Temp > 60");
  }

  if (BMS_module4Cell7Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell7Temp > 60");
  }

  if (BMS_module4Cell8Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell8Temp > 60");
  }

  if (BMS_module4Cell9Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell9Temp > 60");
  }

  if (BMS_module4Cell10Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell10Temp > 60");
  }

  if (BMS_module4Cell11Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell11Temp > 60");
  }

  if (BMS_module4Cell12Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell12Temp > 60");
  }

  if (BMS_module4Cell13Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell13Temp > 60");
  }

  if (BMS_module4Cell14Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell14Temp > 60");
  }

  if (BMS_module4Cell15Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell15Temp > 60");
  }

  if (BMS_module4Cell16Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell16Temp > 60");
  }

  if (BMS_module4Cell17Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell17Temp > 60");
  }

  if (BMS_module4Cell18Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module4Cell18Temp > 60");
  }

  // MODULE 5 TEMPS
  if (BMS_module5Cell1Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell1Temp > 60");
  }

  if (BMS_module5Cell2Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell2Temp > 60");
  }

  if (BMS_module5Cell3Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell3Temp > 60");
  }

  if (BMS_module5Cell4Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell4Temp > 60");
  }

  if (BMS_module5Cell5Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell5Temp > 60");
  }

  if (BMS_module5Cell6Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell6Temp > 60");
  }

  if (BMS_module5Cell7Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell7Temp > 60");
  }

  if (BMS_module5Cell8Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell8Temp > 60");
  }

  if (BMS_module5Cell9Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell9Temp > 60");
  }

  if (BMS_module5Cell10Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell10Temp > 60");
  }

  if (BMS_module5Cell11Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell11Temp > 60");
  }

  if (BMS_module5Cell12Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell12Temp > 60");
  }

  if (BMS_module5Cell13Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell13Temp > 60");
  }

  if (BMS_module5Cell14Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell14Temp > 60");
  }

  if (BMS_module5Cell15Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell15Temp > 60");
  }

  if (BMS_module5Cell16Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell16Temp > 60");
  }

  if (BMS_module5Cell17Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell17Temp > 60");
  }

  if (BMS_module5Cell18Temp.can_value() > 60){
    digitalWrite(BMS_STATUS_SWITCH, LOW); // set BMS status fault
    Serial.print("Module5Cell18Temp > 60");
  }

}


