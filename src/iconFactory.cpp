#include "iconFactory.h"
#include "RPSGameObject.h"
#include "icon.h"
#include <vector>

Icon *IconFactory::create_icon(RPSGameObject *obj) const {
	Icon *icon = new Icon;
	std::string block = "█";
	std::string rock = "R";
	std::string scissors = "S";
	std::string paper = "P";

	std::vector<RPSGameObject *> players;
	if ( obj->isPlayer() ) {
		std::vector<Cell> temp(1, Cell(YELLOW, rock));
		for ( int i = 0; i < 1; i++ ) {
			icon->push_back(temp);
		}
	}
	else if ( obj->getType() == ROCK ) {
		std::vector<Cell> temp(1, Cell(GREEN, rock));
		for ( int i = 0; i < 1; i++ ) {
			icon->push_back(temp);
		}
	}
	else if ( obj->getType() == SCISSORS ) {
		std::vector<Cell> temp(1, Cell(RED, scissors));
		for ( int i = 0; i < 1; i++ ) {
			icon->push_back(temp);
		}
	}
	else {
		std::vector<Cell> temp(1, Cell(CYAN, paper));
		for ( int i = 0; i < 1; i++ ) {
			icon->push_back(temp);
		}
	}
	return icon;
}
