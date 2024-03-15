/*DELUPPGIFT 1.2 Ta 5V och GND från din Arduino UNO och bevisa att du kan använda
 vridpotentiometern som spänningsdelare, och mät in värdet på ADC via pinne A0 tex
 med 300 msec*/
 
void setup() {
  Serial.begin(9600);
  Serial.println("UNO is ready!");
}

void loop() {
  int adcValue = analogRead(A0);
  float voltage = adcValue * (5.0 / 1023.0);

  Serial.print("Digital value: ");
  Serial.println(adcValue);
  Serial.print("Input voltage:");
  Serial.println(voltage);
  delay(300);
}
