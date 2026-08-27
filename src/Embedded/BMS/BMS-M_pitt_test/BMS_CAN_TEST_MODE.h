#ifndef BMS_CAN_TEST_MODE_H
#define BMS_CAN_TEST_MODE_H

/*
 * ================================================================
 * BMS CAN / SAFETY BENCH TEST MODE
 * ================================================================
 *
 * This test mode injects PHYSICAL/ENGINEERING values into the
 * StateSignal objects because the production safety logic now uses:
 *
 *      signal.value()
 *
 * Examples with the updated DBC scaling:
 *
 *      4.100 V -> value() = 4.100, can_value() = 4100
 *      4.200 V -> value() = 4.200, can_value() = 4200
 *      25.0 C  -> value() = 25.0,  can_value() = 250
 *
 * Include this file AFTER the generated StateCAN headers.
 */

// Comment this out to disable bench-test mode.
//#define BMS_CAN_TEST_MODE

#ifdef BMS_CAN_TEST_MODE


// ================================================================
// PHYSICAL TEST VALUES
// ================================================================

// ---------------- VOLTAGE ----------------

const float BMS_TEST_NORMAL_VOLTAGE =
    3.70f;

const float BMS_TEST_UNDERVOLTAGE =
    2.49f;

const float BMS_TEST_OVERVOLTAGE =
    4.21f;

const float BMS_TEST_LOWEST_GOOD_VOLTAGE =
    2.50f;

const float BMS_TEST_HIGHEST_GOOD_VOLTAGE =
    4.20f;


// ---------------- TEMPERATURE ----------------

const float BMS_TEST_NORMAL_TEMP =
    25.0f;

const float BMS_TEST_LOW_TEMP =
    0.0f;

const float BMS_TEST_HIGH_TEMP =
    45.0f;

const float BMS_TEST_LOWEST_GOOD_TEMP =
    1.0f;

const float BMS_TEST_HIGHEST_GOOD_TEMP =
    40.0f;

const float BMS_TEST_DISCONNECTED_TEMP =
    650.0f;


// ================================================================
// TEST CASE ENUM
// ================================================================

enum BMSTestCase {

    TEST_NORMAL,

    TEST_UNDERVOLTAGE,

    TEST_OVERVOLTAGE,

    TEST_LOW_TEMP,

    TEST_HIGH_TEMP,

    TEST_DISCONNECTED_TEMP,

    TEST_LOW_VOLT_SAFE,

    TEST_HIGH_VOLT_SAFE,

    TEST_LOW_TEMP_SAFE,

    TEST_HIGH_TEMP_SAFE
};


// Current test.

BMSTestCase currentBMSTest =
    TEST_NORMAL;


// Simulated vehicle state.

int testVCUState =
    0;


// ================================================================
// SET A PHYSICAL / ENGINEERING VALUE
// ================================================================

void setTestPhysicalValue(
    StateSignal &signal,
    float value
) {

    signal =
        value;
}


// ================================================================
// ALL 90 VOLTAGE SIGNALS
// ================================================================

