#include <LiquidCrystal.h>
using namespace std;

// Array of Output Pin variables, set to the pins being used by the 
// LCD
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Input Pin Variables
const int buzzer   = 3;
const int joyClick = 2;
const int xAxis    = A1;
const int yAxis    = A0;

// Jpystick Constant Varianles
const int xAxis_median = 508;
const int yAxis_median = 514;
const char plusMinus = 100;
const int xAxisLeft = xAxis_median - plusMinus;
const int xAxisRight = xAxis_median + plusMinus;
const int yAxisUp = yAxis_median - plusMinus;
const int yAxisDown = yAxis_median + plusMinus;

//SM1 Specific Variables
unsigned char cnt;
unsigned short col, row;
//const char words[5][10];
String words[10] = {"SNAKE", "HAPPY", "WITCH", "LUNCH", "SWORD", "ZEBRA", 
"VALUE", "DIGIT", "BASIC", "CRIME"};


// Digital Read Helper Function
// if joystick is clicked, returns 'J'
// if stick right, returns 'R'
// and so on...
const unsigned char digitalReadHelper()
{
  const unsigned char jClick = digitalRead(joyClick);
  const int xState = analogRead(xAxis);
  const int yState = analogRead(yAxis);
  
  if(jClick == LOW)
  {
    Serial.println("joyCLick Pressed");
    return 'J';
  }
  else if(xState < xAxisLeft &&  yAxisUp < yState && yState < yAxisDown)
  {
    Serial.println("joystick left");
    return 'L';
  }
  else if(xState > xAxisRight &&  yAxisUp < yState && yState < yAxisDown)
  {
    Serial.println("joystick right");
    return 'R';
  }
  else if(yState < yAxisUp && xAxisLeft < xState && xState < xAxisRight)
  {
    Serial.println("joystick up");
    return 'U';
  }
  else if(yState > yAxisDown && xAxisLeft < xState && xState < xAxisRight)
  {
    Serial.println("joystick down");
    return 'D';
  }
  else if(xState < xAxisLeft && yState < yAxisUp)
  {
    Serial.println("joystick Up Left");
    return 'W';
  }
  else if(xState > xAxisRight && yState < yAxisUp)
  {
    Serial.println("joystick Up Right");
    return 'X';
  }
  else if(yState > yAxisDown && xState > xAxisRight)
  {
    Serial.println("joystick Down Right");
    return 'Y';
  }
  else if(yState > yAxisDown && xState < xAxisLeft)
  {
    Serial.println("joystick Down Left");
    return 'Z';
  } 
  return 'N';
}

enum SM1_STATES {WAIT, ACTIVE};

int SM1_Tick(int state)
{
  switch(state)
  {}

  switch(state)
  {}
  return state;
}

// Task Scheduler
typedef struct task
{
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int(*TickFunc)(int);
} task;

int delay_gcd;
const unsigned short NUMBER_OF_TASKS = 1;
task tasks[NUMBER_OF_TASKS];

void setup()
{
  // Set the pinMode for the Joystick Button
  pinMode(joyClick, INPUT_PULLUP);

  Serial.begin(9600);
  lcd.begin(16,2);

  col = 0;
  row = 0;
  
  // Set up of Task Scheduler
  unsigned char i = 0;
  tasks[i].state = WAIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFunc = &SM1_Tick;
}

void loop()
{
  unsigned char i;
   for(i = 0; i < NUMBER_OF_TASKS; i++)
  {
    if( (millis() - tasks[i].elapsedTime) >= tasks[i].period)
    {
        tasks[i].state = tasks[i].TickFunc(tasks[i].state);
        tasks[i].elapsedTime = millis(); // last time task was ran
    }
  }
  //delay(delay_gcd); // GCD
  //Serial.println(b_buf);
}