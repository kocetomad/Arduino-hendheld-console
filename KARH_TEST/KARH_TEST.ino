#include <LCD5110_Graph.h>
LCD5110 lcd(8,9,10,12,11);
extern uint8_t elsys [];

const int button=2;
const int button1=3;
extern unsigned char TinyFont[];
extern unsigned char SmallFont[];
  int a=1 ;
  int x=0;
  int spawn=0;
  int Y1=0;
  int X1;
  int Y2=-10;
  int X2;
  int Y3=-20;
  int X3;
void setup() {
    Serial.begin(9600);

  pinMode(button,INPUT);
  digitalWrite(button,HIGH);
  pinMode(button1,INPUT);
  digitalWrite(button1,HIGH);
  lcd.InitLCD();
      // X1=random(0,53);???? problem???/

}

void loop() {
  if(digitalRead(button1)==HIGH){
    if (x<=14){
    x++; 
    a=2;
    }
    Serial.println(x);

    delay (10);
  }
  if(digitalRead(button)==HIGH){
     if (x>=-13){
    x--; 
    a=2;
    Serial.println(x);
     }
    delay (10);
  }
  //UI//
  lcd.clrScr();
  lcd.setFont(TinyFont);
  lcd.drawBitmap(x,0,elsys,84,84);
  lcd.print("score:", 59, 1);
  lcd.drawRect(0, 0, 83, 47);
  lcd.setFont(SmallFont);
  lcd.printNumI(x, 58 ,7);
  lcd.drawLine(56, 84, 56, 0); 
  //UI//
  //ROWS/1/
  if(Y1==84){
    Y1=0;
    X1=random(0,53);
  }
  lcd.drawLine(0, Y1, X1, Y1); 
  lcd.drawLine(X1+3, Y1,57 , Y1); 
 
  
  //ROWS/2/
  if(Y2==84){
    Y2=10;
    X2=random(0,53);
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
  if(spawn==3){
  Y3++;
  Y2++;
  Y1++;
  spawn=0;
  }
  
  lcd.update();
  delay(10);
  spawn++;
}