#define BMS_FOR_EACH_VOLTAGE_SIGNAL(X) \
    X(BMS_module1Cell1Volt)            \
    X(BMS_module1Cell2Volt)            \
    X(BMS_module1Cell3Volt)            \
    X(BMS_module1Cell4Volt)            \
    X(BMS_module1Cell5Volt)            \
    X(BMS_module1Cell6Volt)            \
    X(BMS_module1Cell7Volt)            \
    X(BMS_module1Cell8Volt)            \
    X(BMS_module1Cell9Volt)            \
    X(BMS_module1Cell10Volt)           \
    X(BMS_module1Cell11Volt)           \
    X(BMS_module1Cell12Volt)           \
    X(BMS_module1Cell13Volt)           \
    X(BMS_module1Cell14Volt)           \
    X(BMS_module1Cell15Volt)           \
    X(BMS_module1Cell16Volt)           \
    X(BMS_module1Cell17Volt)           \
    X(BMS_module1Cell18Volt)           \
    X(BMS_module2Cell1Volt)            \
    X(BMS_module2Cell2Volt)            \
    X(BMS_module2Cell3Volt)            \
    X(BMS_module2Cell4Volt)            \
    X(BMS_module2Cell5Volt)            \
    X(BMS_module2Cell6Volt)            \
    X(BMS_module2Cell7Volt)            \
    X(BMS_module2Cell8Volt)            \
    X(BMS_module2Cell9Volt)            \
    X(BMS_module2Cell10Volt)           \
    X(BMS_module2Cell11Volt)           \
    X(BMS_module2Cell12Volt)           \
    X(BMS_module2Cell13Volt)           \
    X(BMS_module2Cell14Volt)           \
    X(BMS_module2Cell15Volt)           \
    X(BMS_module2Cell16Volt)           \
    X(BMS_module2Cell17Volt)           \
    X(BMS_module2Cell18Volt)           \
    X(BMS_module3Cell1Volt)            \
    X(BMS_module3Cell2Volt)            \
    X(BMS_module3Cell3Volt)            \
    X(BMS_module3Cell4Volt)            \
    X(BMS_module3Cell5Volt)            \
    X(BMS_module3Cell6Volt)            \
    X(BMS_module3Cell7Volt)            \
    X(BMS_module3Cell8Volt)            \
    X(BMS_module3Cell9Volt)            \
    X(BMS_module3Cell10Volt)           \
    X(BMS_module3Cell11Volt)           \
    X(BMS_module3Cell12Volt)           \
    X(BMS_module3Cell13Volt)           \
    X(BMS_module3Cell14Volt)           \
    X(BMS_module3Cell15Volt)           \
    X(BMS_module3Cell16Volt)           \
    X(BMS_module3Cell17Volt)           \
    X(BMS_module3Cell18Volt)           \
    X(BMS_module4Cell1Volt)            \
    X(BMS_module4Cell2Volt)            \
    X(BMS_module4Cell3Volt)            \
    X(BMS_module4Cell4Volt)            \
    X(BMS_module4Cell5Volt)            \
    X(BMS_module4Cell6Volt)            \
    X(BMS_module4Cell7Volt)            \
    X(BMS_module4Cell8Volt)            \
    X(BMS_module4Cell9Volt)            \
    X(BMS_module4Cell10Volt)           \
    X(BMS_module4Cell11Volt)           \
    X(BMS_module4Cell12Volt)           \
    X(BMS_module4Cell13Volt)           \
    X(BMS_module4Cell14Volt)           \
    X(BMS_module4Cell15Volt)           \
    X(BMS_module4Cell16Volt)           \
    X(BMS_module4Cell17Volt)           \
    X(BMS_module4Cell18Volt)           \
    X(BMS_module5Cell1Volt)            \
    X(BMS_module5Cell2Volt)            \
    X(BMS_module5Cell3Volt)            \
    X(BMS_module5Cell4Volt)            \
    X(BMS_module5Cell5Volt)            \
    X(BMS_module5Cell6Volt)            \
    X(BMS_module5Cell7Volt)            \
    X(BMS_module5Cell8Volt)            \
    X(BMS_module5Cell9Volt)            \
    X(BMS_module5Cell10Volt)           \
    X(BMS_module5Cell11Volt)           \
    X(BMS_module5Cell12Volt)           \
    X(BMS_module5Cell13Volt)           \
    X(BMS_module5Cell14Volt)           \
    X(BMS_module5Cell15Volt)           \
    X(BMS_module5Cell16Volt)           \
    X(BMS_module5Cell17Volt)           \
    X(BMS_module5Cell18Volt)


// ================================================================
// ALL 90 TEMPERATURE SIGNALS
// ================================================================

