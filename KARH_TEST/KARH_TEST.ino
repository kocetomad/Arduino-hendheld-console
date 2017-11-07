#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <LCD5110_Graph.h>
LCD5110 lcd(11,10,9,8,12);
extern uint8_t elsys [];

const int button=2;
const int button1=3;
extern unsigned char TinyFont[];
extern unsigned char SmallFont[];
  int a=1 ;
  int x=27;
  int spawn=0;
  int Y1;
  int X1;
  int Y2;
  int X2;
  int Y3;
  int m=0;
  bool ingame1=false;
  int score=0;
//  int X3;
  bool over=false;
void setup() {
    Serial.begin(9600);

  pinMode(button,INPUT);
  digitalWrite(button,HIGH);
  pinMode(button1,INPUT);
  digitalWrite(button1,HIGH);
  lcd.InitLCD();
   Y1=0;
   Y2=0;


}

void loop() {
 if(ingame1){
  GAME1();
 }else{
 MENU();
 }
}


 void MENU(){
   if(digitalRead(button)==HIGH){
    switch(m){
        case 0:ingame1=true;
    }
   }
    if(digitalRead(button1)==HIGH){
    if(m==2){
      m=0;
    }else{
      m++;
    
    }

    delay (200);
  }
  
    lcd.clrScr();
    lcd.setFont(SmallFont);
    lcd.print("MENU", CENTER , 1);
    lcd.drawLine(20, 9, 65, 9); 
    if(m==0){
    lcd.invertText(true);    
   }
    lcd.print("GAME 1", CENTER , 15);
    lcd.invertText(false);    

   if(m==1){
    lcd.invertText(true);    
   }
    lcd.print("BACKLIGHT", CENTER , 25);
    lcd.invertText(false);    
  if(m==2){
    lcd.invertText(true);    
   }
    lcd.print("CONTRAST", CENTER , 35);
   lcd.invertText(false);    

    lcd.update();
    //delay (5);

 }
 void GAME1(){
  if(digitalRead(button1)==HIGH){
    if (x<=52){
    x++; 
    a=2;
    }

    delay (20);
  }
  if(digitalRead(button)==HIGH){
     if (x>=2){
    x--; 
    a=2;
    Serial.println(x);
     }
    delay (20);
  }
    lcd.setFont(SmallFont);

 if(over==false){
  //UI//
  lcd.clrScr();
  lcd.setFont(TinyFont);
  lcd.drawRect(x, 40, x+2, 42);

 // lcd.drawBitmap(x,0,elsys,84,84);
  lcd.print("score:", 59, 1);
  lcd.drawRect(0, 0, 83, 47);
  lcd.setFont(SmallFont);
  lcd.printNumI(Y1, 58 ,7);
  lcd.drawLine(56, 84, 56, 0); 
  //UI//
  //ROWS/1/
      Serial.println(spawn);

  if(Y1==48){
    Y1=0;
    X1=random(0,53);
    score++;

  }
  lcd.drawLine(0, Y1, X1, Y1); 
  lcd.drawLine(X1+3, Y1,57 , Y1); 
 
  
 /* //ROWS/2/
  if(Y2==48){
    Y2=0;
    X2=random(0,53);
    score++;
  }
  lcd.drawLine(0, Y2, X2, Y2); 
  lcd.drawLine(X2+3, Y2,57 , Y2); 

  //ROWS/3/
  if(Y3==84){
    Y3=20;
    X3=random(0,53);
  }
  lcd.drawLine(0, Y3, X3, Y3); 
  lcd.drawLine(X3+3, Y3,57 , Y3); 
  */
  //TOVA DVIJI BAROVETE
 /* if(spawn==100 && spawn%3==0){
      Y2++;

  }*/
  if(spawn%3==0){
    Y1++;
  }//
  }
  //lose cond
  if(Y1>=40 && Y1 <=42 ){
      if(x<X1 || x>=X1+2){//|| x<=X2 || x>=X2+3 || x<=X3 || x>=X3+3 && Y1>=40 && Y1 <=42 || Y2>=40 && Y2 <=42 || Y3>=40 && Y3 <=42){
  
       lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over=true;}
  }
  lcd.update();
  delay(20);
  spawn++;
  }
