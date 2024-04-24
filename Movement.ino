void  reset() {

	led.line(0, 0, 7, 7);  // (x0, y0, x1, y1)
	led.line(7, 0, 0, 7);
	led.update();
	delay(1000);
	led.clear();
}

void  reset_food_coor() {

	led.dot(food[0], food[1], 0);
	food[0] = random(0,7);
	food[1] = random(0,7);
	led.dot(food[0], food[1], 1);
	led.update();
}

void  food_status() {

	if (snake[0].x_coor == food[0] && snake[0].y_coor == food[1]) {
		grow();
		reset_food_coor();
	}
}

void  grow() {

	snake[snake_length].x_coor = food[0];
	snake[snake_length].y_coor = food[1];
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

	int length = snake_length - 4;
	if (length < 1)
		length = 0;
	for (unsigned int i = 0; i < length; ++i) {
		Serial.print("snake length = ");
		Serial.println(snake_length);
		Serial.print(" ---- value of i: ");
		Serial.println(i);
		Serial.print("length: ");
		Serial.println(length);
		delay(1000);
		Serial.print("\n ____snake[i].x_coor: ");
		Serial.println(snake[i].x_coor);
		Serial.print(" ____snake[i + 4].x_coor: ");
		Serial.println(snake[i + 4].x_coor);
		Serial.print(" ____snake[i].y_coor: ");
		Serial.println(snake[i].y_coor);
		Serial.print(" ____snake[i + 4].y_coor: ");
		Serial.println(snake[i + 4].y_coor);
		delay(1000);
		if (snake[0].x_coor == snake[i + 4].x_coor
				&& snake[0].y_coor == snake[i + 4].y_coor) {
			Serial.println("=== collison check ===\n");
			return 1;
		}
        
	}
	Serial.println("END of collison check");
	return 0;
}

int movement(unsigned int game_speed) {

	blink(game_speed);
	if (collision() == 1) {
		reset();
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
