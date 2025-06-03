#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "RNG.h"
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
	void endgame(int *);

	// Model
	std::vector<RPSGameObject *> _objs;
	void nextPlayer();

	// View
	View &_view;
	int player;
	RNG rng = RNG();
	GameObjectFactory factory;
	int nums[3];
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
