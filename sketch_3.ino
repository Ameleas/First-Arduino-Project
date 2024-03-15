/* DELUPPGIFT 1.3: Koppla upp hela kretsen med lämpliga resistor-värden och skriv en väldigt enkel
 Arduinoapplikation som visar att
 a. Tryckknapp kopplad till tex GPIO1 (valfri pinne) går att läsa av (tex: genom att
 den styr Diod-R), På/AV. Knappen ska TOGGLA På/Av så att lysdioden
 stannar i tillståndet På/Av då knappen inte rörs.
 b. Tryckknapp kopplad till tex GPIO2 (valfri pinne) går att läsa av (tex: genom att
 den styr Diod-G), På/AV. Knappen ska TOGGLA På/Av så att lysdioden
 stannar i tillståndet På/Av då knappen inte rörs.
 c. Vridpotentiometers värde går att läsa av (tex: genom att den styr Diod-B), Läs
 in ADC på A0, mata ut PWM på pinne 3.*/


const int buttonPin1 = 12;
const int ledPinR = 9;
boolean redLedOn = false;

const int buttonPin2 = 7;
const int ledPinY = 6;
boolean yellowLedOn = false;

const int debounceDelay = 10;

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
  // Red light push button 1
  toggleButton(buttonPin1, ledPinR, redLedOn);

  // yellow light push button 2
  toggleButton(buttonPin2, ledPinY, yellowLedOn);
  
  // green light controlled by potentiometer
  adcValue = analogRead(A0);
  analogWrite(ledPinG, map(adcValue, 0, 1023, 0, 255));
}


void toggleButton(int buttonPin, int ledPin, boolean &ledOn) {
  if (digitalRead(buttonPin) == LOW) {       // if the button is pressed
    delay(10);                                // delay to skip the bounce
    if(digitalRead(buttonPin) == LOW) {      // confirm
      ledOn = reverseLED(ledPin, ledOn); // reverse
      while(digitalRead(buttonPin) == LOW);  // wait for releasing.
      delay(10);
    }
  }
}

boolean reverseLED(int ledPin, boolean isLighting) {
  if (isLighting) {
    digitalWrite(ledPin, LOW);
    return false;
  }
  else {
    digitalWrite(ledPin, HIGH);
    return true;
  }
}
