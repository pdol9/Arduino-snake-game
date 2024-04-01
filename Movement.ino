
void  update_food() {
	led.dot(food[0], food[1], 0);
	food[0] = random(0,7);
	food[1] = random(0,7);
	led.dot(food[0], food[1], 1);
	led.update();
}

void  food_status() {
	if (snake[0].x_coor == food[0] && snake[0].y_coor == food[1]) {
		grow();
		update_food();
	}
}

void  grow() {
	Serial.print("BEFORE FOOD snake length: ");
	Serial.println(snake_length);

	snake[snake_length].x_coor = food[0];
	snake[snake_length].y_coor = food[1];
	snake_length += 1;
	Serial.print("AFTER FOOD snake length: ");
	Serial.println(snake_length);

	for (int i = 0; i < snake_length; ++i) {

		Serial.print("snake-> [ ");
		Serial.print(snake[i].x_coor);
		Serial.print(" ");
		Serial.print(snake[i].y_coor);
		Serial.println(" ]");
	}
	delay(500);
}

void   move(unsigned int game_speed) {
	Serial.print("position: [ ");
	Serial.print(snake[0].x_coor);
	Serial.print(" ");
	Serial.print(snake[0].y_coor);
	Serial.println(" ]");

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

// main functions to move

void move_up(unsigned int game_speed) {
	if (previous_direction == DOWN) {
		move_down(game_speed);					// ignore command of going into opposite direction
		return;
	}
	// update snake's coordinate system
	for (int i = 0; i < snake_length; ++i) {
		if (snake[i].x_coor == 7)
			snake[i].x_coor = -1;
		snake[i].x_coor += 1;
	}
	food_status();
	move(game_speed);
	previous_direction = UP;
}

void  move_down(unsigned int game_speed) {
	if (previous_direction == UP) {
		move_up(game_speed);
		return;
	}
	for (int i = 0; i < snake_length; ++i) {
		if (snake[i].x_coor == 0)
			snake[i].x_coor = 8;
		snake[i].x_coor -= 1;
	}
	food_status();
	move(game_speed);
	previous_direction = DOWN;
}

void move_right(unsigned int game_speed) {
	if (previous_direction == LEFT) {
		move_left(game_speed);
		return;
	}
	for (int i = 0; i < snake_length; ++i) {
		if (snake[i].y_coor == 7)
			snake[i].y_coor = -1;
		snake[i].y_coor += 1;
	}
	food_status();
	move(game_speed);
	previous_direction = RIGHT;
}

void move_left(unsigned int game_speed) {
	if (previous_direction == RIGHT) {
		move_right(game_speed);
		return;
	}
	for (int i = 0; i < snake_length; ++i) {
		if (snake[i].y_coor == 0)
			snake[i].y_coor = 8;
		snake[i].y_coor -= 1;
	}
	food_status();
	move(game_speed);
	previous_direction = LEFT;
}

