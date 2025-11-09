void SEND_SMS(String num, String str );
//char ch;

char textmessage[200];

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


int m1=12;
int m2=14;

int m3=27;
int m4=26;

int ir1=18;
int ir2=19;

int a=0;
int k=1;

int red1=15;
int red2=4;

int green1=2;
int green2=5;
int buzzer=23;

#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();


void setup() {
  // put your setup code here, to run once:
  
   
  Serial.begin(9600);
  Serial2.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.println("LANDSLIDE MONITORING");
  SEND_SMS("+918088764423","Landslide Monitoring");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  LANDSLIDE  ");
  lcd.setCursor(0,1);
  lcd.print(" MONITORING  ");
  delay(500);
  
   if(!accel.begin())
{

      Serial.println("No valid sensor found");
      delay(100);

      while(1);

   }  
   digitalWrite(m1,LOW);
   digitalWrite(m2,LOW);
   digitalWrite(m3,LOW);
   digitalWrite(m4,LOW);
   GREEN();


}

void loop() {
  // put your main code here, to run repeatedly:
  ADXL();
  RAIN_CHECK();
   IR_CHECK();
  serial_read();


}

void ADXL()
{
  sensors_event_t event; 

   accel.getEvent(&event);

  float X_val=event.acceleration.x;

  float Y_val=event.acceleration.y;

  float Z_val=event.acceleration.z;
   

   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//
   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
//((X_val>0.5 && X_val<2.0))
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("X:"+String(X_val));
   lcd.setCursor(0,1);
   lcd.print("Y:"+String(Y_val));
   
    delay(500);
    
      
   if(k==1 && (X_val>-1.5&&X_val<2))
  {
    a=1;
    digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
    
  }
  
    

  else if(a==1 && ((X_val<-7.50)||(X_val>7.5)||(Y_val<-7.50)||(Y_val>7.5)))
   {
    k=0;
    a=0;
    
    Serial2.println('L');
    Serial.println("$LANDSLIDE DETECTED#");
    SEND_SMS("+918088764423","Landslide Detected");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  LANDSLIDE  ");
    lcd.setCursor(0,1);
    lcd.print("  DETECTED  ");
    digitalWrite(buzzer,HIGH);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATES CLOSING");
    Serial.println("$GATES CLOSING#");
      SEND_SMS("+918088764423","Gates Closing");
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(m1,HIGH);
      digitalWrite(m2,LOW);
      digitalWrite(m3,HIGH);
      digitalWrite(m4,LOW);
      delay(500);
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
     
      delay(1000);
       RED();
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("GATES OPENING");
//      digitalWrite(m1,LOW);
//      digitalWrite(m2,HIGH);
//      digitalWrite(m3,LOW);
//      digitalWrite(m4,HIGH);
//      delay(500);
//      digitalWrite(m1,LOW);
//      digitalWrite(m2,LOW);
//      digitalWrite(m3,LOW);
//      digitalWrite(m4,LOW);
//      delay(1000);
   }
   else if(k==0&&(X_val>-1.5&&X_val<2))
   {
    k=1;
    a=1;
   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GATES OPENING");
      Serial.println("$GATES OPENING#");
      SEND_SMS("+918088764423","Gates Opening");
      delay(1000);
      digitalWrite(m1,LOW);
      digitalWrite(m2,HIGH);
      digitalWrite(m3,LOW);
      digitalWrite(m4,HIGH);
      delay(500);
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
      delay(1000);
       GREEN();
   }
   
   
  
}

void RAIN_CHECK()
{
  int rainval=analogRead(36);
  rainval=4095-rainval;
  Serial.print("Rain:");
  Serial.println(rainval);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rain:");
  lcd.setCursor(6,0);
  lcd.print(rainval);
  delay(1000);
  if(rainval>2500)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RAINFALL IS MORE");
    Serial.println("RAINFALL IS MORE");
    SEND_SMS("+918088764423","Rainfall is More");
    Serial2.println('R');
    delay(1000);
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATES CLOSING");
      digitalWrite(buzzer,LOW);
      digitalWrite(m1,HIGH);
      digitalWrite(m2,LOW);
      digitalWrite(m3,HIGH);
      digitalWrite(m4,LOW);
      delay(500);
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
      RED();
      delay(5000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GATES OPENING");
      digitalWrite(m1,LOW);
      digitalWrite(m2,HIGH);
      digitalWrite(m3,LOW);
      digitalWrite(m4,HIGH);
      delay(500);
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
      delay(1000);
      GREEN();

  }
  else
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m1,LOW);
    digitalWrite(m4,LOW);
    delay(1000);
  }
 }

 void IR_CHECK()
  {
    int irval=digitalRead(ir1);
    int ir2val=digitalRead(ir2);
    if((irval==LOW))
    {
      Serial.println("ROAD1 CLEAR");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ROAD1 CLEAR");
      
      ROAD1();
      delay(1000);
      GREEN();
      delay(1000);
    }
   else if((ir2val==LOW))
    {
      Serial.println("ROAD2 CLEAR");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ROAD2 CLEAR");
      ROAD2();
      delay(1000);
      GREEN();
      delay(1000);
    }
    serial_read();
  }

void ROAD1()
  {
    digitalWrite(red1,LOW);
    digitalWrite(red2,HIGH);
    digitalWrite(green1,HIGH);
    digitalWrite(green2,LOW);
    delay(2500);
  }
  void ROAD2()
  {
    digitalWrite(red1,HIGH);
    digitalWrite(red2,LOW);
    digitalWrite(green1,LOW);
    digitalWrite(green2,HIGH);
    delay(2500);
  }
  void RED()
  {
    digitalWrite(red1,HIGH);
    digitalWrite(red2,HIGH);
    digitalWrite(green1,LOW);
    digitalWrite(green2,LOW);
    
  }

  void GREEN()
  {
    digitalWrite(red1,LOW);
    digitalWrite(red2,LOW);
    digitalWrite(green1,HIGH);
    digitalWrite(green2,HIGH);
  }

void serial_read()
  {
    if(Serial.available()>0)
    {
      char ch=Serial.read();
      Serial.println(ch);
      delay(500);
      if(ch=='A')
      {
        Serial.println("GIVEN PRIORITY FOR TRUCK");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PRIORITY FOR");
        lcd.setCursor(0,1);
        lcd.print("TRUCK GIVEN");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" TRUCK CAN ");
        lcd.setCursor(0,1);
        lcd.print(" MOVE AHEAD ");
        delay(1000);
        
      }
      if(ch=='B')
      {
        
        Serial.println("GIVEN PRIORITY FOR BUS");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PRIORITY FOR");
        lcd.setCursor(0,1);
        lcd.print("BUS GIVEN");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" BUS CAN ");
        lcd.setCursor(0,1);
        lcd.print(" MOVE AHEAD ");
        delay(1000);
      }
    }
}


void SEND_SMS(String num, String str )
{
    Serial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000); // Delay of 1000 milli seconds or 1 second
    
    Serial.print("AT+CMGS=\""); // Send the SMS number
    Serial.print(num);
    Serial.println("\"");
    delay(1000);
    
    Serial.println(str);// The SMS text you want to send
    delay(100);
    
    Serial.println((char)26);// ASCII code of CTRL+Z
    delay(1000);

    Serial.println("SMS Sent..");
 
}