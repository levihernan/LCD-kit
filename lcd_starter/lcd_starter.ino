#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

#define DHTPIN 22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

BH1750 lightMeter;

#define RELAYPIN 23

float hum;  
float temp; 
float lux;  

int waterLevel;

const int rs = 4, en = 5, d4 = 6, d5 = 3, d6 = 7, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  Serial.begin(9600);
  
  //BEEP
  pinMode(10, OUTPUT);

  //DHT22
  pinMode(DHTPIN, INPUT);
  dht.begin();

  //LUX
  Wire.begin();
  lightMeter.begin();

  //RELAY
  pinMode(RELAYPIN, OUTPUT);

  
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("my life's a mess... ");
}

void loop() {
  // Turn off the cursor:
  lcd.noCursor();
  delay(500);
  // Turn on the cursor:
  lcd.cursor();
  delay(500);

  //DHT22
  hum = dht.readHumidity();
  temp= dht.readTemperature();

  //Water sensor
  waterLevel = analogRead(A8);
  
  //Lux sensor
  lux = lightMeter.readLightLevel();


  //DISPLAY
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("h ");
  lcd.print(hum);
  lcd.print("   ");
  lcd.print("t ");
  lcd.print(temp);
  lcd.print("   ");
  lcd.print("w ");
  lcd.print(waterLevel);
  lcd.print("   ");
  lcd.print("l ");
  lcd.print(lux);
  lcd.print("   ");
  lcd.setCursor(0,0);

  if (lux > 100) {
    digitalWrite(RELAYPIN, HIGH);
  }  
  else {
    digitalWrite(RELAYPIN, LOW);
  }

  
  //BEEP
  //analogWrite(10, 100);
}