#define BMS_FOR_EACH_TEMP_SIGNAL(X) \
    X(BMS_module1Cell1Temp)         \
    X(BMS_module1Cell2Temp)         \
    X(BMS_module1Cell3Temp)         \
    X(BMS_module1Cell4Temp)         \
    X(BMS_module1Cell5Temp)         \
    X(BMS_module1Cell6Temp)         \
    X(BMS_module1Cell7Temp)         \
    X(BMS_module1Cell8Temp)         \
    X(BMS_module1Cell9Temp)         \
    X(BMS_module1Cell10Temp)        \
    X(BMS_module1Cell11Temp)        \
    X(BMS_module1Cell12Temp)        \
    X(BMS_module1Cell13Temp)        \
    X(BMS_module1Cell14Temp)        \
    X(BMS_module1Cell15Temp)        \
    X(BMS_module1Cell16Temp)        \
    X(BMS_module1Cell17Temp)        \
    X(BMS_module1Cell18Temp)        \
    X(BMS_module2Cell1Temp)         \
    X(BMS_module2Cell2Temp)         \
    X(BMS_module2Cell3Temp)         \
    X(BMS_module2Cell4Temp)         \
    X(BMS_module2Cell5Temp)         \
    X(BMS_module2Cell6Temp)         \
    X(BMS_module2Cell7Temp)         \
    X(BMS_module2Cell8Temp)         \
    X(BMS_module2Cell9Temp)         \
    X(BMS_module2Cell10Temp)        \
    X(BMS_module2Cell11Temp)        \
    X(BMS_module2Cell12Temp)        \
    X(BMS_Module2Cell13Temp)        \
    X(BMS_module2Cell14Temp)        \
    X(BMS_module2Cell15Temp)        \
    X(BMS_module2Cell16Temp)        \
    X(BMS_module2Cell17Temp)        \
    X(BMS_module2Cell18Temp)        \
    X(BMS_module3Cell1Temp)         \
    X(BMS_module3Cell2Temp)         \
    X(BMS_module3Cell3Temp)         \
    X(BMS_module3Cell4Temp)         \
    X(BMS_module3Cell5Temp)         \
    X(BMS_module3Cell6Temp)         \
    X(BMS_module3Cell7Temp)         \
    X(BMS_module3Cell8Temp)         \
    X(BMS_module3Cell9Temp)         \
    X(BMS_module3Cell10Temp)        \
    X(BMS_module3Cell11Temp)        \
    X(BMS_module3Cell12Temp)        \
    X(BMS_module3Cell13Temp)        \
    X(BMS_module3Cell14Temp)        \
    X(BMS_module3Cell15Temp)        \
    X(BMS_module3Cell16Temp)        \
    X(BMS_module3Cell17Temp)        \
    X(BMS_module3Cell18Temp)        \
    X(BMS_module4Cell1Temp)         \
    X(BMS_module4Cell2Temp)         \
    X(BMS_module4Cell3Temp)         \
    X(BMS_module4Cell4Temp)         \
    X(BMS_module4Cell5Temp)         \
    X(BMS_module4Cell6Temp)         \
    X(BMS_module4Cell7Temp)         \
    X(BMS_module4Cell8Temp)         \
    X(BMS_module4Cell9Temp)         \
    X(BMS_module4Cell10Temp)        \
    X(BMS_module4Cell11Temp)        \
    X(BMS_module4Cell12Temp)        \
    X(BMS_module4Cell13Temp)        \
    X(BMS_module4Cell14Temp)        \
    X(BMS_module4Cell15Temp)        \
    X(BMS_module4Cell16Temp)        \
    X(BMS_module4Cell17Temp)        \
    X(BMS_module4Cell18Temp)        \
    X(BMS_module5Cell1Temp)         \
    X(BMS_module5Cell2Temp)         \
    X(BMS_module5Cell3Temp)         \
    X(BMS_module5Cell4Temp)         \
    X(BMS_module5Cell5Temp)         \
    X(BMS_module5Cell6Temp)         \
    X(BMS_module5Cell7Temp)         \
    X(BMS_module5Cell8Temp)         \
    X(BMS_module5Cell9Temp)         \
    X(BMS_module5Cell10Temp)        \
    X(BMS_module5Cell11Temp)        \
    X(BMS_module5Cell12Temp)        \
    X(BMS_module5Cell13Temp)        \
    X(BMS_module5Cell14Temp)        \
    X(BMS_module5Cell15Temp)        \
    X(BMS_module5Cell16Temp)        \
    X(BMS_module5Cell17Temp)        \
    X(BMS_module5Cell18Temp)


// ================================================================
// SET ALL CELL VOLTAGES
// ================================================================

void setAllCellVoltages(
    float value
) {

#define SET_ONE_VOLTAGE(signal) \
    setTestPhysicalValue(signal, value);

    BMS_FOR_EACH_VOLTAGE_SIGNAL(
        SET_ONE_VOLTAGE
    )

#undef SET_ONE_VOLTAGE
}


// ================================================================
// SET ALL CELL TEMPERATURES
// ================================================================

void setAllCellTemperatures(
    float value
) {

#define SET_ONE_TEMP(signal) \
    setTestPhysicalValue(signal, value);

    BMS_FOR_EACH_TEMP_SIGNAL(
        SET_ONE_TEMP
    )

#undef SET_ONE_TEMP
}


