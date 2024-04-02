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

void   on() {

	for (int i = 0; i < snake_length; ++i) {
		led.dot(snake[i].x_coor, snake[i].y_coor, 1);
	}
	led.update();
}

void	off(unsigned int game_speed) {

	for (int i = 0; i < snake_length; ++i) {
		led.dot(snake[i].x_coor, snake[i].y_coor, 0);
	}
	delay(100 + game_speed);
	led.update();
}

void	update_snake_pos() {

	for (int i = snake_length; i > 0; --i) {
		snake[i].x_coor = snake[i - 1].x_coor;
		snake[i].y_coor = snake[i - 1].y_coor;
	}
}

/*	functions to change directions	*/

void move_up(unsigned int game_speed) {
	if (previous_direction == DOWN) {
		move_down(game_speed);					// ignore command of going into opposite direction
		return;
	}
	// update snake's coordinate system
	on();
	off(game_speed);
	update_snake_pos();
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
	on();
	off(game_speed);
	update_snake_pos();
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
	on();
	off(game_speed);
	update_snake_pos();
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
	on();
	off(game_speed);
	update_snake_pos();
	if (snake[0].y_coor == 0)
		snake[0].y_coor = 8;
	snake[0].y_coor -= 1;
	food_status();
	previous_direction = LEFT;
}

