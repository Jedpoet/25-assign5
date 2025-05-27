#include <ctime>
#include <iostream>
#include <termios.h>
#include <thread>
#include <unistd.h>

#include "RPSGameObject.h"
#include "controller.h"
#include "environment.h"

Controller::Controller(View &view) : _view(view) {
	int time = rng.getInt(15, 30);
	for ( int i = 0; i < time; i++ ) {
		factory.create_object();
	}
	_objs = factory.get_objs();

	for ( auto obj : _objs ) {
		if ( auto rpsObj = dynamic_cast<RPSGameObject *>(obj) ) {
			switch ( rng.getInt(1, 3) ) {
			case 1:
				rpsObj->setType(RPSType::ROCK);
				players.push_back(rpsObj);
				break;
			case 2:
				rpsObj->setType(RPSType::SCISSORS);
				break;
			case 3:
				rpsObj->setType(RPSType::PAPER);
				break;
			}
		}
	}
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

			obj->update();

			_view.updateGameObject(obj);
		}

		// check collision
		for ( GameObject *obj1 : _objs ) {
			for ( GameObject *obj2 : _objs ) {
				auto rpsObj1 = dynamic_cast<RPSGameObject *>(obj1);
				auto rpsObj2 = dynamic_cast<RPSGameObject *>(obj2);
				if ( !rpsObj1 || !rpsObj2 || rpsObj1 == rpsObj2 ) {
					continue;
				}
				if ( rpsObj1->intersect(rpsObj2) ) {
					rpsObj1->onCollision(rpsObj2);
					rpsObj2->onCollision(rpsObj1);
				}
			}
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

	// handle key events.
	switch ( keyInput ) {
	case 'w':
	case 'k':
		players[player]->setDirection(Direction::UP);
		break;
	case 'a':
	case 'h':
		players[player]->setDirection(Direction::LEFT);
		break;
	case 's':
	case 'j':
		players[player]->setDirection(Direction::DOWN);
		break;
	case 'd':
	case 'l':
		players[player]->setDirection(Direction::RIGHT);
		break;
	case 'q':
	case 'y':
		players[player]->setDirection(Direction::TOP_LIFT);
		break;
	case 'e':
	case 'u':
		players[player]->setDirection(Direction::TOP_RIGHT);
		break;
	case 'z':
	case 'b':
		players[player]->setDirection(Direction::DOWN_LIFT);
		break;
	case 'c':
	case 'n':
		players[player]->setDirection(Direction::DOWN_RIGHT);
		break;

	case 'x':
	case 'o':
		player++;
		if ( player == players.size() ) {
			player = 0;
		}
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
