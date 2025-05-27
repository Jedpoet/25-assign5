#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "RPSGameObject.h"
#include "gameObject.h"
#include "gameObjectFactory.h"
#include "view.h"
#include <termios.h>
#include <vector>

class Controller {

  public:
	Controller(View &);
	void run();

  private:
	void handleInput(int);
	void update();

	// Model
	std::vector<GameObject *> _objs;

	// View
	View &_view;
	int player = 0;
	std::vector<RPSGameObject *> players;
	RNG rng = RNG();
	GameObjectFactory factory;
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
