//DHT11 hőmérséklet és páratartalom szenzor értékeinek PCD8544 Nokia 3310 LCD-re

#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

#define DHTPIN 12 //DHT szenzor PIN
#define DHTTYPE DHT11 //nekem most csak ez van

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.println("Zoli DHT test");
  lcd.print("Zoli DHT test");
}

void loop() {
  //a tényleges program, ismételjük a lépéseket
  delay(2000); //kicsit várunk az elöző mérés után
  lcd.setCursor(0,0);
  float paratartalom = dht.readHumidity(); //páratartalom
  float homerseklet = dht.readTemperature(); //hőmérséklet Celsiusban

// későbbi hibaüzenethez kell majd, ha nincs érték akkor valamit azért böfögjünk
  if (isnan(paratartalom) || isnan(homerseklet)) {
    Serial.println("DHT nem talalhato"); 
    return;  
    }
  lcd.print("Para:    ");
  lcd.print(paratartalom);
  lcd.print(" %");  
  Serial.print("Paratartalom: ");
  Serial.print(paratartalom);
  Serial.print(" %\t");
  lcd.setCursor(0,1);
  lcd.print("Celsius: ");
  lcd.print(homerseklet);
  lcd.print(" C");
  Serial.print("Homerseklet: ");
  Serial.print(homerseklet);
  Serial.println(" *C");

}
