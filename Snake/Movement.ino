void  game_reset() {
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, HIGH);
  led.line(0, 0, 7, 7);  // (x0, y0, x1, y1)
  led.line(7, 0, 0, 7);
  led.update();
  delay(2000);
  digitalWrite(red_led, LOW);
  digitalWrite(blue_led, HIGH);
  delay(1000);
  led.clear();
  fresh_start();
}

void  reset_food_coor() {

  led.dot(food[0], food[1], CLEAR);
  food[0] = random(0,7);
  food[1] = random(0,7);
  led.dot(food[0], food[1], FILL);
  led.update();
}

void  food_status() {

  if (snake[0].x_coor == food[0] && snake[0].y_coor == food[1]) {
    digitalWrite(blue_led, LOW);
    digitalWrite(green_led, HIGH);
    grow();
    delay(800);
    reset_food_coor();
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, HIGH);
  }
}

void  grow() {

  snake[snake_length].x_coor = snake[snake_length - 1].x_coor;
  snake[snake_length].y_coor = snake[snake_length - 1].x_coor;
  snake_length += 1;
}

void	blink(unsigned int game_speed) {

  for (int i = 0; i < snake_length; ++i) {
    led.dot(snake[i].x_coor, snake[i].y_coor, 1);
  }
  led.update();
  for (int i = 0; i < snake_length; ++i) {
    led.dot(snake[i].x_coor, snake[i].y_coor, 0);
  }
  delay(100 + game_speed);
  led.update();
}

/*  update snake's coordinate system  */
void	update_snake_pos() {

  for (int i = snake_length; i > 0; --i) {
    snake[i].x_coor = snake[i - 1].x_coor;
    snake[i].y_coor = snake[i - 1].y_coor;
  }
}

int collision() {

  for (unsigned int i = 4; i < snake_length; ++i) {
    if (snake[0].x_coor == snake[i].x_coor
        && snake[0].y_coor == snake[i].y_coor) {
      Serial.println("=== collison check -> game over ===");
      return 1;
    }
  }
  return 0;
}

int movement(unsigned int game_speed) {

  blink(game_speed);
  if (collision() == 1) {
    game_reset();
    return 1;
  }
  update_snake_pos();
  return 0;
}

/*	functions to change directions	*/

void move_up(unsigned int game_speed) {
  if (previous_direction == DOWN) {
    move_down(game_speed);					// ignore command of going into opposite direction
    return;
  }
  if (movement(game_speed) == 1)
    return ;
  if (snake[0].x_coor == 7)
    snake[0].x_coor = -1;
  snake[0].x_coor += 1;
  food_status();
  previous_direction = UP;
}

void  move_down(unsigned int game_speed) {
  if (previous_direction == UP) {
    move_up(game_speed);
    return;
  }
  if (movement(game_speed) == 1)
    return ;
  if (snake[0].x_coor == 0)
    snake[0].x_coor = 8;
  snake[0].x_coor -= 1;
  food_status();
  previous_direction = DOWN;
}

void move_right(unsigned int game_speed) {
  if (previous_direction == LEFT) {
    move_left(game_speed);
    return;
  }
  if (movement(game_speed) == 1)
    return ;
  if (snake[0].y_coor == 7)
    snake[0].y_coor = -1;
  snake[0].y_coor += 1;
  food_status();
  previous_direction = RIGHT;
}

void move_left(unsigned int game_speed) {
  if (previous_direction == RIGHT) {
    move_right(game_speed);
    return;
  }
  if (movement(game_speed) == 1)
    return ;
  if (snake[0].y_coor == 0)
    snake[0].y_coor = 8;
  snake[0].y_coor -= 1;
  food_status();
  previous_direction = LEFT;
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
