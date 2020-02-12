#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <SPI.h>  
#include "RF24.h"

//RADIO SETUP
RF24 myRadio (9,10);
byte addresses[][6] = {"0"};
int on = 0666;
int off = 0555;
int potVal;
//LCD SETUP
LiquidCrystal_I2C lcd(0x27, 16, 2);

//DHT SETUP
//d6
DHT dht(8, DHT22);
float temp;
void print2Screen(float temp, int pot)
{
  lcd.clear();
  lcd.home();
  lcd.print("  Oda : ");
  lcd.print(temp,1);
  lcd.setCursor(0,1);
  lcd.print(" Istenen : ");
  lcd.print(pot);
}

void print2Screen(String a)
{
  lcd.clear();
  lcd.home();
  lcd.print(a);
}


void setup() {
  pinMode(A0, INPUT);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print("Merhaba");
  delay(2000);
  
  Serial.begin(115200);
  delay(10);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Baslatiiyor");
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openWritingPipe(addresses[0]);    
  delay(500);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Radio Baglandi");
  delay(1000);
  myRadio.stopListening();
}

void loop() {
  
  temp = dht.readTemperature();
  Serial.println(temp);

  
  potVal = analogRead(A0);
  int potVall = map(potVal,0,1023,18,32);

  Serial.println(potVall);
  print2Screen((int)temp, potVall);

  if(potVall > (int)temp)
  {
    myRadio.write(&on, sizeof(on));
    Serial.print("Package Transferred: "); 
    Serial.println("ON");
    delay(500);
  }
  if(potVall <= (int)temp)
  {
    myRadio.write(&off, sizeof(off));
    Serial.print("Package Transferred: ");
    Serial.println("OFF");
    delay(500);
  }
}
