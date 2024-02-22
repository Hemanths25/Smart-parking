#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial nodemcu(0,1);
Servo myservo;

#define led_slot1 10
#define led_slot2 11
#define led_slot3 12
#define led_slot4 13

#define ir_enter 8
#define ir_back  9

#define ir_car1 4
#define ir_car2 5
#define ir_car3 6
#define ir_car4 7

int S1=0, S2=0, S3=0, S4=0;
int flag1=0, flag2=0; 
int slot = 4;

String sensor1; 
String sensor2; 
String sensor3; 
String sensor4; 

String cdata ="";

void setup(){
nodemcu.begin(9600);
Serial.begin(9600);

pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT); 

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);

pinMode(led_slot1, OUTPUT);
pinMode(led_slot2, OUTPUT);
pinMode(led_slot3, OUTPUT);
pinMode(led_slot4, OUTPUT);
  
myservo.attach(3);
myservo.write(180);
lcd.init();  
lcd.backlight();
lcd.setCursor (0,0);
lcd.print("     Smart   ");
lcd.setCursor (0,1);
lcd.print("     Parking  ");
delay (2000);
lcd.clear(); 
Read_Sensor();
int total = S1+S2+S3+S4;
slot = slot-total;
}


void loop()
{

slot1(); 
slot2();
slot3(); 
slot4();
Read_Sensor();

  cdata = cdata + sensor1 +"," + sensor2 + ","+ sensor3 +","+ sensor4 + ","; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(10); // 100 milli seconds
   cdata = ""; 
digitalWrite(ir_car1, HIGH); 
digitalWrite(ir_car2, HIGH); 
digitalWrite(ir_car3, HIGH);
digitalWrite(ir_car4, HIGH);

lcd.setCursor (0,0);
if(S1==1||led_slot1==HIGH){lcd.print("S1:Full");}
     else{lcd.print("S1:Free");}
     
lcd.setCursor (9,0);
if(S2==1||led_slot2==HIGH){lcd.print("S2:Full");}
     else{lcd.print("S2:Free");}

lcd.setCursor (0,1);
if(S3==1||led_slot3==HIGH){lcd.print("S3:Full");}
     else{lcd.print("S3:Free");}

lcd.setCursor (9,1);
if(S4==1||led_slot4==HIGH){lcd.print("S4:Full");}
     else{lcd.print("S4:Free");}

if(digitalRead (ir_enter) == 0 && flag1==0){
if(slot>0){flag1=1;
if(flag2==0){myservo.write(90); slot = slot-1;}
}else{
lcd.clear(); 
lcd.setCursor (0,0);
lcd.print("  Parking Full ");  
delay(2000);
lcd.clear();
}   
}

if(digitalRead (ir_back) == 0 && flag2==0){flag2=1;
if(flag1==0){myservo.write(90); slot = slot+1;}
}

if(flag1==1 && flag2==1){
delay (200);
myservo.write(180);
flag1=0, flag2=0;
}

delay(1);
}



void slot1() // parkng slot1
{
  if( digitalRead(ir_car1) == LOW) 
  {
  sensor1 = "255";
  digitalWrite(led_slot1, HIGH);
 delay(200); 
  } 
if( digitalRead(ir_car1) == HIGH)
{
  sensor1 = "0"; 
  digitalWrite(led_slot1, LOW);
 delay(200);  
}

}

void slot2() // parking slot2
{
  if( digitalRead(ir_car2) == LOW) 
  {
  sensor2 = "255"; 
  digitalWrite(led_slot2, HIGH);
  delay(200); 
  }
if( digitalRead(ir_car2) == HIGH)  
  {
  sensor2 = "0"; 
  digitalWrite(led_slot2, LOW); 
 delay(200);
  } 
}


void slot3() // parking slot3
{
  if( digitalRead(ir_car3) == LOW) 
  {
  sensor3 = "255"; 
  digitalWrite(led_slot3, HIGH);
  delay(200); 
  }
if( digitalRead(ir_car3) == HIGH)  
  {
  sensor3 = "0";  
  digitalWrite(led_slot3, LOW);
 delay(200);
  } 
}

void slot4() // parking slot4
{
  if( digitalRead(ir_car4) == LOW) 
  {
  sensor4 = "255"; 
  digitalWrite(led_slot4, HIGH);
  delay(200); 
  }
if( digitalRead(ir_car4) == HIGH)  
  {
  sensor4 = "0"; 
  digitalWrite(led_slot4, LOW); 
 delay(200);
  } 
}
void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0;

if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;}
if(digitalRead(ir_car3) == 0){S3=1;}
if(digitalRead(ir_car4) == 0){S4=1;}
}