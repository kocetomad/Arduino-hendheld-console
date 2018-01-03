#include <LCD5110_Graph.h>
LCD5110 lcd(11, 10, 9, 8, 12);
bool snake=false;
int x=20,y=20;
extern unsigned char SmallFont[];
extern unsigned char TinyFont[];
bool over1=false;
int score=0;
const int button = 2;
const int button1 = 3;
int state=1;
struct axis{
  int x;
  int y;
};
int stepp=0;

  struct axis body[40]; 
  struct axis body1[40]; 
  struct axis pick;

int n=5;
void setup() {
  for (int i=0;i<n;i++){
    body[i].x=20-i;body[i].y=20;
  }
  // put your setup code here, to run once:
  lcd.InitLCD();
  lcd.update();
 pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
     pick.x=random(8,46);
    pick.y=random(5,46);
 

}

void loop() {
  if(over1){
    if (digitalRead(button) == LOW) {score=0;snake==false;loop();};
  lcd.update();
  }
  if(over1==false){
   lcd.setFont(TinyFont);
   lcd.print("score:", 59, 1);
   lcd.drawRect(0, 0, 83, 47);
   lcd.setFont(SmallFont);
   lcd.printNumI(score, 58 , 7);
   lcd.drawLine(56, 84, 56, 0);
   lcd.setPixel(pick.x,pick.y);
  }
  for(int i=1;i<n;i++){
    if(body[0].x==body[i].x && body[0].y==body[i].y){
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over1=true;
            lcd.update();

        
    }
  }
    if(over1==false){

  if (pick.x==body1[0].x && pick.y==body1[0].y){
    n++;
    score++;
     pick.x=random(8,46);
    pick.y=random(5,46);
    if (n==50){
      lcd.clrScr();
        lcd.print("YOU WIN ", CENTER , 1);
        over1=true;
            lcd.update();

    }
  }
  for(int i=0;i<n;i++){
  lcd.setPixel(body[i].x,body[i].y);
  }
  for(int i=0;i<n;i++){
  body1[i].x=body[i].x;
  body1[i].y=body[i].y;
  }

  if (digitalRead(button)==LOW){
    if(state==4){
      state=1;
    }else{
    state++;
    }
  }
  
  if (digitalRead(button1)==LOW){
    if(state==1){
      state=4;
    }else{
    state--;
    }
  }
  
  lcd.setPixel(body[0].x,body[0].y);
  lcd.update();
    switch(state){
      case 1:body[0].x++;
      break;
      case 2:body[0].y++;
      break;
      case 3:body[0].x--;
      break;
      case 4:body[0].y--;
      break;
    }
    if(body[0].x==56){
      body[0].x=1;
    }
    if(body[0].y==48){
      body[0].y=1;
    }
    if(body[0].x==0){
      body[0].x=56;
    }
    if(body[0].y==0){
      body[0].y=48;
    }

  for(int i=0;i<n-1;i++){
  body[i+1].x=body1[i].x;

  body[i+1].y=body1[i].y;
  }
  delay(100);
    lcd.update();
    lcd.clrScr();
    }
  // put your main code here, to run repeatedly:

}