// ================================================================
// RESET ALL CELLS TO NORMAL
// ================================================================

void setBMSNormal() {

    setAllCellVoltages(
        BMS_TEST_NORMAL_VOLTAGE
    );

    setAllCellTemperatures(
        BMS_TEST_NORMAL_TEMP
    );
}


// ================================================================
// APPLY CURRENT TEST
// ================================================================

void applyBMSTest() {

    // Always begin from a known-good state.

    setBMSNormal();


    switch (
        currentBMSTest
    ) {


        // ========================================================
        // NORMAL
        // ========================================================

        case TEST_NORMAL:

            // Everything remains normal.

            break;


        // ========================================================
        // UNDERVOLTAGE
        // ========================================================

        case TEST_UNDERVOLTAGE:

            setTestPhysicalValue(
                BMS_module1Cell1Volt,
                BMS_TEST_UNDERVOLTAGE
            );

            break;


        // ========================================================
        // OVERVOLTAGE
        // ========================================================

        case TEST_OVERVOLTAGE:

            setTestPhysicalValue(
                BMS_module1Cell1Volt,
                BMS_TEST_OVERVOLTAGE
            );

            break;


        // ========================================================
        // LOW TEMPERATURE
        // ========================================================

        case TEST_LOW_TEMP:

            setTestPhysicalValue(
                BMS_module1Cell1Temp,
                BMS_TEST_LOW_TEMP
            );

            break;


        // ========================================================
        // HIGH TEMPERATURE
        // ========================================================

        case TEST_HIGH_TEMP:

            setTestPhysicalValue(
                BMS_module1Cell1Temp,
                BMS_TEST_HIGH_TEMP
            );

            break;


        // ========================================================
        // DISCONNECTED TEMPERATURE
        // ========================================================

        case TEST_DISCONNECTED_TEMP:

            setTestPhysicalValue(
                BMS_module1Cell1Temp,
                BMS_TEST_DISCONNECTED_TEMP
            );

            break;


        // ========================================================
        // LOWEST SAFE VOLTAGE
        // ========================================================

        case TEST_LOW_VOLT_SAFE:

            setTestPhysicalValue(
                BMS_module1Cell1Volt,
                BMS_TEST_LOWEST_GOOD_VOLTAGE
            );

            break;


        // ========================================================
        // HIGHEST SAFE VOLTAGE
        // ========================================================

        case TEST_HIGH_VOLT_SAFE:

            setTestPhysicalValue(
                BMS_module1Cell1Volt,
                BMS_TEST_HIGHEST_GOOD_VOLTAGE
            );

            break;


        // ========================================================
        // LOWEST SAFE TEMPERATURE
        // ========================================================

        case TEST_LOW_TEMP_SAFE:

            setTestPhysicalValue(
                BMS_module1Cell1Temp,
                BMS_TEST_LOWEST_GOOD_TEMP
            );

            break;


        // ========================================================
        // HIGHEST SAFE TEMPERATURE
        // ========================================================

        case TEST_HIGH_TEMP_SAFE:

            setTestPhysicalValue(
                BMS_module1Cell1Temp,
                BMS_TEST_HIGHEST_GOOD_TEMP
            );

            break;
    }


    /*
     * VCU_vehicleState has factor 1.
     *
     * Therefore direct assignment gives both:
     *
     *      value()     == testVCUState
     *      can_value() == testVCUState
     */

    VCU_vehicleState =
        testVCUState;
}


// ================================================================
// GET CURRENT TEST NAME
// ================================================================

const char* getBMSTestName() {

    switch (
        currentBMSTest
    ) {

        case TEST_NORMAL:

            return "NORMAL";


        case TEST_UNDERVOLTAGE:

            return "UNDERVOLTAGE";


        case TEST_OVERVOLTAGE:

            return "OVERVOLTAGE";


        case TEST_LOW_TEMP:

            return "LOW TEMPERATURE";


        case TEST_HIGH_TEMP:

            return "HIGH TEMPERATURE";


        case TEST_DISCONNECTED_TEMP:

            return "DISCONNECTED TEMPERATURE";


        case TEST_LOW_VOLT_SAFE:

            return "LOWEST SAFE VOLTAGE";


        case TEST_HIGH_VOLT_SAFE:

            return "HIGHEST SAFE VOLTAGE";


        case TEST_LOW_TEMP_SAFE:

            return "LOWEST SAFE TEMPERATURE";


        case TEST_HIGH_TEMP_SAFE:

            return "HIGHEST SAFE TEMPERATURE";


        default:

            return "UNKNOWN";
    }
}


