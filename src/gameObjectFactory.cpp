#include "gameObjectFactory.h"
#include "environment.h"
#include "gameObject.h"
#include "iconFactory.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

Player::Player() : GameObject() {
	srand(time(NULL));
	_pos = {rand() % (GAME_WINDOW_WIDTH - 2),
	        rand() % (GAME_WINDOW_HEIGHT - 2)};
	IconFactory factory = IconFactory();
	_icon = *factory.create_icon(1);
}

void Player::update(int next_step) {
	switch ( next_step ) {
	case 1:
		_pos.x() += 1;
		break;
	case 2:
		_pos.y() += 1;
		break;
	case 3:
		_pos.x() -= 1;
		break;
	case 4:
		_pos.y() -= 1;
		break;
	}
}

Block::Block() : GameObject() {
	srand(time(NULL));
	_pos = {rand() % (GAME_WINDOW_WIDTH - 3),
	        rand() % (GAME_WINDOW_HEIGHT - 3)};
	IconFactory factory = IconFactory();
	_icon = *factory.create_icon(2);
}

void Block::update(int next_step) {
}

void GameObjectFactory::creat_object(int type) {
	if ( type == 1 ) {
		add_object(new Player());
	}
	else {
		add_object(new Block());
	}
}

void GameObjectFactory::add_object(GameObject *obj) {
	objs.push_back(obj);
}

std::vector<GameObject *> GameObjectFactory::get_objs() {
	return objs;
}
