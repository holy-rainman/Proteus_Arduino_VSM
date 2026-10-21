#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define led1	10
#define led2	11
#define led3	13
#define segM	A2
#define segR	A3

void setup()
{
   pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
   pinMode(led3,OUTPUT);
   pinMode(segM,OUTPUT);
   pinMode(segR,OUTPUT);
   pinMode(9,INPUT);	//AH
   pinMode(8,INPUT);	//AL
   
   lcd.begin(16, 2);
   lcd.setCursor(0,0); lcd.print(" Selamat Datang ");
   lcd.setCursor(0,1); lcd.print(" ke ADTEC Kulim ");   
}

uint8_t cnt=0, segment=0;
void loop()
{ checkPB();
  runMenu();
}

void checkPB()
{  if(digitalRead(9)==1)
   {  cnt++;
      while(digitalRead(9)==1);
      delay(200);
      if(cnt==3) cnt=0;
   }
   
   if(cnt==0)
   {  digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
   }
   if(cnt==1)
   {  digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
   }
   if(cnt==2)
   {  digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
   } 
}

void runMenu()
{
  if(digitalRead(8)==0) 
  {   if(cnt==0)	//increment 7 segment
      {	 digitalWrite(segM,HIGH); delay(200);
	 digitalWrite(segM,LOW);
	 segment++;
      }
      if(cnt==1)	//trigger blink with n times
      {	 for(uint8_t i=0;i<segment;i++)
	 {  digitalWrite(led3,HIGH);	delay(500);
	    digitalWrite(led3,LOW);	delay(500);
	 }
	 segment=0;
	 digitalWrite(segR,HIGH);	delay(200);
	 digitalWrite(segR,LOW);
      }
      if(cnt==2)	//change LCD display to workshop name
      {	 lcd.setCursor(0,0); lcd.print("    -Kursus-    ");
	 lcd.setCursor(0,1); lcd.print(" -EDA Proteus-  ");
	 delay(2000);
	 lcd.setCursor(0,0); lcd.print(" Selamat Datang ");
	 lcd.setCursor(0,1); lcd.print(" ke ADTEC Kulim ");   
      }
      while(digitalRead(8)==0);
      delay(200);
  }
}
