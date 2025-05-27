#include "gameObject.h"
#include "environment.h"

GameObject::GameObject() {
	_pos = {rand() % (GAME_WINDOW_WIDTH - 2),
	        rand() % (GAME_WINDOW_HEIGHT - 2)};
}

GameObject::~GameObject() {
}

Position GameObject::getPosition() const {
	return _pos;
}

Icon GameObject::getIcon() const {
	return _icon;
}