// ================================================================
// PRINT CURRENT TEST VALUES
// ================================================================

void printBMSTestValues() {

    Serial.println();

    Serial.println(
        "================================================"
    );

    Serial.println(
        "CURRENT BMS TEST"
    );

    Serial.println(
        "================================================"
    );


    Serial.print(
        "Test: "
    );

    Serial.println(
        getBMSTestName()
    );


    Serial.println();


    Serial.print(
        "VCU state target: "
    );

    Serial.println(
        testVCUState
    );


    Serial.print(
        "VCU value(): "
    );

    Serial.println(
        VCU_vehicleState.value()
    );


    Serial.print(
        "VCU can_value(): "
    );

    Serial.println(
        VCU_vehicleState.can_value()
    );


    Serial.println();


    // ------------------------------------------------------------
    // VOLTAGE
    // ------------------------------------------------------------

    Serial.println(
        "Module 1 Cell 1 Voltage:"
    );


    Serial.print(
        "  value()     = "
    );

    Serial.println(
        BMS_module1Cell1Volt.value(),
        4
    );


    Serial.print(
        "  can_value() = "
    );

    Serial.println(
        BMS_module1Cell1Volt.can_value()
    );


    Serial.println();


    // ------------------------------------------------------------
    // TEMPERATURE
    // ------------------------------------------------------------

    Serial.println(
        "Module 1 Cell 1 Temperature:"
    );


    Serial.print(
        "  value()     = "
    );

    Serial.println(
        BMS_module1Cell1Temp.value(),
        4
    );


    Serial.print(
        "  can_value() = "
    );

    Serial.println(
        BMS_module1Cell1Temp.can_value()
    );


    Serial.println();

    Serial.println(
        "================================================"
    );

    Serial.println();
}


// ================================================================
// VERIFY NORMAL ENGINEERING VALUES
// ================================================================

void printBMSValueCheck() {

    Serial.println();

    Serial.println(
        "================================================"
    );

    Serial.println(
        "STATECAN TEST VALUE CHECK"
    );

    Serial.println(
        "================================================"
    );


    Serial.println();

    Serial.println(
        "NORMAL targets:"
    );


    Serial.print(
        "Voltage target value(): "
    );

    Serial.println(
        BMS_TEST_NORMAL_VOLTAGE,
        4
    );


    Serial.print(
        "Voltage actual value(): "
    );

    Serial.println(
        BMS_module1Cell1Volt.value(),
        4
    );


    Serial.print(
        "Voltage actual can_value(): "
    );

    Serial.println(
        BMS_module1Cell1Volt.can_value()
    );


    Serial.println();


    Serial.print(
        "Temperature target value(): "
    );

    Serial.println(
        BMS_TEST_NORMAL_TEMP,
        4
    );


    Serial.print(
        "Temperature actual value(): "
    );

    Serial.println(
        BMS_module1Cell1Temp.value(),
        4
    );


    Serial.print(
        "Temperature actual can_value(): "
    );

    Serial.println(
        BMS_module1Cell1Temp.can_value()
    );


    Serial.println();


    if (
        fabs(
            BMS_module1Cell1Volt.value()
            -
            BMS_TEST_NORMAL_VOLTAGE
        )
        <
        0.0005f
    ) {

        Serial.println(
            "Voltage physical injection: PASS"
        );

    } else {

        Serial.println(
            "Voltage physical injection: FAIL"
        );
    }


    if (
        fabs(
            BMS_module1Cell1Temp.value()
            -
            BMS_TEST_NORMAL_TEMP
        )
        <
        0.05f
    ) {

        Serial.println(
            "Temperature physical injection: PASS"
        );

    } else {

        Serial.println(
            "Temperature physical injection: FAIL"
        );
    }


    Serial.println();

    Serial.println(
        "================================================"
    );

    Serial.println();
}


// ================================================================
// PRINT SERIAL MENU
// ================================================================

