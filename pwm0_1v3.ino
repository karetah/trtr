#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27); 


byte PWM_OUTL = 9;
byte PWM_OUTR = 10;
byte ACCEL = A2;
byte REV_CTRL = 4;
byte REV_OUT = 3;
bool REV_ST;

int value;
int mapped;
unsigned long now;
unsigned long lastSecond = 0;

void setup() {
    lcd.begin(16, 2);
       lcd.setBacklight(127);
  lcd.home();
  lcd.clear();
TCCR1A = 0b00000001;  // 8bit
TCCR1B = 0b00001010;  // x8 fast pwm

pinMode (PWM_OUTL, OUTPUT);
pinMode (PWM_OUTR, OUTPUT);
pinMode (REV_OUT, OUTPUT);
pinMode (REV_CTRL, INPUT_PULLUP);
//Serial.begin(9600);
}

void loop() {

  now = millis();


  REV_ST = digitalRead(REV_CTRL);
  value = analogRead(ACCEL);

mapped = map(value, 0, 925, 255, 0);
if (mapped < 50) {
  mapped = 0;
if (REV_ST == HIGH) { digitalWrite(REV_OUT,LOW); }
  else { digitalWrite(REV_OUT,HIGH); }
  analogWrite(PWM_OUTL, mapped);
  analogWrite(PWM_OUTR, mapped);
  //Serial.println(value);
  //Serial.println(mapped);
  //delay(500);
  
} else {
    if (mapped > 255 ) mapped = 255;
  analogWrite(PWM_OUTL, mapped);
  analogWrite(PWM_OUTR, mapped);
  
  //Serial.println(value);
  //  Serial.println(mapped);
  //delay(500);
 
} 
  if (now - lastSecond > 2000) 
  {
  lcd.clear();
  lcd.setCursor(0, 0);  
  //lcd.print("ACCEL :");  
  lcd.print(value);
  lcd.setCursor(0, 1);  
  //lcd.print("mapped :");  
  lcd.print(mapped);
     lastSecond = now;
  }
  
}
