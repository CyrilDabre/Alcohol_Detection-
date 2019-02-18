#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
const int LEDRED = D2;
const int LEGREEN = D3;
const int Buzzer = D8;
const int Relay = D4;
const int sensorin = A0;
LiquidCrystal_I2C lcd(0x27,16, 2);
char auth[] = "Authentication token generate by blynk eg: bdfdd67f8726439d850ce62d2275ec84";
char ssid[] = "wifi name";
char pass[] = "your wifi password if any";
BlynkTimer timer;
void myTimerEvent()
{
  int sensorData = analogRead(sensorin);
  Serial.println(sensorData);
  Blynk.virtualWrite(V5, sensorData);
  if (sensorData > 500){
    digitalWrite(LEDRED,HIGH);
    digitalWrite(LEDGREEN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("You are drunk!");
    tone(8, 440, 200);
    delay(300);
    noTone(8);
    tone(8, 494, 500);
    delay(300);
    noTone(8);
    tone(8, 523, 300);
    delay(200);
    tone(8, 440, 200);
    delay(300);
    digitalWrite(Relay, LOW);
    delay(300);
    }
  else{
    digitalWrite(LEDRED,LOW);
    digitalWrite(LEDGREEN, HIGH) ;
    lcd.setCursor(0, 1);
    lcd.print("You are sober!");
    delay(200);
     }
}
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Alcohol Detector");
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  pinMode(Buzzer, OUTPUT) ;
  pinMode(Relay, OUTPUT);
  pinMode(sensorin, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}
void loop()
{
  Blynk.run();
  timer.run();
}