void printBMSTestMenu() {

    Serial.println();

    Serial.println(
        "================================================"
    );

    Serial.println(
        "        BMS MASTER BENCH TEST MODE"
    );

    Serial.println(
        "================================================"
    );


    Serial.println();

    Serial.println(
        "SAFETY TESTS"
    );

    Serial.println();


    Serial.println(
        "n = Normal"
    );

    Serial.println(
        "    All cell voltages = 3.70 V"
    );

    Serial.println(
        "    All cell temperatures = 25.0 C"
    );

    Serial.println(
        "    EXPECTED: NO FAULT"
    );


    Serial.println();


    Serial.println(
        "u = Undervoltage"
    );

    Serial.println(
        "    M1C1 voltage = 2.49 V"
    );

    Serial.println(
        "    EXPECTED: FAULT / code 101"
    );


    Serial.println();


    Serial.println(
        "o = Overvoltage"
    );

    Serial.println(
        "    M1C1 voltage = 4.21 V"
    );

    Serial.println(
        "    EXPECTED: FAULT / code 201"
    );


    Serial.println();


    Serial.println(
        "l = Low temperature"
    );

    Serial.println(
        "    M1C1 temperature = 0.0 C"
    );

    Serial.println(
        "    EXPECTED: FAULT / code 301"
    );


    Serial.println();


    Serial.println(
        "h = High temperature"
    );

    Serial.println(
        "    M1C1 temperature = 45.0 C"
    );

    Serial.println(
        "    EXPECTED: FAULT / code 401"
    );


    Serial.println();


    Serial.println(
        "d = Disconnected temperature"
    );

    Serial.println(
        "    M1C1 temperature = 650.0 C"
    );

    Serial.println(
        "    EXPECTED: NO FAULT from this sensor"
    );


    Serial.println();

    Serial.println(
        "------------------------------------------------"
    );

    Serial.println(
        "SAFE LIMIT TESTS"
    );

    Serial.println();


    Serial.println(
        "a = Lowest safe voltage"
    );

    Serial.println(
        "    M1C1 voltage = 2.50 V"
    );

    Serial.println(
        "    EXPECTED: NO FAULT"
    );


    Serial.println();


    Serial.println(
        "b = Highest safe voltage"
    );

    Serial.println(
        "    M1C1 voltage = 4.20 V"
    );

    Serial.println(
        "    EXPECTED: NO FAULT"
    );


    Serial.println();


    Serial.println(
        "c = Lowest safe temperature"
    );

    Serial.println(
        "    M1C1 temperature = 1.0 C"
    );

    Serial.println(
        "    EXPECTED: NO FAULT"
    );


    Serial.println();


    Serial.println(
        "e = Highest safe temperature"
    );

    Serial.println(
        "    M1C1 temperature = 40.0 C"
    );

    Serial.println(
        "    EXPECTED: NO FAULT"
    );


    Serial.println();

    Serial.println(
        "------------------------------------------------"
    );

    Serial.println(
        "VCU VEHICLE STATES"
    );

    Serial.println();


    Serial.println(
        "0 = Vehicle state 0"
    );

    Serial.println(
        "1 = Vehicle state 1 / Precharge"
    );

    Serial.println(
        "2 = Vehicle state 2 / Operational"
    );

    Serial.println(
        "3 = Vehicle state 3 / Operational"
    );

    Serial.println(
        "4 = Vehicle state 4 / Discharge"
    );

    Serial.println(
        "5 = Vehicle state 5 / Discharge"
    );

    Serial.println(
        "6 = Vehicle state 6 / Discharge"
    );


    Serial.println();

    Serial.println(
        "------------------------------------------------"
    );

    Serial.println(
        "DEBUG"
    );

    Serial.println();


    Serial.println(
        "s = Verify target vs actual value()"
    );

    Serial.println(
        "p = Print current test values"
    );

    Serial.println(
        "? = Print this menu"
    );


    Serial.println();

    Serial.println(
        "================================================"
    );

    Serial.println();
}


// ================================================================
// SELECT A TEST
// ================================================================

void selectBMSTest(
    BMSTestCase test
) {

    currentBMSTest =
        test;


    applyBMSTest();


    printBMSTestValues();
}


// ================================================================
// INITIALIZE TEST MODE
// ================================================================

