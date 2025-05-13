#include "iconFactory.h"
#include "icon.h"
#include <vector>

Icon *IconFactory::create_icon(int type) const {
	Icon *icon = new Icon;
	std::string block = "█";
	if ( type == 1 ) {
		std::vector<Cell> temp(2, Cell(RED, block));
		for ( int i = 0; i < 2; i++ ) {
			icon->push_back(temp);
		}
	}
	else {
		std::vector<Cell> temp(3, Cell(BLUE, block));
		for ( int i = 0; i < 3; i++ ) {
			icon->push_back(temp);
		}
	}
	return icon;
}
