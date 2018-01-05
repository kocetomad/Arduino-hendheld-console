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
void setup() {
  Serial.begin(9600);
  for (int i=0;i<n;i++){
    body[i].x=20-i;body[i].y=20;
  }
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
  lcd.InitLCD();
  Y1 = 0;
       pick.x=random(8,46);
    pick.y=random(5,46);
  //   Y2=0;
  

  //CLOCK PART
  rtc.halt(false);
  rtc.writeProtect(true);

  // Make a new time object to set the date and time.
  // Sunday, September 22, 2013 at 01:38:50.
  Time t(2018, 01, 02, 18, 10, 00, Time::kTuesday);
  rtc.writeProtect(true);

  // Set the time and date on the chip.
  rtc.time(t);
}

void loop() {
  if (inTIME) {
    TIME();
  }
  if (ingame2) {
    CARS();
  }
  if (ingame1) {
    GAME1();
  }
  if(snake){
    SNAKE();
  }
  if (ingame1 == false && ingame2 == false && inTIME == false && snake==false) {
    MENU();
  }
  lcd.update();

}

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}
void MENU() {
  if (digitalRead(button) == LOW) {
    switch (m) {
      case 0: ingame1 = true;
        break;
      case 1: snake = true;
        break;
      case 2: ingame2 = true;
        break;
      case 3: inTIME = true;
        break;
    }
  }
  if (digitalRead(button1) == LOW) {
    if (m == 3) {
      m = 0;
    } else {
      m++;

    }

    delay (300);
  }

  lcd.clrScr();
  lcd.setFont(SmallFont);
  lcd.print("MENU", CENTER , 1);
  lcd.drawLine(20, 9, 65, 9);
  if (m == 0) {
    lcd.invertText(true);
  }
  lcd.print("DODGE", 6 , 15);
  lcd.invertText(false);
  if (m == 1) {
    lcd.invertText(true);
  }
  lcd.print("SNAKE", 48 , 15);
  lcd.invertText(false);
  if (m == 2) {
    lcd.invertText(true);
  }
  lcd.print("CARS", CENTER , 25);
  lcd.invertText(false);
  if (m == 3) {
    lcd.invertText(true);
  }
  lcd.print("CLOCK", CENTER , 35);
  lcd.invertText(false);

  lcd.update();
  //delay (5);

}
void SNAKE(){
          lcd.clrScr();

   if(over1){
    if (digitalRead(button1) == LOW) {score=0;snake==false;loop();};
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
  if(over1==false){
   lcd.setFont(TinyFont);
   lcd.print("score:", 59, 1);
   lcd.drawRect(0, 0, 83, 47);
   lcd.setFont(SmallFont);
   lcd.printNumI(score, 58 , 7);
   lcd.drawLine(56, 84, 56, 0);
   lcd.setPixel(pick.x,pick.y);
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
  
   
    }
}
void CARS() {
  if (over2) {
    lcd.clrScr();

    lcd.print("GAME OVER ", CENTER , 1);

    if (digitalRead(button1) == LOW) {
      score = 0;
      ingame2 == false;
      loop();
    };
    lcd.update();
  } else {
    // if (over2 == false) {

    lcd.setFont(SmallFont);

    if (y4 > 48) {
      y4 = 12;
      if (random(1, 3) == 1) {
        x5 = 30;
      } else {
        x5 = 50;
      }
    }


    if (y2 > 48) {
      y2 = 12;
      if (random(1, 3) == 1) {
        x3 = 28;
      } else {
        x3 = 44;
      }
    }
    if (y3 > 48) {
      y3 = 12;
      if (random(1, 3) == 1) {
        x4 = 28;
      } else {
        x4 = 44;
      }
    }
    if (digitalRead(button) == LOW) {
      x2 = 24;
    }
    if (digitalRead(button1) == LOW) {
      x2 = 48;
    }
    lcd.drawBitmap(0, 0, thirdframe, 84, 48);
    lcd.drawBitmap(x2, 37, car, 12, 8);
    lcd.drawBitmap(x3, y2, bad, 12, 8);
    lcd.drawBitmap(x4, y3, bad, 12, 8);
    lcd.drawRect(x5, y4, x5 + 4, y4 + 4);

    y2++;
    y3++;
    y4++;
    lcd.printNumI(score1, 1, 13);

    if (y2 >= 34 && y2 <= 44) {
      if (x2 == 24 && x3 == 28) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
      if (x2 == 48 && x3 == 44) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
    }
    if (y3 >= 34 && y3 <= 44) {
      if (x2 == 24 && x4 == 28) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
      if (x2 == 48 && x4 == 44) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
    }

    if (y4 >= 34 && y4 <= 44) {
      if (x2 == 24 && x5 == 30) {
        y4 = 12;
        score1++;

        if (random(1, 3) == 1) {
          x5 = 30;
        } else {
          x5 = 50;
        }
      }
      if (x2 == 48 && x5 == 50) {
        y4 = 12;
        score1++;
        if (random(1, 3) == 1) {
          x5 = 30;
        } else {
          x5 = 50;
        }
      }
    }
    delay(100);
    lcd.update();
    if (digitalRead(button) == LOW) {
      x2 = 24;
    }
    if (digitalRead(button1) == LOW) {
      x2 = 48;
    }
    lcd.drawBitmap(0, 0, secondframe, 84, 48);
    lcd.drawBitmap(x2, 37, car, 12, 8);
    lcd.drawBitmap(x3, y2, bad, 12, 8);
    lcd.drawBitmap(x4, y3, bad, 12, 8);
    lcd.drawRect(x5, y4,  x5 + 4, y4 + 4);


    y2++;
    y3++;
    y4++;

    if (y2 >= 34 && y2 <= 44) {
      if (x2 == 24 && x3 == 28) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
      if (x2 == 48 && x3 == 44) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
    }
    if (y3 >= 34 && y3 <= 44) {
      if (x2 == 24 && x4 == 28) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
      if (x2 == 48 && x4 == 44) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
    }
    if (y4 >= 34 && y4 <= 44) {
      if (x2 == 24 && x5 == 30) {
        y4 = 12;
        score1++;

        if (random(1, 3) == 1) {
          x5 = 30;
        } else {
          x5 = 50;
        }
      }
      if (x2 == 48 && x5 == 50) {
        y4 = 12;
        score1++;

        if (random(1, 3) == 1) {
          x5 = 30;
        } else {
          x5 = 50;
        }
      }
    }  lcd.printNumI(score1, 1, 13);

    delay(100);
    lcd.update();
    if (digitalRead(button) == LOW) {
      x2 = 24;
    }
    if (digitalRead(button1) == LOW) {
      x2 = 48;
    }
    lcd.drawBitmap(0, 0, firstframe, 84, 48);
    lcd.drawBitmap(x2, 37, car, 12, 8);
    lcd.drawBitmap(x3, y2, bad, 12, 8);
    lcd.drawBitmap(x4, y3, bad, 12, 8);
    lcd.drawRect(x5, y4,  x5 + 4, y4 + 4);



    y2++;
    y3++;
    y4++;
    lcd.printNumI(score1, 1, 13);

    delay(100);
    lcd.update();
    y2++;
    y3++;
    y4++;
    if (y2 >= 34 && y2 <= 44) {
      if (x2 == 24 && x3 == 28) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
      if (x2 == 48 && x3 == 44) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
    }
    if (y3 >= 34 && y3 <= 44) {
      if (x2 == 24 && x4 == 28) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
      if (x2 == 48 && x4 == 44) {
        lcd.clrScr();
        lcd.print("GAME OVER ", CENTER , 1);
        over2 = true;

      }
    }
    if (y4 >= 34 && y4 <= 44) {
      if (x2 == 24 && x5 == 30) {
        y4 = 12;
        score1++;

        if (random(1, 3) == 1) {
          x5 = 30;
        } else {
          x5 = 50;
        }
      }
      if (x2 == 48 && x5 == 50) {
        y4 = 12;
        score1++;

        if (random(1, 3) == 1) {
          x5 = 30;
        } else {
          x5 = 50;
        }
      }
    }
    lcd.printNumI(score1, 1, 13);
  }
}
void TIME() {

  if (digitalRead(button1) == LOW) {
    score = 0;
    inTIME == false;
    loop();
  };
  lcd.update();
  lcd.update();



  lcd.clrScr();

  Time t = rtc.time();

  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  char tr[50];

  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d ",
           day.c_str(),
           t.yr, t.mon, t.date);
  snprintf(tr, sizeof(tr), "%02d:%02d:%02d ",
           t.hr, t.min, t.sec);
  lcd.setFont(TinyFont);

  lcd.print(buf, CENTER, 10);
  lcd.print(tr, CENTER, 20);

  lcd.update();

}
void GAME1() {
  if (over) {
    if (digitalRead(button1) == LOW) {
      score = 0;
      ingame1 == false;
      loop();
    };
    lcd.update();
  }
  if (digitalRead(button1) == LOW) {
    if (x <= 52) {
      x++;
      a = 2;
    }

  }


  if (digitalRead(button) == LOW) {
    if (x >= 2) {
      x--;
      a = 2;
    }
  }
  lcd.setFont(SmallFont);

  if (over == false) {
    //UI//
    lcd.clrScr();
    lcd.setFont(TinyFont);
    lcd.drawRect(x, 40, x + 2, 42);

    // lcd.drawBitmap(x,0,elsys,84,84);
    lcd.print("score:", 59, 1);
    lcd.drawRect(0, 0, 83, 47);
    lcd.setFont(SmallFont);
    lcd.printNumI(score, 58 , 7);
    lcd.drawLine(56, 84, 56, 0);
    //UI//
    //ROWS/1/
    Serial.println(spawn);

    if (Y1 == 48) {
      Y1 = 0;
      X1 = random(0, 53);
      score++;

    }
    lcd.drawLine(0, Y1, X1, Y1);
    lcd.drawLine(X1 + 4, Y1, 57 , Y1);


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
    if (spawn % 3 == 0) {
      Y1 += 2;
    }//
  }
  //lose cond
  if (Y1 >= 40 && Y1 <= 42 ) {
    if (x < X1 || x >= X1 + 2) { //|| x<=X2 || x>=X2+3 || x<=X3 || x>=X3+3 && Y1>=40 && Y1 <=42 || Y2>=40 && Y2 <=42 || Y3>=40 && Y3 <=42){

      lcd.clrScr();
      lcd.print("GAME OVER ", CENTER , 1);
      over = true;
    }
  }
  lcd.update();
  delay(20);
  spawn++;
}



