/*UPPGIFT 1.1 Ta 5Voch GNDfrån din Arduino UNO och lämpliga resistorer och visa att du kan
 tända Diod-R (röd), Diod-G (grön) och Diod-B (blå) var för sig via mjukvara och GPIO
 portar/pinnar som OUTPUT. Loopa och tänd släck alla lysdioder med konstant
 lystid/paus. OBS! Kolla att du dimensionerar lysdiod + resistor så att du kan koppla
 den direkt till utgången. Redovisa beräkning på strömmen.*/

/* Beräkna strömmen: Givet ett framspänningsfall på VfD1 = 2,1V, samt resistor 220 ohm.
KLC: U – VfD1 – R1*ID1 = 0 --> U - VfD1 = R*ID1 --> (U-VfD1)/R = ID1
 --> ID1 (5 - 2,1)/220 = 0,0132 = 13mA.
*/

int ledPinRed = 4;  // ID1 ("Ström (genom) Diod 1")
int ledPinBlue = 5;
int ledPinGreen = 6; 

void setup() {
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
}

void loop() {
  setLed(HIGH, LOW, LOW);
  setLed(LOW, HIGH, LOW);
  setLed(LOW, LOW, HIGH);
}

void setLed(int led1, int led2, int led3) {
  digitalWrite(ledPinRed, led1);
  digitalWrite(ledPinBlue, led2);
  digitalWrite(ledPinGreen, led3);  
  delay(1000);
}