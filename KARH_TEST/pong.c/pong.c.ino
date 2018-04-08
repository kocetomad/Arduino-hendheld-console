#include <DS1302.h>
#include <stdio.h>

#include <LCD5110_Graph.h>
LCD5110 lcd(11, 10, 9, 8, 12);
DS1302 rtc(A5, A4, A3);
extern uint8_t elsys [];
extern uint8_t firstframe [];
extern uint8_t secondframe [];
extern uint8_t thirdframe [];
extern uint8_t car [];
extern uint8_t bad [];
bool over2 = false;
int timing=0;
bool over1=false;

extern uint8_t enm [];
extern uint8_t plr [];
const int button = 2;
const int button1 = 3;
const int action = 4;
bool check = true;
extern unsigned char TinyFont[];
extern unsigned char SmallFont[];
int a = 1 ;
int x = 27;
int spawn = 0;
int Y1;
int X1;
int score1 = 0;
int x2 = 24;
int y2 = 12;
int x3 = 28;
int y3 = 25;
int x4 = 44;
int y4 = 32;
int x5 = 30;
bool klik = true;
int state=1;
struct axis{
  int x;
  int y;
};
int stepp=0;

  struct axis body[40]; 
  struct axis body1[40]; 
  struct axis pick;
/*int Y2;
  int Y3;*/
  bool snake=false;
int n=5;

float X2 = 0;
int m = 0;
bool ingame1 = false;
bool ingame2 = false;
int fire = 0;
int fires[3] = {0, 0, 0};
int score = 0;
int dvijenie_na_shota_v_game_2 [3] = {0, 0, 0};
int shotpos1[3] = {0, 0, 0};
bool pressed = false;
bool inTIME = false;
//  int X3;
bool over = false;
struct axis PongPlayer1;
struct axis PongPlayer2;
struct axis Ball;
int ballstate;
int xSpeed;
int ySpeed;
int AI=0;
int AI_modetimer=0;
int PLAYER1score;
int PLAYER2score;

void setup() {
  ballstate=0;
  PongPlayer1.y=22;
  PongPlayer2.y=22;
  Ball.x=40;
  Ball.y=20;
  xSpeed=1;
  ySpeed=1;

  // put your setup code here, to run once:
   pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
  lcd.InitLCD();

}

void loop() {

Pong();
}




void Pong(){

  if (digitalRead(button)==LOW){
    if(PongPlayer1.y>=1){
          PongPlayer1.y--;
    }
    
  }
  
  if (digitalRead(button1)==LOW){
     if(PongPlayer1.y+7<=47){

    PongPlayer1.y++;
     }

  }

    Serial.println(Ball.x);

//BALL
  if(AI_modetimer==0){
  AI=random(0,6);//XDXD
  }
  //Ai mode 1 
  if(AI>=0 && AI<=3){
  if (Ball.y>0 && Ball.y<=41){
  PongPlayer2.y=Ball.y;
  }
  AI_modetimer++;
  if(AI_modetimer>=500){
    AI_modetimer=0;
  }
  }
  //Ai mode 2
  if(AI>=4){
  int dir=random(1,100);
  if(dir<50){
    if(PongPlayer2.y>1){
      PongPlayer2.y--;
    }
  }
  if(dir>50){
    if(PongPlayer2.y<41){
      PongPlayer2.y++;
    }
  }
  AI_modetimer++;
  if(AI_modetimer>=150){
    AI_modetimer=0;
  }
  }


  
  Ball.x+=xSpeed;
  Ball.y+=ySpeed;
 if (Ball.x<=4 && Ball.y>=PongPlayer1.y-2 && Ball.y<=PongPlayer1.y+6){
    xSpeed*=-1;
  }
 if (Ball.x>=77 && Ball.y>=PongPlayer2.y-2 && Ball.y<=PongPlayer2.y+6){
    xSpeed*=-1;
  }
/* if (Ball.x>=77){
    xSpeed*=-1;
    ballstate=0;//collision
  }*/

  if(Ball.y>=45){
     ySpeed*=-1;
  }

  if(Ball.y<=1){
     ySpeed*=-1;
  }


  if(Ball.x<0){
  Ball.x=40;
  Ball.y=20;
  PLAYER2score++;
  }


  if(Ball.x+2>84){
  Ball.x=40;
  Ball.y=20;
  PLAYER1score++;
  AI=2;
  }

  
  
  lcd.drawRect(Ball.x,Ball.y,Ball.x+2,Ball.y+2); 
  delay(50);
  
 // put your main code here, to run repeatedly:
  lcd.drawLine(4,PongPlayer1.y,4, PongPlayer1.y+7);
  lcd.drawRect(79,PongPlayer2.y,79, PongPlayer2.y+6); 
  lcd.drawRect(0,0,83, 47); 

  for(int i=0;i<12;i++){
    lcd.drawLine(42,i*4,42,(i*4)+3);
 }

  lcd.setFont(TinyFont);
  
  lcd.printNumI(PLAYER1score,22,3);
  lcd.printNumI(PLAYER2score,62,3);


 
  lcd.update();
  lcd.clrScr();

}

