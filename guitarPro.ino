#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BUTTON_NEXT 13
#define BUTTON_PROTECTION 100
#define LONG_PRESS 1000
#define PATTERN_STRING 1
#define INFO_STRING 3

//паттерны
int fingers[][6]={
  {1343,1434,1341,1314,1431,1413},
  {3143,3413,3414,3141,3134,3431},
  {4143,4341,4134,4314,4131,4313}
  };
int curFinger = 0;
#define MAXFINGER 3
int curPos = 0;
#define MAXPOS 6
int curString=4;
int maxStrings=6; //сделать возможность указать количество струн
int stringsCounter = 0;
int lad=5;
bool btnPressed=1;

LiquidCrystal_I2C lcd(0x3f,20,4);  

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

void printPattern(int pattern)
{
  String curPattern = String(pattern);
  size_t j;
  for(j=0;j<4;j++)
  {
    lcd.setCursor(10+j+j,PATTERN_STRING);
    lcd.print(curPattern[j]);
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
  shuffle(fingers[curFinger], 6);

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

void setup()
{
  pinMode(BUTTON_NEXT, INPUT_PULLUP);
  shuffle(fingers[curFinger], 6);
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("EASY mode");
  lcd.setCursor(0,INFO_STRING);
  lcd.print("STRING: ");
  lcd.setCursor(11,INFO_STRING);
  lcd.print("POS: ");
  lcd.setCursor(0,PATTERN_STRING);
  lcd.print("Pattern: ");
  
//когда добавлю рандом выбора позиции убрать 
  lcd.setCursor(16,INFO_STRING);
  lcd.print(lad);
  
}


void loop()
{
if(digitalRead(BUTTON_NEXT) == LOW)
{
  //пауза для защиты от дребезга
  delay(BUTTON_PROTECTION);  
  //повторный опрос кнопки
  if(digitalRead(BUTTON_NEXT) == LOW)
  {
    //один раз выводим текст
    btnPressed = 1;
    //ничего не делаем, пока кнопка нажата
    while(digitalRead(BUTTON_NEXT) == LOW);
    delay(BUTTON_PROTECTION);
    }
  }

//зато не надо отдельно выводить информацию до первого нажатия кнопки. Вывели и ждем
  if (btnPressed == 1)
  {
    printPattern(fingers[curFinger][curPos]);
    //выводим струну
    lcd.setCursor(8,INFO_STRING);
    lcd.print(curString);
    nextStep();
    btnPressed = 0;
  }

}
