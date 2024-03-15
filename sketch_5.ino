/*DELUPPGIFT 3.5 Använd din kommando-implementation från Inlämningsuppgift 3 och implementera
 kommandon för att enabla/disable knappar och vridpotentiometer, samt att
 tända/släcka lysdioderna, samt sätta intensiteten på en lysdiod med PWM. Eka
 tillbaka status på serieporten. */


const int buttonPin1 = 12;
const int ledPinR = 9;
int buttonState1;
int lastButtonState1 = LOW;
int ledStateR = LOW;
bool button1Enabled = true;

const int buttonPin2 = 7;
const int ledPinY = 6;
int buttonState2;
int lastButtonState2 = LOW;
int ledStateY = LOW;
bool button2Enabled = true;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 10;

const int ledPinG = 3;
int adcValue;
bool potentiometerEnabled = true;

void toggleButton(int buttonPin, int ledPin, int &buttonState, int &lastButtonState, int &ledState);
void handleCommand(String command);
void buttonCommand(int value, char toggle);
void ledCommand(int value, char toggle);
void potentiometerCommand(char toggle);


void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (button1Enabled) {
    toggleButton(buttonPin1, ledPinR, buttonState1, lastButtonState1, ledStateR);
  }
  if (button2Enabled) {
    toggleButton(buttonPin2, ledPinY, buttonState2, lastButtonState2, ledStateY);
  }
  if (potentiometerEnabled) {
    adcValue = analogRead(A0);
    analogWrite(ledPinG, map(adcValue, 0, 1023, 0, 255));
  }
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    handleCommand(command);
  }
}

void handleCommand(String command) {
  int value;
  char toggle;

  // ENABLE/DISABLE BUTTONS
  if (sscanf(command.c_str(), "button %d %c", &value, &toggle) == 2) {
    buttonCommand(value, toggle);
  }
  
  //HANDLE LED's
  else if (sscanf(command.c_str(), "led %d %c", &value, &toggle) == 2) {
    ledCommand(value, toggle);
  }

  // ENABLE/DISABLE POTENTIOMETER
  else if (sscanf(command.c_str(), "potentiometer %c", &toggle) == 1) {
    potentiometerCommand(toggle);
  }

  // CONTROL LED BY PWM-VALUE
  else if (sscanf(command.c_str(), "pwm %d", &value) == 1) {
    if (value >= 0 && value <= 255) {
      analogWrite(ledPinG, value);
    }
    else {
      Serial.println("valid range 0 - 255.");
    }
  }
  else {
    Serial.println("Not a valid command.");
  }
}


void buttonCommand(int value, char toggle) {
  if (value == 1 && toggle == 'd') {
    button1Enabled = false;
    Serial.println("Button 1 disabled. Control led by typing 'led 1'+ 'p' = power, 'o' = off.");
  }
  else if (value == 2 && toggle == 'd') {
    button2Enabled = false;
    Serial.println("Button 2 disabled. Control led by typing 'led 2'+ 'p' = power, 'o' = off.");
  }
  else if (value ==  1 && toggle == 'e') {
    button1Enabled = true;
    Serial.println("Button 1 enabled. Control led by button.");
  }
  else if (value ==  2 && toggle == 'e') {
    button2Enabled = true;
    Serial.println("Button 2 enabled. Control led by button.");
  }
}


void ledCommand(int value, char toggle) {
  if (value == 1 && toggle == 'p') {
    digitalWrite(ledPinR, HIGH);
  }
  else if (value == 2 && toggle == 'p') {
    digitalWrite(ledPinY, HIGH);
  }
  else if (value == 1 && toggle == 'o') {
    digitalWrite(ledPinR, LOW);
  }
  else if (value == 2 && toggle == 'o') {
    digitalWrite(ledPinY, LOW);
  }
  else {
    Serial.println("Not valid command, led +\n1 = red\n2 = yellow\np = power\no = off\nDid you remember to disable button first?\nTry again.");
  }
}


void potentiometerCommand(char toggle) {
  if (toggle == 'd') {
    potentiometerEnabled = false;
    Serial.println("Potentiometer disabled. Control led by typing 'pwm' + value range 0-255.");
  }
  else if (toggle == 'e') {
    potentiometerEnabled = true;
    Serial.println("Potentiometer enabled.");
  }
  else {
    Serial.println("use 'd' for disable or 'e' for enable.");
  }
}


void toggleButton(int buttonPin, int ledPin, int &buttonState, int &lastButtonState, int &ledState) {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // record current time.
  }
  // check if debounce delay has passed.
  if ((millis() - lastDebounceTime) > debounceDelay) {
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
