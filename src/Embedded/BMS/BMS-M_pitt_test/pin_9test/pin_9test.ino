#define TEST_PIN_8 8
#define TEST_PIN_9 9

void setup() {
    Serial.begin(112500);

    pinMode(TEST_PIN_8, OUTPUT);
    pinMode(TEST_PIN_9, OUTPUT);

    digitalWrite(TEST_PIN_8, LOW);
    digitalWrite(TEST_PIN_9, LOW);

    Serial.println("Pin 8 and Pin 9 output test started");
}

void loop() {

    // ---------------- HIGH ----------------
    digitalWrite(TEST_PIN_8, HIGH);
    digitalWrite(TEST_PIN_9, HIGH);

    Serial.println("COMMAND: BOTH HIGH");

    Serial.print("Pin 8 digitalRead = ");
    Serial.println(digitalRead(TEST_PIN_8));

    Serial.print("Pin 9 digitalRead = ");
    Serial.println(digitalRead(TEST_PIN_9));

    Serial.println();

    delay(5000);


    // ---------------- LOW ----------------
    digitalWrite(TEST_PIN_8, LOW);
    digitalWrite(TEST_PIN_9, LOW);

    Serial.println("COMMAND: BOTH LOW");

    Serial.print("Pin 8 digitalRead = ");
    Serial.println(digitalRead(TEST_PIN_8));

    Serial.print("Pin 9 digitalRead = ");
    Serial.println(digitalRead(TEST_PIN_9));

    Serial.println();

    delay(5000);
}