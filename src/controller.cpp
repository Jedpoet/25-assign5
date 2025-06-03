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

	player = 0;
	nums[0] = 0;
	nums[1] = 0;
	nums[2] = 0;

	for ( auto obj : _objs ) {
		switch ( rng.getInt(1, 3) ) {
		case 1:
			obj->setType(RPSType::ROCK);
			nums[0]++;
			break;
		case 2:
			obj->setType(RPSType::SCISSORS);
			nums[1]++;
			break;
		case 3:
			obj->setType(RPSType::PAPER);
			nums[2]++;
			break;
		}
	}
	if ( nums[0] != 0 ) {
		nextPlayer();
		_objs[player]->playerSwitch();
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
			_view.readPlayerPos(_objs[player]->getPosition());
		}

		// check collision
		for ( auto *obj1 : _objs ) {
			for ( auto *obj2 : _objs ) {
				if ( obj1 == obj2 ) {
					continue;
				}
				int battle;
				if ( obj1->intersect(obj2) ) {
					battle = obj1->onCollision(obj2);
					battle = obj2->onCollision(obj1);
				}

				switch ( battle ) {
				case 1:
					nums[0]++;
					nums[1]--;
					break;
				case 2:
					nums[1]++;
					nums[2]--;
					break;
				case 3:
					nums[2]++;
					nums[0]--;
					break;
				case 4:
					nums[0]++;
					nums[1]--;
					_objs[player]->playerSwitch();
					nextPlayer();
					_objs[player]->playerSwitch();
					break;
				default:
					break;
				}
			}
		}

		int count = 0;
		for ( int i = 0; i < 3; i++ ) {
			if ( nums[i] == 0 ) {
				count++;
			}
		}

		if ( count == 2 ) {

			if ( nums[0] != 0 ) {
				std::cout << "ROCK ";
			}
			else if ( nums[1] != 0 ) {
				std::cout << "SCISSORS ";
			}
			else if ( nums[2] != 0 ) {
				std::cout << "PAPER ";
			}
			std::cout << "WIN!" << std::endl;
			break;
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
		_objs[player]->setDirection(Direction::UP);
		break;
	case 'a':
	case 'h':
		_objs[player]->setDirection(Direction::LEFT);
		break;
	case 's':
	case 'j':
		_objs[player]->setDirection(Direction::DOWN);
		break;
	case 'd':
	case 'l':
		_objs[player]->setDirection(Direction::RIGHT);
		break;
	case 'q':
	case 'y':
		_objs[player]->setDirection(Direction::TOP_LIFT);
		break;
	case 'e':
	case 'u':
		_objs[player]->setDirection(Direction::TOP_RIGHT);
		break;
	case 'z':
	case 'b':
		_objs[player]->setDirection(Direction::DOWN_LIFT);
		break;
	case 'c':
	case 'n':
		_objs[player]->setDirection(Direction::DOWN_RIGHT);
		break;

	case 'x':
	case 'o':
		_objs[player]->playerSwitch();
		nextPlayer();
		_objs[player]->playerSwitch();
		break;

	default:
		break;
	}
}

void Controller::update() {
}

void Controller::nextPlayer() {
	while ( _objs[player++]->getType() != ROCK ) {
		if ( player >= _objs.size() ) {
			player = 0;
		}
	}
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
