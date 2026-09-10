#include "contactordriver.h"

#include <FlexCAN_T4.h>
#include <EasyTimer.h>

#include <StateCAN.h>
#include "CAN/raptor_CAN1.hpp"
#include "CAN/SR26_CAN2.hpp"
#include "CAN/elcon.hpp"

// BENCH TEST MODE
#include "BMS_CAN_TEST_MODE.h"

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
unsigned long undervoltageFaultDetectedTime = 0;

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

void setup() {

    disableAllCont();
    Serial.begin(112500);

    SPI.begin();

    adc1.begin();

    can1.begin();
    can1.setBaudRate(500000);

    can2.begin();
    can2.setBaudRate(1000000);

    can3.begin();
    can3.setBaudRate(250000);

    set_mailboxes();

    pinMode(BMS_STATUS_SWITCH, OUTPUT);
    digitalWrite(BMS_STATUS_SWITCH, HIGH);

#ifdef BMS_CAN_TEST_MODE
    bmsTestBegin();
#endif
}

int currentTime = millis();
int undevoltageFaultDetectedTime = millis();

void loop() {

    adc1.sample(sens0, sens1, sens2, sens3);
    Serial.println("running");


#ifdef BMS_CAN_TEST_MODE

    bmsTestUpdate();

    checkAllBatterySafetyLimits();

    Serial.print("Pin 9 state: ");
    Serial.println(digitalRead(BMS_STATUS_SWITCH));

#else

    // ------------------------------------------------------------
    // NORMAL VEHICLE OPERATION
    // ------------------------------------------------------------

    read_CAN();

    checkAllBatterySafetyLimits();


    /////////////// CHARGING FLAG /////////////////

    if (
        OutputVoltage.value() <= PACK_VOLTAGE_UPPER_LIMIT &&
        OutputVoltage.value() >= PACK_VOLTAGE_LOWER_LIMIT
    ) {

        VALID_VOLTAGE_RANGE = true;

    } else {

        VALID_VOLTAGE_RANGE = false;
    }


    if (
        VCU_vehicleState.can_value() == 0 &&
        VALID_VOLTAGE_RANGE
    ) {

        CHARGING = true;

    } else {

        Serial.println("not chargin because");
        Serial.println(VCU_vehicleState.can_value());
        Serial.println(VALID_VOLTAGE_RANGE);
        Serial.println(OutputVoltage.value());
        CHARGING = false;
    }

    /////////////// CHARGING FLAG /////////////////



    /////////////// CONTACTOR STATES ///////////////

    if (
        VCU_vehicleState.can_value() == 0
    ) {

        if (
            CHARGING
        ) {

            Serial.println("CHARGING");
            runOperational();

        } else {

            Serial.println("NOT CHARGING");
            runDischarge();
        }

    } else if (
        VCU_vehicleState.can_value() == 1
    ) {

        runPrecharge();

    } else if (
        VCU_vehicleState.can_value() == 2
    ) {

        runOperational();

    } else if (
        VCU_vehicleState.can_value() == 3
    ) {

        runOperational();

    } else if (
        VCU_vehicleState.can_value() == 4
    ) {

        runDischarge();

    } else if (
        VCU_vehicleState.can_value() == 5
    ) {

        runDischarge();

    } else if (
        VCU_vehicleState.can_value() == 6
    ) {

        runDischarge();
    }

    /////////////// CONTACTOR STATES ///////////////


    sumPackVoltage();

    send_can2(); // summed info CANbus

    send_can3(); // charger CANbus


#endif


#ifdef BMS_CAN_TEST_MODE

    // Slow bench test loop down so Serial Monitor is easy to use
    delay(2000);

#endif
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

    // CAN1
    count = 0;
    while (count < MAX_CAN_FRAME_READ_PER_CYCLE && can1.read(rxmsg)) {
        decode_raptor_CAN1(rxmsg);
        count++;
    }

    // CAN2
    count = 0;
    while (count < MAX_CAN_FRAME_READ_PER_CYCLE && can2.read(rxmsg)) {
        decode_SR26_CAN2(rxmsg);
        count++;
    }

    // CAN3
    count = 0;
    while (count < MAX_CAN_FRAME_READ_PER_CYCLE && can3.read(rxmsg)) {
        decode_elcon(rxmsg);
        count++;
    }
}

