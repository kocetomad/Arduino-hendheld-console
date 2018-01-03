#include <DS1302.h>
#include <stdio.h>
#include <gfxfont.h>

#include <LCD5110_Graph.h>
LCD5110 lcd(11, 10, 9, 8, 12);
DS1302 rtc(A5, A4, A3);
extern uint8_t elsys [];
extern uint8_t enm [];
extern uint8_t plr [];
const int button = 2;
const int button1 = 3;
const int action = 4;
bool check=true;
extern unsigned char TinyFont[];
extern unsigned char SmallFont[];
int a = 1 ;
int x = 27;
int spawn = 0;
int Y1;
int X1;
bool klik=true;
/*int Y2;
  int Y3;*/
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
bool inTIME=false;
//  int X3;
bool over = false;
void setup() {
  Serial.begin(9600);

  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
  lcd.InitLCD();
  Y1 = 0;
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
  if(inTIME){
  TIME();
  }
  if(ingame2){
  GAME2();
   }
  if(ingame1){
   GAME1();
   }
   if(ingame1==false && ingame2==false && inTIME==false){
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
  if (digitalRead(action) == LOW) {
    switch (m) {
      case 0: ingame1 = true;
        break;
      case 1: ingame2 = true;
        break;
      case 2: inTIME=true;
        break;
    }
  }
  if (digitalRead(button1) == LOW) {
    if (m == 2) {
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
  lcd.print("GAME 1", CENTER , 15);
  lcd.invertText(false);

  if (m == 1) {
    lcd.invertText(true);
  }
  lcd.print("GAME 2", CENTER , 25);
  lcd.invertText(false);
  if (m == 2) {
    lcd.invertText(true);
  }
  lcd.print("TIME", CENTER , 35);
  lcd.invertText(false);

  lcd.update();
  //delay (5);

}
void TIME(){
   
    if (digitalRead(button) == LOW) {score=0;ingame1==false ; ingame2==false ; inTIME==false; klik==false;loop();};
   
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

  lcd.print(buf,CENTER,10);
    lcd.print(tr,CENTER,20);

  lcd.update();

}
void GAME1() {
  if(over){
    if (digitalRead(button) == LOW) {score=0;ingame1==false;loop();};
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
      Y1+=2;
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

void GAME2() {
  if (digitalRead(button1) == LOW) {
    x++;
  }
  if (digitalRead(action) == LOW) {
    if (pressed == false) {
      if (fires[2] != 1) {

        fire++;
      }
      if (fire == 1 && fires[2] != 1) {
        shotpos1[0] = x + 7;
        fires[0] = 1;
      }
      if (fire == 2 && fires[2] != 1) {
        shotpos1[1] = x + 7;
        fires[1] = 1;
      }
      if (fire == 3 && fires[2] != 1) {
        shotpos1[2] = x + 7;
        fires[2] = 1;
      }
      pressed = true;
    }
  } else {
    pressed = false;
  }
  if (digitalRead(button) == LOW) {
    x--;
  }
  lcd.clrScr();
  // lcd.drawBitmap(0,0,elsys,84,84);

  lcd.drawBitmap(x, 40, plr, 10, 7);
  if ( X2 <= 10 && spawn % 3 == 0) {
    X2++;
  }
  lcd.drawBitmap(30, X2, enm, 10, 8);
  //WAT>>>!!!?
  if (fires[0] == 1) { //TUKA SA STRELYA
    lcd.drawLine(shotpos1[0], 42 - dvijenie_na_shota_v_game_2[0], shotpos1[0] , 39 - dvijenie_na_shota_v_game_2[0]);
  }
  if (fires[1] == 1) { //TUKA SA STRELYA
    lcd.drawLine(shotpos1[1], 42 - dvijenie_na_shota_v_game_2[1], shotpos1[1] , 39 - dvijenie_na_shota_v_game_2[1]);
  }
  if (fires[2] == 1) { //TUKA SA STRELYA
    lcd.drawLine(shotpos1[2], 42 - dvijenie_na_shota_v_game_2[2], shotpos1[2] , 39 - dvijenie_na_shota_v_game_2[2]);
  }
  lcd.setPixel(33, X2);

  if (shotpos1[0] >= 33 && shotpos1[0] <= 37 && dvijenie_na_shota_v_game_2[0] >= X2 + 10) {
    X2 = -10;
    dvijenie_na_shota_v_game_2[0] = 0;
    fires[0] = 0;
    fire--;
  }
  if (dvijenie_na_shota_v_game_2[0] == 42) {
    dvijenie_na_shota_v_game_2[0] = 0;
    fires[0] = 0;
    fire--;

  } else if (fires[0] == 1) {
    dvijenie_na_shota_v_game_2[0]++;
  }
  if (shotpos1[1] >= 33 && shotpos1[1] <= 37 && dvijenie_na_shota_v_game_2[1] >= X2 + 10) {
    X2 = -10;
    dvijenie_na_shota_v_game_2[1] = 0;
    fires[1] = 0;
    fire--;
  }
  if (dvijenie_na_shota_v_game_2[1] == 42) {
    dvijenie_na_shota_v_game_2[1] = 0;
    fires[1] = 0;
    fire--;

  } else if (fires[1] == 1) {
    dvijenie_na_shota_v_game_2[1]++;
  }
  if (shotpos1[2] >= 33 && shotpos1[2] <= 37 && dvijenie_na_shota_v_game_2[2] >= X2 + 10) {
    X2 = -10;
    dvijenie_na_shota_v_game_2[2] = 0;
    fires[2] = 0;
    fire = 0;
  }
  if (dvijenie_na_shota_v_game_2[2] == 42) {
    dvijenie_na_shota_v_game_2[2] = 0;
    fires[2] = 0;
    fire = 0;

    // fire=0;
  } else if (fires[2] == 1) {
    dvijenie_na_shota_v_game_2[2]++;
  }
  lcd.update();

  delay(30);
  spawn++;
}

