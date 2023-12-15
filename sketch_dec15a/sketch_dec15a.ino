int sensorValue;
// set dummy values for numeric light indicator
int sensorLow = 1023;
int sensorHigh = 0;

int buzzer = 8;

const int onboardPin = 13;  // on-board indicator


void setup() {
  Serial.begin(9600);

  // use little led on the board to show 5 seconds passing
  pinMode(onboardPin, OUTPUT);
  digitalWrite(onboardPin, HIGH);

  // do this for five seconds
  while (millis() < 5000) {
    // set the sensor value as what comes from the "A0" spot on the board
    sensorValue = analogRead(A0);

    // calibrate sensor - set light level numeric values as it is in reality
    if (sensorValue > sensorLow) {
      sensorHigh = sensorValue;
    }

    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }

  // turn off indicator led
  digitalWrite(onboardPin, LOW);
}

void loop() {
  delay(100);

  // read the sensor value from the A0 port
  sensorValue = analogRead(A0);

  // map the sensor value to the frequency:
  // sensorValue-  value to map;
  // sensorLow and sensorHigh - bounds;
  // 50 and 4000 - pitch bounds;
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(buzzer, pitch, 20);
  delay(10);
}
