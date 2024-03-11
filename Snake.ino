
/*
	Snake game

	Playing snake on a LED matrix MAX7219.

	The circuit:
	- red and green LED attached from pin 12 and 11 respectively to ground through 220 ohm resistors
	- pushbutton (speed sensor) attached to pin 2 from +5V
	- 10K resistor attached to pushbutton from ground

	- LED matrix max7219 8x8
		* VCC: to Arduino 5V
		* GND: to Arduino GND
		* DIN (Data In): to pin 11
		* CLK (Clock): to pin 13
		* CS (Chip Select): to pin 5
*/

#include <GyverMAX7219.h>

#define DIN_PIN 11
#define CLK_PIN 13
#define CS_PIN 5

MAX7219 <CLK_PIN, DIN_PIN, CS_PIN> led;

const int game_speed_sensor = A0;
const int reset_button = 2;
const int red_led = 8;
const int green_led = 9;

int score_value = 0;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  // initialize the reset button pin as an input:
  pinMode(reset_button, INPUT);
  // LED matrix
  lc.shutdown(0,false); 
  lc.setIntensity(0,50);
  lc.clearDisplay(0);

  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, HIGH);
  delay(2000);
  digitalWrite(red_led, LOW);
}

void loop() {
  
  // read the state of the reset button value:
  int reading_reset = digitalRead(reset_button);
  if (reading_reset == HIGH) {
      digitalWrite(red_led, HIGH);
      digitalWrite(green_led, LOW);
      delay(2000);
      digitalWrite(red_led, LOW);
      digitalWrite(green_led, HIGH);
  }
  float reading_speed = analogRead(game_speed_sensor) * (5.0 / 1023.0);
  // Serial.print("Value of reading speed: ");
  // Serial.println(reading_speed);
  // delay(200);
  int game_speed = reading_speed / 4;


}
