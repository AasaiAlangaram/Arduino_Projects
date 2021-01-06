//setup pins
const char BUTTON_PIN = 8;
bool pressed = false;
bool ledState = false;
bool lastTime = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
  long elapsedTime = millis() - lastTime;
  lastTime = lastTime + elapsedTime;

  readButton();
  //readADC();
  blink(elapsedTime);
}

void blink(long elapsedMS)
{
  static long ledTime = 0;
  ledTime = ledTime + elapsedMS;

  if(ledTime >= 1000){
    ledState ^= ledState;
    digitalWrite(LED_BUILTIN, ledState);
    ledTime = ledTime - 1000;
  }
}

void readButton(){
  bool currentState = digitalRead(BUTTON_PIN);

  if(currentState == pressed)
  {
    Serial.println("Hello");
    while(digitalRead(BUTTON_PIN) == pressed){
      //Do nothing while button is pressed
    }
  }
}
