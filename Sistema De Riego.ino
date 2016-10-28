#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


Servo servo_Motor;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
 
char* password = "1995AB";
int position = 0;
const byte ROWS = 4; 
const byte COLS = 4;
 
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 34, 35, 36, 37 };
byte colPins[COLS] = { 38, 39, 40, 41 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int redPin = 12;
int greenPin = 13;

void setup()
{
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
lcd.begin(16,2);
servo_Motor.attach(11);
setLocked(true);
}

void loop()
{
  
lcd.setCursor(1,0);     
lcd.print("Panel Control"); 
lcd.setCursor(1,1);     
lcd.print("Green Watering"); 

char key = keypad.getKey();
if (key == '*' || key == '#')
{
position = 0;
setLocked(true);
}
if (key == password[position])
{
position ++;
}
if (position == 6)
{
setLocked(false);
}
delay(100);
}
void setLocked(int locked)
{
if (locked)
{
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, LOW);
servo_Motor.write(11);
}
else
{
digitalWrite(redPin, LOW);
digitalWrite(greenPin, HIGH);
servo_Motor.write(90);
}
}


