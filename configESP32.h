// backend url
#define BACKEND_URL "<YOUR BACKEND URL>"
#define BACKEND_KEY "<YOUR BACKEND KEY>"

// data wifi
#define SSID "<YOUR WIFI NAME>"
#define PASSWORD "<YOUR WIFI PASSWORD>"

// pin sensor
const int SENSOR_INPUT = 34;
const int LED_GREEN = 14;
const int LED_YELLOW = 12;
const int LED_RED = 13;

// status sensor
const int KERING_HIGH = 4096;
const int KERING_LOW = 0;
const int AGAK_LEMBAP_HIGH = 3276;
const int AGAK_LEMBAP_LOW = 2458;
const int LEMBAP_HIGH = 2457;
const int LEMBAP_LOW = 1639;
const int TERLALU_LEMBAP_HIGH = 1638;
const int TERLALU_LEMBAP_LOW = 820;

int getSensorPercent(int sensorValue) {
  int soilMoisturePercent = map(sensorValue, KERING_LOW, KERING_HIGH, 0, 100);
  return constrain(soilMoisturePercent, 0, 100);
}

void switchLED(const char* state) {
  if (state == "GREEN") {
    // set conditional led
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);

    // set led
    digitalWrite(LED_GREEN, HIGH);
  } else if (state == "YELLOW") {
    // set conditional led
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    // set led
    digitalWrite(LED_YELLOW, HIGH);
  } else if (state == "RED") {
    // set conditional led
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);

    // set led
    digitalWrite(LED_RED, HIGH);
  } else {
    // default case
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  }
}