const int channels = 4;
const int inputPin[channels] = {2, 3, 4, 5};
const int outputPin[channels] = {14, 15, 16, 17};
const int ledPin = 13;

int buttonState[channels];
int lastButtonState[channels] = {HIGH, HIGH, HIGH, HIGH};
int reading[channels];

unsigned long lastDebounceTime[channels] = {0, 0, 0, 0};
unsigned long debounceDelay = 100;

void setup() {
  // Serial.begin(115200);
  // Serial.println("Adafruit Sound Board!");
  // Initialize pins
  for (int i = 0; i < channels; i++) {
    pinMode(inputPin[i], INPUT_PULLUP);
    pinMode(outputPin[i], OUTPUT);
    digitalWrite(outputPin[i], HIGH);
  }
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

}

void loop() {
  for (uint8_t i = 0; i < channels; i++) {
    reading[i] = digitalRead(inputPin[i]);

    if (reading[i] != lastButtonState[i]) {
      // Serial.print("State change ");
      // Serial.print(inputPin[i]);
      // Serial.print(" went ");
      // Serial.println(reading[i]);

    // reset the debouncing timer
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading[i] != buttonState[i]) {
        buttonState[i] = reading[i];

        // only toggle the LED if the new button state is LOW
        if (buttonState[i] ==LOW) {
          digitalWrite(outputPin[i], LOW);
          digitalWrite(ledPin, HIGH);
          // Serial.print("Pressed button ");
          // Serial.println(inputPin[i]);
          delay(200);
          digitalWrite(outputPin[i], HIGH);
          digitalWrite(ledPin, LOW);
          // Serial.println("Pulse end");
        }
      }
    }
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState[i] = reading[i];
  }
  delay(1);
}
