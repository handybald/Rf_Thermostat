#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (9,10);
byte addresses[][6] = {"0"};  
int num;



void setup() {
  Serial.begin(115200);
  Serial.println("Hi");
  delay(2000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  
  pinMode(2, OUTPUT);
  
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
 
}

void loop() {
  
  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &num, sizeof(num) );
    }
    Serial.print("Package Received: ");
    Serial.println(num);

    if(num == 0555)
    {
      digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  Serial.println("Relay Opened");
      
      Serial.println("on");
    }
    if(num == 0666)
    {
      digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  Serial.println("Relay Closed");
      Serial.println("off");
    }
  }
  
delay(100);
}
