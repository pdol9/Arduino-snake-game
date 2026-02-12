/*
 * 
 *  Snake game
 *
 *  Playing snake on LED matrix MAX7219.
 *
 */

#include <GyverMAX7219.h>

#define DIN_PIN 41
#define CLK_PIN 45
#define CS_PIN 43

#define CLEAR 0
#define FILL 1

typedef struct snake_location {
  uint8_t x_coor;
  uint8_t y_coor;
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

MAX7219 <1,1, CS_PIN, DIN_PIN, CLK_PIN> led;

// potentiometer
const int game_speed_sensor = A0;
// joystick controller
const uint8_t y_axis = A1;
const uint8_t x_axis = A2;

const uint8_t reset_button_score = 2;
const uint8_t pause_button = 3;
volatile bool is_game_paused = false;

// RGB led
const uint8_t blue_led = 8;
const uint8_t green_led = 9;
const uint8_t red_led = 10;

uint8_t snake_length = 1;
uint8_t food[2];

// handle bounce signal
unsigned long last_debounce_time = 0;  // the last time the output pin was toggled
unsigned long debounce_delay = 250;

inline void  transition(unsigned int added_time) {
  led.update();
  delay(added_time);
}

void	fresh_start() {
  for (int i = 0; i < snake_length; ++i) {
    snake[i].x_coor = 0;
    snake[i].y_coor = 0;
  }
  snake[0].x_coor = 3;
  snake[0].y_coor = 3;
  snake_length = 1;
  reset_food_coor();
}

void interrupt_func() {
  if ((millis() - last_debounce_time) > debounce_delay) {
    is_game_paused ^= 1;              // toggle pause button
    if (is_game_paused == false)
      digitalWrite(red_led, LOW);
    else
      digitalWrite(red_led, HIGH);
    last_debounce_time = millis();
  }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(pause_button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pause_button), interrupt_func, CHANGE) ;

  // initialize the LED pin as an output:
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  // initialize the reset button pin as an input:
  pinMode(reset_button_score, INPUT);

  digitalWrite(red_led, HIGH);
  // LED matrix
  led.begin();
  led.clear();

  delay(1000);
  fresh_start();

  // run greeting screen
  for (int clear_greeting_screen = 1; clear_greeting_screen > -1; --clear_greeting_screen) {
    greeting_screen(clear_greeting_screen);
  }
  delay(500);
  led.setBright(2);
  led.update();
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, HIGH);
}

/// main function

void loop() {

  unsigned int game_speed = analogRead(game_speed_sensor);
  update_direction();
  switch (current_direction) {
    case UP: move_up(game_speed); break;
    case DOWN: move_down(game_speed); break;
    case LEFT: move_left(game_speed); break;
    case RIGHT: move_right(game_speed); break;
  }
  while (is_game_paused == true) {
    continue;
  }

  // read the state of the reset button value:
  int reading_reset = digitalRead(reset_button_score);
  if (reading_reset == HIGH) {
    digitalWrite(blue_led, LOW);
    digitalWrite(red_led, HIGH);
    fresh_start();
    delay(2000);
    digitalWrite(red_led, LOW);
    digitalWrite(blue_led, HIGH);
  }
}
