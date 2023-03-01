#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BUTTON_NEXT 13
#define BUTTON_PROTECTION 50
#define BUTTON_SHORT_PRESS_TIME 100
#define BUTTON_LONG_PRESS_TIME 1000
#define LINE_CURR 1
#define LINE_NEXT 3
#define LINE_MENU 2
#define POS_LAD 8
#define POS_STRING 4
#define POS_PATTERN 12

//паттерны
int fingers[][4]={
  {1343,1434,1314,1413},
  {3414,3141,3134,3431},
  {4143,4341,4131,4313}
  };
int curFinger = 0;
#define MAXFINGER 3
int curPos = 0;
#define MAXPOS 4
int curString=4;
int maxStrings=6; //сделать возможность указать количество струн
int stringsCounter = 0;
int lad=5;
bool btnPressed=1;
bool hardMode=0;

LiquidCrystal_I2C lcd(0x3f,20,4);  

void lcdMode(String strMode)
{
  size_t i;
  for (i=0; i< 4; i++)
  {
    lcd.setCursor(1,i);
    lcd.print(strMode[i]);
  }
}

void lcdMenu()
{
  lcd.setCursor(POS_LAD,LINE_MENU);
  lcd.print("*");
    lcd.setCursor(POS_STRING,LINE_MENU);
  lcd.print("|");
}

void lcdPattern(int pattern, int lcdLine)
{
  String curPattern = String(pattern);
  size_t j;
  for(j=0;j<4;j++)
  {
    lcd.setCursor(POS_PATTERN+j+j,lcdLine);
    lcd.print(curPattern[j]);
  }
}

void lcdExersise(int lcdLine)
{
  lcd.setCursor(POS_LAD,lcdLine);
  lcd.print(lad);
  lcd.print(" ");
  lcd.setCursor(POS_STRING,lcdLine);
  lcd.print(curString);
  lcdPattern(fingers[curFinger][curPos], lcdLine);
}

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + random(0,n-i);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

//меняем палец  которого начинаются паттерны
void nextFinger()
{
  curFinger++;
  if (curFinger >= MAXFINGER)
  {
    curFinger -= MAXFINGER;
  }
}

//меняем струну на которой работаем
void nextString()
{
  curString++;
  //проверяем переполнение струн
  if (curString > maxStrings)
  {
    curString -= maxStrings;
  }
  //проверяем лимит
  stringsCounter++;
  if (stringsCounter >= maxStrings)
  {
    stringsCounter -= maxStrings;
    //меняем палец
    nextFinger();
  }
  //не забываем перемешать
  shuffle(fingers[curFinger], MAXPOS);

}

//меняем паттерн для пальца
void nextStep()
{
  curPos++;
  //проверяем переполнение
  if (curPos >= MAXPOS)
  {
    curPos -= MAXPOS;
    //меняем струну
    nextString();
  }
}

void hardStep()
{
  curPos = random(0,MAXPOS - 1);
  curFinger = random(0, MAXFINGER - 1);
  curString = random(1, 6);
  lad = random(1,12); //подумать о более плавном перемещении по всему грифу. 
}

void changeMode()
{
  hardMode = !hardMode;
  if(hardMode == 1)
    lcdMode("HARD");
  else
    lcdMode("EASY");
}

void setup()
{
  pinMode(BUTTON_NEXT, INPUT_PULLUP);
  shuffle(fingers[curFinger], MAXPOS);
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcdMode("EASY");
  lcdMenu();
}

void loop()
{
  //dвынеси меня в функцию
  uint16_t buttonPressTime = 0;
  while(digitalRead(BUTTON_NEXT) == LOW){
    //шаг по шкале времени
    delay(BUTTON_PROTECTION);  
    //считаем время
    buttonPressTime += BUTTON_PROTECTION;
    //это нужно, чтоб счетчик не переполнился, если кто-то уснет на кнопке
    if(buttonPressTime > BUTTON_LONG_PRESS_TIME)
      buttonPressTime = BUTTON_LONG_PRESS_TIME;
  }
  //delay(BUTTON_PROTECTION);

  if(buttonPressTime >= BUTTON_LONG_PRESS_TIME)
    changeMode();

  if(buttonPressTime >= BUTTON_SHORT_PRESS_TIME)
    btnPressed = 1; 

//зато не надо отдельно выводить информацию до первого нажатия кнопки. Вывели и ждем
  if (btnPressed == 1)
  {
    lcdExersise(LINE_CURR);
    if (hardMode == 1)
      hardStep();
    else
      nextStep();
    lcdExersise(LINE_NEXT);
    btnPressed = 0;
  }

}
