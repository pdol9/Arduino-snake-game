/*
   Snake game

   Playing snake on a LED matrix MAX7219.

   The circuit:
	 * red and green LED attached from pin 8 and 9 respectively to ground through 220 ohm resistors
	 * pushbutton (reset button) attached to pin 2 from +5V with 10K resistor attached to pushbutton
	 from ground
	 * 10k potentiometer (game's speed controller) attached to A0, with other connectors to ground and 5V
	 * LED matrix max7219 8x8
		 - VCC: to Arduino 5V
		 - GND: to Arduino GND
		 - DIN (Data In): to pin 11
		 - CLK (Clock): to pin 13
		 - CS (Chip Select): to pin 5
 */

#include <GyverMAX7219.h>

#define DIN_PIN 11
#define CLK_PIN 13
#define CS_PIN 5

typedef struct snake_location {
  int x_coor;
  int y_coor;
} t_snake_location;

enum  direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum direction current_direction = RIGHT;
enum direction previous_direction = RIGHT;

t_snake_location snake[64];

MAX7219 <CLK_PIN, DIN_PIN, CS_PIN> led;

// potentiometer
const int game_speed_sensor = A0;
// joystick controller
const int y_axis = A1;
const int x_axis = A2;

const int reset_button_score = 2;
const int red_led = 8;
const int green_led = 9;

unsigned int snake_length = 1;
unsigned int food[2];

void greeting_screen(unsigned int fill) {

	for (int i = 0; i < 8; ++i) {
		transition(100);
		led.dot(i, 0, fill);
	}
	for (int i = 1; i < 8; ++i) {
		transition(100);
		led.dot(7, i, fill);
	}
	for (int i = 6; i >= 0; --i) {
		transition(100);
		led.dot(i, 7, fill);
	}
	for (int i = 6; i > 1; --i) {
		transition(100);
		led.dot(0, i, fill);
	}
	led.dot(1, 2, fill);
	if (fill == 0)
		transition(2000);
	/// display S letter
	for (int i = 2; i < 6; ++i) {
		transition(100);
		led.dot(2, i, fill);
	}
	led.dot(3, 5, fill);
	transition(100);
	for (int i = 5; i > 1; --i) {
		led.dot(4, i, fill);
		transition(100);
	}
	led.dot(5, 2, fill);
	transition(100);
	for (int i = 2; i < 6; ++i) {
		led.dot(6, i, fill);
		transition(100);
	}
}

inline void  transition(unsigned int added_time) {
	led.update();
	delay(added_time);
}

void setup() {
	Serial.begin(9600);
	randomSeed(analogRead(0));

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
	delay(1000);
	digitalWrite(red_led, LOW);

	for (int i = 0; i < 64; ++i) {
		snake[i].x_coor = 0;
		snake[i].y_coor = 0;
	}
	snake[0].x_coor = 3;
	snake[0].y_coor = 3;

	// run greeting screen
	//  for (int clear_greeting_screen = 1; clear_greeting_screen > -1; --clear_greeting_screen) {
	//  	greeting_screen(clear_greeting_screen);
	//  }
	//  delay(1000);
	led.update();
	update_food();
}

/// main code

// TODO make snake bigger
// TODO snake collision

void loop() {

	int reading_speed = analogRead(game_speed_sensor);
	update_direction();
	change_direction(reading_speed);

	// read the state of the reset button value:
	// int reading_reset = digitalRead(reset_button_score);
	// if (reading_reset == HIGH) {
	// 	digitalWrite(red_led, HIGH);
	// 	digitalWrite(green_led, LOW);
	// 	delay(2000);
	// 	digitalWrite(red_led, LOW);
	// 	digitalWrite(green_led, HIGH);
	// }
}

inline void change_direction(unsigned int game_speed) {

	switch (current_direction) {
		case UP: move_up(game_speed); break;
		case DOWN: move_down(game_speed); break;
		case LEFT: move_left(game_speed); break;
		case RIGHT: move_right(game_speed); break;
	}
}

void	update_direction() {

	int pos_x = analogRead(x_axis);
	int pos_y = analogRead(y_axis);

	if (pos_x > 900)
		current_direction = DOWN;
	else if (pos_x < 10)
		current_direction = UP;
	else if (pos_y > 900)
		current_direction = LEFT;
	else if (pos_y < 10)
		current_direction = RIGHT;
}
