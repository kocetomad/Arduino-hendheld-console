#include <LCD5110_Graph.h>
LCD5110 lcd(11, 10, 9, 8, 12);
int x=20,y=20;
const int button = 2;
const int button1 = 3;
int state=1;
struct body{
  int x;
  int y;
};
struct body1{
  int x;
  int y;
};
  struct body body[20]; 
    struct body body1[20]; 


void setup() {
  for (int i=0;i<4;i++){
    body[i].x=20-i;body[i].y=20;
  }
  // put your setup code here, to run once:
  lcd.InitLCD();
  lcd.update();
 pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
 
  lcd.setPixel(body[0].x,body[0].y);
  lcd.setPixel(body[1].x,body[1].y);
  lcd.setPixel(body[2].x,body[2].y);
  lcd.setPixel(body[3].x,body[3].y);

}

void loop() {
  lcd.setPixel(body[0].x,body[0].y);
  lcd.setPixel(body[1].x,body[1].y);
  lcd.setPixel(body[2].x,body[2].y);
  lcd.setPixel(body[3].x,body[3].y);
  body1[0].x=body[0].x;
  body1[1].x=body[1].x;
  body1[2].x=body[2].x;
  body1[3].x=body[3].x;
   body1[0].y=body[0].y;
  body1[1].y=body[1].y;
  body1[2].y=body[2].y;
  body1[3].y=body[3].y;


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
    if(body[0].x==84){
      body[0].x=1;
    }
    if(body[0].y==48){
      body[0].y=1;
    }
    if(body[0].x==0){
      body[0].x=84;
    }
    if(body[0].y==0){
      body[0].y=48;
    }
  body[1].x=body1[0].x;
  body[1].x=body1[2].x;
  body[2].x=body1[3].x;
  body[3].x=body1[3].x;
  body[0].y=body1[1].y;
  body[1].y=body1[2].y;
  body[2].y=body1[3].y;
  delay(200);
  lcd.clrScr();
  
  // put your main code here, to run repeatedly:

}
