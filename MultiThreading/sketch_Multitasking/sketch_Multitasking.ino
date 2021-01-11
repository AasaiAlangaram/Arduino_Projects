// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//setup pins
const char BUTTON_PIN = 7;
//ADC Monitor
int sensorPin = A0;    // select the input pin for the potentiometer
int ADCledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

bool pressed = true;
bool ledState = false;
//LED_100ms initial state
bool ledState1 = false;
bool ledState2 = false;
unsigned long lastTime = millis();

void setup() {
  
  // put your setup code here, to run once:
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Arduino_Multitasking!");
  
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(ADCledPin, OUTPUT);

  digitalWrite(8, ledState1);
  digitalWrite(9, ledState2);
  digitalWrite(10, ledState);
  digitalWrite(ADCledPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long elapsedTime = millis() - lastTime;
  lastTime = lastTime + elapsedTime;

  //Sub-routines call for blink, readButton, readADC and displayLCD.
  blink(elapsedTime);
  readButton();
  readADC();
  display_LCD(elapsedTime);
}

void blink(unsigned long elapsedMS)
{
  static unsigned long l_ledTime = 0;
  static unsigned long l_ledTime1 = 0;
  static unsigned long l_ledTime2 = 0;

  //local variable to store the elapsed time
  l_ledTime = l_ledTime + elapsedMS;
  l_ledTime1 = l_ledTime1 + elapsedMS;
  l_ledTime2 = l_ledTime2 + elapsedMS;

  //condition for 100ms led
  if(l_ledTime1 >= 100){
    ledState1 = !ledState1;
    digitalWrite(8, ledState1);
    l_ledTime1 = l_ledTime1 - 100;
  }

  //condition for 500ms led
  if(l_ledTime2 >= 500){
    ledState2 = !ledState2;
    digitalWrite(9, ledState2);
    l_ledTime2 = l_ledTime2 - 500;
  }

  //condition for 1000ms led
  if(l_ledTime >= 1000){
    ledState = !ledState;
    digitalWrite(10, ledState);
    l_ledTime = l_ledTime - 1000;
  }


}

void readButton(){
  bool currentState = digitalRead(BUTTON_PIN);

  if(currentState == pressed)
  {
    Serial.println("Button Pressed");
    while(digitalRead(BUTTON_PIN) == pressed){
      //Do nothing while button is pressed
    }
  }
}

void readADC()
{
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue > 512)
  {
    digitalWrite(ADCledPin, HIGH);
  }
  else
  {
    digitalWrite(ADCledPin, LOW);
  }
    
}

void display_LCD(unsigned long elapsedMS){

  static unsigned long l_lcdtimeout = 0;
  static unsigned long l_flag = 0;

  l_lcdtimeout = l_lcdtimeout + elapsedMS;

  
  if(l_lcdtimeout >= 1000){
      // Turn off the display:
      l_flag = !l_flag;
      l_lcdtimeout = l_lcdtimeout - 1000;
  }

  if(l_flag)
  {
    lcd.display();
  }
  else
  {
    lcd.clear();
  }

}
