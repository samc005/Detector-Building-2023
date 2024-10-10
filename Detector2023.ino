#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define ledBlue 6
#define ledRed 7
#define ledGreen 8


float massOne = 300;
float massTwo = 700;
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
float fsrReading;     // the analog reading from the FSR resistor divider
float V_Out = 0;
float const maxAnalog = 1023;
float const maxVoltage = 5; //V+
float mass;


 void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}


void loop() {
  fsrReading = analogRead(fsrPin);


  V_Out = fsrReading * (maxVoltage / maxAnalog);


  lcd.setCursor(0, 0);
  lcd.print("Voltage = ");
  lcd.print(V_Out);


  lcd.setCursor(0, 1);
  mass = V_OuttoMass(V_Out);
  lcd.print("Mass = ");
  lcd.print(mass); // display to nearest 0.1


  digitalWrite(ledBlue, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);


    if (mass > massTwo) {
      digitalWrite(ledBlue, HIGH);
    }
    else if (mass > massOne) {
      digitalWrite(ledRed, HIGH);
    }
    else
    {
      digitalWrite(ledGreen, HIGH);
    }
  delay(10);


}


float V_OuttoMass(float V_Out) {
  if (V_Out <= 0.1) {
    mass = 30;
    return mass;
  }
  mass = pow(2.71828183,((V_Out+1.19019312)/0.8633822797));
  return mass;
}
