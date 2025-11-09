#include<LiquidCrystal.h>
int rs=13,en=12,d4=14,d5=27,d6=26,d7=25;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);




int buzzer=5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
//  Serial1.begin(9600);
  lcd.begin(16,2);
  pinMode(buzzer,OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("VEHICLE MODEL");
  
  Serial.println("LANDSLIDE VEHICLE MODEL");
  delay(1000);

  digitalWrite(buzzer,LOW);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vehicle Model");
  delay(1000);
  
  if(Serial2.available()>0)
  {
    char ch=Serial2.read();
    Serial.println(ch);
    delay(500);
    if(ch=='L')
    {
      Serial.println("Landslide Detected");
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  LANDSLIDE  ");
      lcd.setCursor(0,1);
      lcd.print("  DETECTED  ");
      digitalWrite(buzzer,HIGH);
      delay(3000);
      digitalWrite(buzzer,LOW);
      delay(500);
    }
    if(ch=='R')
    {
      Serial.println("MORE RAINFALL");
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MORE RAINFALL");
      digitalWrite(buzzer,HIGH);
      delay(3000);
      digitalWrite(buzzer,LOW);
      delay(500);
    }
  }

}