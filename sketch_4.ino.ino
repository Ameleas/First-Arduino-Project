/*the debounce function of this code has been borrowed (and slightly modified) from:
  created 21 Nov 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Limor Fried
  modified 28 Dec 2012
  by Mike Walters
  modified 30 Aug 2016
  by Arturo Guadalupi
  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
*/


const int buttonPin1 = 12;
const int ledPinR = 9;
int buttonState1;
int lastButtonState1 = LOW;
int ledStateR = HIGH;

const int buttonPin2 = 7;
const int ledPinY = 6;
int buttonState2;
int lastButtonState2 = LOW;
int ledStateY = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

const int ledPinG = 3;
int adcValue;

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);
}

void loop() {
  // Red light + debounced button.
  debounceButton(buttonPin1, ledPinR, buttonState1, lastButtonState1, ledStateR);

  // Yellow light + debounced button.
  debounceButton(buttonPin2, ledPinY, buttonState2, lastButtonState2, ledStateY);

  // Green light + potentiometer.
  adcValue = analogRead(A0);
  analogWrite(ledPinG, map(adcValue, 0, 1023, 0, 255));
}

void debounceButton(int buttonPin, int ledPin, int &buttonState, int &lastButtonState, int &ledState) {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // record current time.
  }
  // check if debounce delay has passed.
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    if (reading != buttonState) { // check if button state has changed.
      buttonState = reading;
      if (buttonState == HIGH) { // toggle state of led when button is pressed (HIGH).
        ledState = !ledState;
      }
    }
  }
  //set the lED:
  digitalWrite(ledPin, ledState);
  // save the reading. Next time though the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

