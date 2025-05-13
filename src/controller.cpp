#include <ctime>
#include <iostream>
#include <termios.h>
#include <thread>
#include <unistd.h>

#include "controller.h"
#include "environment.h"
#include "gameObjectFactory.h"

Controller::Controller(View &view) : _view(view) {
	GameObjectFactory factory;
	factory.creat_object(1);
	factory.creat_object(2);
	factory.creat_object(2);
	_objs = factory.get_objs();
}

void Controller::run() {
	// initial setup
	std::cin.tie(0);
	std::ios::sync_with_stdio(0);
	configure_terminal();

	// init state
	int input = -1;
	clock_t start, end;

	// Main loop
	while ( true ) {
		start = clock();
		// game loop goes here
		input = read_input();

		// ESC to exit program
		if ( input == 27 )
			break;

		this->handleInput(input);

		_view.resetLatest();
		for ( GameObject *obj : _objs ) {

			obj->update(next_step);

			_view.updateGameObject(obj);
		}

		_view.render();

		end = clock();

		// frame rate normalization
		double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
		if ( time_taken > SPF )
			continue;
		int frameDelay = int((SPF - time_taken) * 1000); // 0.1 seconds
		if ( frameDelay > 0 )
			std::this_thread::sleep_for(
			    std::chrono::milliseconds(frameDelay)); // frame delay
	}
}

void Controller::handleInput(int keyInput) {

	// If there is no input, do nothing.
	if ( keyInput == -1 )
		return;

	// TODO
	// handle key events.
	switch ( keyInput ) {
	case 'w':
		next_step = 1;
		break;
	case 'a':
		next_step = 2;
		break;
	case 's':
		next_step = 3;
		break;
	case 'd':
		next_step = 4;
		break;
	default:
		break;
	}
}

void Controller::update() {
}
void reset_terminal() {
	printf("\e[m");    // reset color changes
	printf("\e[?25h"); // show cursor
	fflush(stdout);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
	tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit

	new_termios.c_lflag &=
	    ~(ICANON | ECHO); // turn off echo + non-canonical mode
	new_termios.c_cc[VMIN] = 0;
	new_termios.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

	printf("\e[?25l"); // hide cursor
	std::atexit(reset_terminal);
}

int read_input() {
	fflush(stdout);
	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
	return n > 0 ? buf[n - 1] : -1;
}
