//DENNA KOD UTGÅR FRÅN https://pages.uoregon.edu/torrence/432/task5.html
// Pin to read for button value
#define BUTTON_1 3
#define BUTTON_2 2
const int ledPinR = 10;
const int ledPinY = 9;
int ledStateR = HIGH;
int ledStateY = HIGH;

const int ledPinG = 5;
int adcValue;


// Boolean to show if pin value has changed
// Because this value is changed in the interrupt, must declare as volatile,
// which tells the compiler to always read this from memory, not a register
volatile bool pinChange1; // Communicates from interrupt routine for BUTTON_1
volatile bool pinChange2; // Communicates from interrupt routine for BUTTON_2


// the setup function runs once when you press reset or power the board
void setup() {
  
  // Pin to read button state, use internal pull-up to avoid external resistor
  // This also emulates TTL inputs that float HI.
  // Use INPUT for normal digital input (emulates CMOS input)
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  // Setup the interrupt handler on pin change
  // Must be attached to pin 2 or 3 on Nano
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), pinChangeRoutine1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), pinChangeRoutine2, CHANGE);
}


void loop() {

  // Previous button state (to find changes)
  static bool lastButtonState1; 
  static bool lastButtonState2;

  // Get the logical button value (pressed = true) from debounce routine
  bool buttonValue1 = buttonState1(pinChange1, BUTTON_1);
  bool buttonValue2 = buttonState2(pinChange2, BUTTON_2);

  // Has this changed?
  toggleLED(lastButtonState1, buttonValue1, ledStateR, ledPinR);
  lastButtonState1 = buttonValue1;

  toggleLED(lastButtonState2, buttonValue2, ledStateY, ledPinY);
  lastButtonState2 = buttonValue2;

  adcValue = analogRead(A0);
  analogWrite(ledPinG, map(adcValue, 0, 1023, 0, 255));
}


void toggleLED(bool &lastButtonState, bool buttonValue, int &ledState, int ledPin) {
  // If it is now pressed and was not pressed before, update LED value.
  if (buttonValue && !lastButtonState) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

// Interrupt handler, this is called via the interrupt handler every 
// time a change is detected on the button pin.  Best to do very little here.
void pinChangeRoutine1() {
  pinChange1 = true;
}

void pinChangeRoutine2() {
  pinChange2 = true;
}

bool buttonState1(volatile bool &pinChange, int buttonPin) {

  //8-bit storage used as shift register of past pin values
  static byte pinHistory = 0; 

  // Best guess of debounced button value
  static bool buttonValue = false;  

  // Time (in ms) since Arduino rebooted
  static unsigned long lastTime = 0;
  
  // If no change, just return last value
  if (!pinChange) return buttonValue;

  // Check how long since we last read the pin
  unsigned long currentTime = millis();
  if ((currentTime - lastTime) < 4) return buttonValue;
  lastTime = currentTime;
  
  // Read the pin and push value onto buttonHistory
  pinHistory = (pinHistory << 1);
  if (digitalRead(buttonPin)) bitSet(pinHistory, 0);

  // If the value has been stable for the last 8 x 4ms = 32ms, consider it stable
  // buttonValue reflects whether the button is pressed (true) or not (false)
  if (pinHistory == 0xFF) {
    buttonValue = false;
    pinChange = false;  // Reset this to indicate we are in a stable state
  }
  if (pinHistory == 0x00) {
    buttonValue = true;
    pinChange = false;
  }
  return buttonValue;
}


// repeat for BUTTON_2 + yellow led.
bool buttonState2(volatile bool &pinChange, int buttonPin) {

  static byte pinHistory = 0;
  static bool buttonValue = false;  
  static unsigned long lastTime = 0;
  
  if (!pinChange) return buttonValue;
  unsigned long currentTime = millis();
  if ((currentTime - lastTime) < 4) return buttonValue;
  lastTime = currentTime;
  
  pinHistory = (pinHistory<<1);
  if (digitalRead(BUTTON_2)) bitSet(pinHistory, 0);

  if (pinHistory == 0xFF) {
    buttonValue = false;
    pinChange = false;
  }
  if (pinHistory == 0x00) {
    buttonValue = true;
    pinChange = false;
  }
  return buttonValue;
}
