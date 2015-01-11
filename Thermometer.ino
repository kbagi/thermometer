#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 7     // What pin we're connected to
#define DHTTYPE DHT11   // DHT 11 model 

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  Serial.begin(9600); 
 
  dht.begin();
  lcd.begin(16, 2);
   
  pinMode(9, OUTPUT);
  lcd.print("DHTxx test!");
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true); // Read in Fahrenhit
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  lcd.clear();
  
  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  lcd.print("Hum:  "); 
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Temp: "); 
  lcd.print(t);
  lcd.print(" C ");
}
