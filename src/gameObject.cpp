// TODO implementation

#include "gameObject.h"

GameObject::GameObject() {
}

GameObject::~GameObject() {
}

Position GameObject::getPosition() const {
	return _pos;
}

Icon GameObject::getIcon() const {
	return _icon;
}
