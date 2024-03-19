/*
	Snake game

	Playing snake on a LED matrix MAX7219.

	The circuit:
	- red and green LED attached from pin 8 and 9 respectively to ground through 220 ohm resistors
	- pushbutton (reset button) attached to pin 2 from +5V with 10K resistor attached to pushbutton
    from ground
  - 10k potentiometer (game's speed controller) attached to A0, with other connectors to ground and 5V

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
// joystick controller
const int y_axis = A1;
const int x_axis = A2;

const int reset_button_score = 2;
const int red_led = 8;
const int green_led = 9;

int score_value = 0;
unsigned char snake_size = 2;
unsigned char snake_position_x = 5;
unsigned char snake_position_y = 5;
unsigned char food[2];

inline void  transition(int added_time) {
    led.update();
    delay(100 + added_time);
}

void greeting_screen(unsigned int fill) {

  for (int i = 0; i < 8; ++i) {
    transition(0);
    led.dot(i, 0, fill);
  }
  for (int i = 1; i < 8; ++i) {
    transition(0);
    led.dot(7, i, fill);
  }
  for (int i = 6; i >= 0; --i) {
    transition(0);
    led.dot(i, 7, fill);
  }
  for (int i = 6; i > 1; --i) {
    transition(0);
    led.dot(0, i, fill);
  }
  led.dot(1, 2, fill);
  if (fill == 0)
    transition(2000);
/// S letter
  for (int i = 2; i < 6; ++i) {
    transition(0);
    led.dot(2, i, fill);
  }
  led.dot(3, 5, fill);
  transition(0);
  for (int i = 5; i > 1; --i) {
    led.dot(4, i, fill);
    transition(0);
  }
  led.dot(5, 2, fill);
  transition(0);
  for (int i = 2; i < 6; ++i) {
    led.dot(6, i, fill);
    transition(0);
  }
}

void setup() {
  Serial.begin(9600);
 
  // initialize the LED pin as an output:
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  // initialize the reset button pin as an input:
  pinMode(reset_button_score, INPUT);
  
  // LED matrix
  led.begin();
  led.clear();

  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, HIGH);
  delay(2000);
  digitalWrite(red_led, LOW);
  
  int fill = 2;

repeat:
  fill -= 1;
  greeting_screen(fill);
  if (fill == 1)
    goto repeat;

  led.update();
  delay(3000);
  set_food();
}
void  set_food() {
  food[0] = 4;
  food[1] = 4;
  led.dot(food[0], food[1], 1);
  led.update();
}
void  update_food() {
  led.dot(food[0], food[1], 0);
  food[1] = 8 - snake_position_x;
  food[0] = 8 - snake_position_y;
  led.dot(food[0], food[1], 1);
  led.update();
}

int  check_food() {
  if (snake_position_x == food[0] || snake_position_y == food[1])
    return 1;
  return 0;
}

inline void  move_down() {

}
inline void move_right() {

}
inline void move_up() {
  if (snake_position_y == 7)
    snake_position_y = 0;
  else
    ++snake_position_y;
}
inline void move_left() {
  if (snake_position_y == 0)
    snake_position_y = 8;
  --snake_position_y;
    led.dot(snake_position_x, snake_position_y, 1);
    transition(200);
    led.dot(snake_position_x, snake_position_y, 0);
}

void loop() {

  int pos_x = analogRead(x_axis);
  int pos_y = analogRead(y_axis);
  // Serial.println(pos_x);
  // Serial.println(pos_y);
  move_left();
  // if (check_food() == 1)
  //   update_food();

  // read the state of the reset button value:
  int reading_reset = digitalRead(reset_button_score);
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
