#include "iconFactory.h"
#include "RPSGameObject.h"
#include "icon.h"
#include <vector>

Icon *IconFactory::create_icon(RPSType type) const {
	Icon *icon = new Icon;
	std::string block = "█";
	if ( type == ROCK ) {
		std::vector<Cell> temp(1, Cell(GREEN, block));
		for ( int i = 0; i < 1; i++ ) {
			icon->push_back(temp);
		}
	}
	else if ( type == SCISSORS ) {
		std::vector<Cell> temp(1, Cell(RED, block));
		for ( int i = 0; i < 2; i++ ) {
			icon->push_back(temp);
		}
	}
	else {
		std::vector<Cell> temp(1, Cell(WHITE, block));
		for ( int i = 0; i < 2; i++ ) {
			icon->push_back(temp);
		}
	}
	return icon;
}
