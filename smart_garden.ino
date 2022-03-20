#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int rs=9, en =10, d4 = 5, d5 = 4,d6 = 3,d7 = 2;
LiquidCrystal lcd(rs, en , d4 ,d5,d6,d7);
int ldr = A0;
int lm35 = A1;
int SM = A2;
int value=0;
int moisture;
int led =12;
const int RELAY_PIN = 11;


void setup() {
Serial.begin(9600);
pinMode(led, OUTPUT);

pinMode(RELAY_PIN, OUTPUT);
pinMode(ldr, INPUT);
pinMode(lm35, INPUT);

lcd.begin(16,2);
lcd.setCursor(0,0);

while (!Serial); 
 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {


   
    //RTC
    DateTime now = rtc.now();
    lcd.print(now.day());
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(6,1);
    lcd.print(now.hour());
    lcd.print(':');
    lcd.print(now.minute());
    lcd.print(':');
    lcd.print(now.second());
    delay(1000);
    lcd.clear();
     if(now.hour()>=20 || now.hour()>=0 && now.hour()<=5)
    {
      digitalWrite(led, HIGH);
      
    }
      if( now.hour()>=0 && now.hour()<=5)
    {
      digitalWrite(led, HIGH);
      
    }
//LDR SENSOR
lcd.print("LDR value :");
lcd.print(analogRead(ldr));
delay(2000);
lcd.clear();
  
// TEMP SENSOR
int tmp;
float tmp_val;
tmp=analogRead(lm35);
tmp_val=tmp*4.88;
tmp_val/=10;
 lcd.print("tmp:");
  lcd.print(tmp_val);
   lcd.print("C");
delay(2000);
  lcd.clear();
  
 //SOIL SENSOR
  value=analogRead(SM);
  moisture=map(value,1017,100,0,100);
  lcd.print("moisture :");
  lcd.print(moisture);
  lcd.print("%");
  delay(2000);
  lcd.clear();
    

//CONDITIONS

// TOO DRY 
  if(moisture<20)
  {
    digitalWrite(RELAY_PIN, LOW);
    lcd.print("Pump ON");
    delay(1000);
    lcd.clear();
    
    }

    if(moisture>25)
  {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.print("Pump OFF");
    delay(1000);
    lcd.clear();
    
    }

  if(tmp_val>30)
  {
    //MORNING
    if( now.hour()== 6)
    {
      digitalWrite(RELAY_PIN, LOW);
      lcd.print("PUMP ON");
      delay(1000);
      lcd.clear();
      
      
    }
    //EVENING
    if(now.hour()== 18)
    {
      digitalWrite(RELAY_PIN, LOW);
      lcd.print("PUMP ON");
      delay(1000);
      lcd.clear();
      
    }
    
    //Dhuhr
    if(now.hour()== 12)
    {
      digitalWrite(RELAY_PIN, LOW);
      lcd.print("PUMP ON");
      delay(1000);
      lcd.clear();
      
    }
  }

  else
  {
    //MORNING
    if(now.hour()== 6)
    {
      digitalWrite(RELAY_PIN, LOW);
      lcd.print("PUMP ON");
      delay(1000);
      lcd.clear();
      
    }
    //EVENING
    if(now.hour()== 18)
    {
      digitalWrite(RELAY_PIN, LOW);
      lcd.print("PUMP ON");
      delay(1000);
      lcd.clear();
      
    }
  }
  
}