void bmsTestBegin() {

    currentBMSTest =
        TEST_NORMAL;


    testVCUState =
        0;


    applyBMSTest();


    Serial.println();

    Serial.println(
        "************************************************"
    );

    Serial.println(
        "*                                              *"
    );

    Serial.println(
        "*         BMS BENCH TEST MODE ENABLED          *"
    );

    Serial.println(
        "*                                              *"
    );

    Serial.println(
        "************************************************"
    );


    Serial.println();


    Serial.println(
        "Accumulator CAN data is NOT required."
    );

    Serial.println(
        "Safety logic is using simulated physical values."
    );


    Serial.println();


    printBMSTestMenu();


    printBMSValueCheck();
}


// ================================================================
// SERIAL COMMAND HANDLER
// ================================================================

void processBMSTestCommand(
    char command
) {

    switch (
        command
    ) {


        // NORMAL

        case 'n':
        case 'N':

            selectBMSTest(
                TEST_NORMAL
            );

            break;


        // UNDERVOLTAGE

        case 'u':
        case 'U':

            selectBMSTest(
                TEST_UNDERVOLTAGE
            );

            break;


        // OVERVOLTAGE

        case 'o':
        case 'O':

            selectBMSTest(
                TEST_OVERVOLTAGE
            );

            break;


        // LOW TEMPERATURE

        case 'l':
        case 'L':

            selectBMSTest(
                TEST_LOW_TEMP
            );

            break;


        // HIGH TEMPERATURE

        case 'h':
        case 'H':

            selectBMSTest(
                TEST_HIGH_TEMP
            );

            break;


        // DISCONNECTED TEMPERATURE

        case 'd':
        case 'D':

            selectBMSTest(
                TEST_DISCONNECTED_TEMP
            );

            break;


        // LOWEST SAFE VOLTAGE

        case 'a':
        case 'A':

            selectBMSTest(
                TEST_LOW_VOLT_SAFE
            );

            break;


        // HIGHEST SAFE VOLTAGE

        case 'b':
        case 'B':

            selectBMSTest(
                TEST_HIGH_VOLT_SAFE
            );

            break;


        // LOWEST SAFE TEMPERATURE

        case 'c':
        case 'C':

            selectBMSTest(
                TEST_LOW_TEMP_SAFE
            );

            break;


        // HIGHEST SAFE TEMPERATURE

        case 'e':
        case 'E':

            selectBMSTest(
                TEST_HIGH_TEMP_SAFE
            );

            break;


        // ========================================================
        // VEHICLE STATES
        // ========================================================

        case '0':

            testVCUState =
                0;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 0"
            );

            break;


        case '1':

            testVCUState =
                1;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 1"
            );

            break;


        case '2':

            testVCUState =
                2;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 2"
            );

            break;


        case '3':

            testVCUState =
                3;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 3"
            );

            break;


        case '4':

            testVCUState =
                4;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 4"
            );

            break;


        case '5':

            testVCUState =
                5;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 5"
            );

            break;


        case '6':

            testVCUState =
                6;

            applyBMSTest();

            Serial.println(
                "VCU vehicle state set to 6"
            );

            break;


        // ========================================================
        // VALUE VERIFICATION
        // ========================================================

        case 's':
        case 'S':

            printBMSValueCheck();

            break;


        // ========================================================
        // PRINT CURRENT VALUES
        // ========================================================

        case 'p':
        case 'P':

            printBMSTestValues();

            break;


        // ========================================================
        // MENU
        // ========================================================

        case '?':

            printBMSTestMenu();

            break;


        // Ignore Serial Monitor line endings.

        case '\r':
        case '\n':
        case ' ':

            break;


        // Unknown command.

        default:

            Serial.print(
                "Unknown BMS test command: "
            );

            Serial.println(
                command
            );

            Serial.println(
                "Enter ? for available commands."
            );

            break;
    }
}


// ================================================================
// TEST UPDATE
// ================================================================

void bmsTestUpdate() {

    /*
     * Reapply the selected test every loop so the test values remain
     * deterministic.
     */

    applyBMSTest();


    /*
     * Process Serial Monitor input.
     */

    if (
        Serial.available() > 0
    ) {

        char command =
            (char)Serial.read();


        processBMSTestCommand(
            command
        );
    }
}


// ================================================================
// END TEST MODE
// ================================================================

#endif // BMS_CAN_TEST_MODE


#endif // BMS_CAN_TEST_MODE_H