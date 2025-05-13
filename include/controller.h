#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "gameObject.h"
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
	int next_step;
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