void sumPackVoltage() {

    float module1Volt = 0;
    float module2Volt = 0;
    float module3Volt = 0;
    float module4Volt = 0;
    float module5Volt = 0;
    float PackVoltage = 0;

    module1Volt = BMS_module1voltageBMSS.value();
    module2Volt = BMS_module2voltageBMSS.value();
    module3Volt = BMS_module3voltageBMSS.value();
    module4Volt = BMS_module4voltageBMSS.value();
    module5Volt = BMS_module5voltageBMSS.value();

    PackVoltage =
        module1Volt +
        module2Volt +
        module3Volt +
        module4Volt +
        module5Volt;

    // Set pack voltage for CAN
    BMS_packmVoltage = PackVoltage;
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
    currentTime = millis();

    // Read all 90 cell voltages directly from their CAN values.
    // This avoids using StateSignal* arrays.
    float allCellVolts[] = {
        // Module 1
        BMS_module1Cell1Volt.value(), BMS_module1Cell2Volt.value(), BMS_module1Cell3Volt.value(), BMS_module1Cell4Volt.value(), BMS_module1Cell5Volt.value(), BMS_module1Cell6Volt.value(),
        BMS_module1Cell7Volt.value(), BMS_module1Cell8Volt.value(), BMS_module1Cell9Volt.value(), BMS_module1Cell10Volt.value(), BMS_module1Cell11Volt.value(), BMS_module1Cell12Volt.value(),
        BMS_module1Cell13Volt.value(), BMS_module1Cell14Volt.value(), BMS_module1Cell15Volt.value(), BMS_module1Cell16Volt.value(), BMS_module1Cell17Volt.value(), BMS_module1Cell18Volt.value(),

        // Module 2
        BMS_module2Cell1Volt.value(), BMS_module2Cell2Volt.value(), BMS_module2Cell3Volt.value(), BMS_module2Cell4Volt.value(), BMS_module2Cell5Volt.value(), BMS_module2Cell6Volt.value(),
        BMS_module2Cell7Volt.value(), BMS_module2Cell8Volt.value(), BMS_module2Cell9Volt.value(), BMS_module2Cell10Volt.value(), BMS_module2Cell11Volt.value(), BMS_module2Cell12Volt.value(),
        BMS_module2Cell13Volt.value(), BMS_module2Cell14Volt.value(), BMS_module2Cell15Volt.value(), BMS_module2Cell16Volt.value(), BMS_module2Cell17Volt.value(), BMS_module2Cell18Volt.value(),

        // Module 3
        BMS_module3Cell1Volt.value(), BMS_module3Cell2Volt.value(), BMS_module3Cell3Volt.value(), BMS_module3Cell4Volt.value(), BMS_module3Cell5Volt.value(), BMS_module3Cell6Volt.value(),
        BMS_module3Cell7Volt.value(), BMS_module3Cell8Volt.value(), BMS_module3Cell9Volt.value(), BMS_module3Cell10Volt.value(), BMS_module3Cell11Volt.value(), BMS_module3Cell12Volt.value(),
        BMS_module3Cell13Volt.value(), BMS_module3Cell14Volt.value(), BMS_module3Cell15Volt.value(), BMS_module3Cell16Volt.value(), BMS_module3Cell17Volt.value(), BMS_module3Cell18Volt.value(),

        // Module 4
        BMS_module4Cell1Volt.value(), BMS_module4Cell2Volt.value(), BMS_module4Cell3Volt.value(), BMS_module4Cell4Volt.value(), BMS_module4Cell5Volt.value(), BMS_module4Cell6Volt.value(),
        BMS_module4Cell7Volt.value(), BMS_module4Cell8Volt.value(), BMS_module4Cell9Volt.value(), BMS_module4Cell10Volt.value(), BMS_module4Cell11Volt.value(), BMS_module4Cell12Volt.value(),
        BMS_module4Cell13Volt.value(), BMS_module4Cell14Volt.value(), BMS_module4Cell15Volt.value(), BMS_module4Cell16Volt.value(), BMS_module4Cell17Volt.value(), BMS_module4Cell18Volt.value(),

        // Module 5
        BMS_module5Cell1Volt.value(), BMS_module5Cell2Volt.value(), BMS_module5Cell3Volt.value(), BMS_module5Cell4Volt.value(), BMS_module5Cell5Volt.value(), BMS_module5Cell6Volt.value(),
        BMS_module5Cell7Volt.value(), BMS_module5Cell8Volt.value(), BMS_module5Cell9Volt.value(), BMS_module5Cell10Volt.value(), BMS_module5Cell11Volt.value(), BMS_module5Cell12Volt.value(),
        BMS_module5Cell13Volt.value(), BMS_module5Cell14Volt.value(), BMS_module5Cell15Volt.value(), BMS_module5Cell16Volt.value(), BMS_module5Cell17Volt.value(), BMS_module5Cell18Volt.value()
    };

    // Read all 90 cell temperatures directly from their CAN values.
    float allCellTemps[] = {
        // Module 1
        BMS_module1Cell1Temp.value(), BMS_module1Cell2Temp.value(), BMS_module1Cell3Temp.value(), BMS_module1Cell4Temp.value(), BMS_module1Cell5Temp.value(), BMS_module1Cell6Temp.value(),
        BMS_module1Cell7Temp.value(), BMS_module1Cell8Temp.value(), BMS_module1Cell9Temp.value(), BMS_module1Cell10Temp.value(), BMS_module1Cell11Temp.value(), BMS_module1Cell12Temp.value(),
        BMS_module1Cell13Temp.value(), BMS_module1Cell14Temp.value(), BMS_module1Cell15Temp.value(), BMS_module1Cell16Temp.value(), BMS_module1Cell17Temp.value(), BMS_module1Cell18Temp.value(),

        // Module 2
        BMS_module2Cell1Temp.value(), BMS_module2Cell2Temp.value(), BMS_module2Cell3Temp.value(), BMS_module2Cell4Temp.value(), BMS_module2Cell5Temp.value(), BMS_module2Cell6Temp.value(),
        BMS_module2Cell7Temp.value(), BMS_module2Cell8Temp.value(), BMS_module2Cell9Temp.value(), BMS_module2Cell10Temp.value(), BMS_module2Cell11Temp.value(), BMS_module2Cell12Temp.value(),
        BMS_Module2Cell13Temp.value(), BMS_module2Cell14Temp.value(), BMS_module2Cell15Temp.value(), BMS_module2Cell16Temp.value(), BMS_module2Cell17Temp.value(), BMS_module2Cell18Temp.value(),

        // Module 3
        BMS_module3Cell1Temp.value(), BMS_module3Cell2Temp.value(), BMS_module3Cell3Temp.value(), BMS_module3Cell4Temp.value(), BMS_module3Cell5Temp.value(), BMS_module3Cell6Temp.value(),
        BMS_module3Cell7Temp.value(), BMS_module3Cell8Temp.value(), BMS_module3Cell9Temp.value(), BMS_module3Cell10Temp.value(), BMS_module3Cell11Temp.value(), BMS_module3Cell12Temp.value(),
        BMS_module3Cell13Temp.value(), BMS_module3Cell14Temp.value(), BMS_module3Cell15Temp.value(), BMS_module3Cell16Temp.value(), BMS_module3Cell17Temp.value(), BMS_module3Cell18Temp.value(),

        // Module 4
        BMS_module4Cell1Temp.value(), BMS_module4Cell2Temp.value(), BMS_module4Cell3Temp.value(), BMS_module4Cell4Temp.value(), BMS_module4Cell5Temp.value(), BMS_module4Cell6Temp.value(),
        BMS_module4Cell7Temp.value(), BMS_module4Cell8Temp.value(), BMS_module4Cell9Temp.value(), BMS_module4Cell10Temp.value(), BMS_module4Cell11Temp.value(), BMS_module4Cell12Temp.value(),
        BMS_module4Cell13Temp.value(), BMS_module4Cell14Temp.value(), BMS_module4Cell15Temp.value(), BMS_module4Cell16Temp.value(), BMS_module4Cell17Temp.value(), BMS_module4Cell18Temp.value(),

        // Module 5
        BMS_module5Cell1Temp.value(), BMS_module5Cell2Temp.value(), BMS_module5Cell3Temp.value(), BMS_module5Cell4Temp.value(), BMS_module5Cell5Temp.value(), BMS_module5Cell6Temp.value(),
        BMS_module5Cell7Temp.value(), BMS_module5Cell8Temp.value(), BMS_module5Cell9Temp.value(), BMS_module5Cell10Temp.value(), BMS_module5Cell11Temp.value(), BMS_module5Cell12Temp.value(),
        BMS_module5Cell13Temp.value(), BMS_module5Cell14Temp.value(), BMS_module5Cell15Temp.value(), BMS_module5Cell16Temp.value(), BMS_module5Cell17Temp.value(), BMS_module5Cell18Temp.value()
    };

    const int totalCells = 90;

// Default = healthy / no fault
BMS_packSOC = 1;


// ============================================================
// VOLTAGE CHECKS
// ============================================================

bool undervoltageDetected = false;
int undervoltageCell = 0;

for (int i = 0; i < totalCells; i++) {

    float v = allCellVolts[i];
    int cellNumber = i + 1;

    if (v < 2.5) {
        undervoltageDetected = true;
        undervoltageCell = cellNumber;
        break;
    }
}

if (undervoltageDetected) {

    // Start timer when undervoltage is first detected
    if (undervoltageFaultDetectedTime == 0) {
        undervoltageFaultDetectedTime = millis();
    }

    // Only fault if undervoltage has continuously existed for 2 seconds
    if (millis() - undervoltageFaultDetectedTime >= 2000) {

        faultDetected = true;

        BMS_packSOC = 100 + undervoltageCell;

        Serial.print("Undervoltage fault on cell ");
        Serial.print(undervoltageCell);

        Serial.print("  Fault code: ");
        Serial.println(100 + undervoltageCell);
    }

} else {

    // Every cell is healthy again, so reset timer
    undervoltageFaultDetectedTime = 0;
}


// ============================================================
// TEMPERATURE CHECKS
// ============================================================

if (!faultDetected) {

    for (int i = 0; i < totalCells; i++) {

        float t = allCellTemps[i];

        int cellNumber = i + 1;


        // ---------------- LOW TEMPERATURE ----------------

        if (t < 1.0) {

            faultDetected = true;

            // 301-390
            BMS_packSOC =
                300 + cellNumber;

            Serial.print("Low temperature fault on cell ");
            Serial.print(cellNumber);

            Serial.print(": ");
            Serial.print(t);

            Serial.print("  Fault code: ");
            Serial.println(
                300 + cellNumber
            );

            break;
        }


        // ---------------- HIGH TEMPERATURE ----------------

        if (t > 60.0 && t <= 200.0) {

            faultDetected = true;

            // 401-490
            BMS_packSOC =
                400 + cellNumber;

            Serial.print("High temperature fault on cell ");
            Serial.print(cellNumber);

            Serial.print(": ");
            Serial.print(t);

            Serial.print("  Fault code: ");
            Serial.println(
                400 + cellNumber
            );

            break;
        }
    }
}


// ============================================================
// BMS STATUS OUTPUT
// ============================================================

if (faultDetected) {

    digitalWrite(
        BMS_STATUS_SWITCH,
        LOW
    );

} else {

    // 1 = no fault
    BMS_packSOC = 1;

    digitalWrite(
        BMS_STATUS_SWITCH,
        HIGH
    );
}
}