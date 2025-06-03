#include "gameObjectFactory.h"
#include "iconFactory.h"
#include <memory>
#include <stdlib.h>
#include <vector>

void GameObjectFactory::add_object(std::unique_ptr<RPSGameObject> obj) {
	objs.push_back(std::move(obj));
}

void GameObjectFactory::create_object() {
	add_object(std::unique_ptr<RPSGameObject>(new RPSGameObject()));
}

std::vector<RPSGameObject *> GameObjectFactory::get_objs() {
	std::vector<RPSGameObject *> raw_ptrs;
	for ( const auto &uptr : objs ) {
		raw_ptrs.push_back(uptr.get());
	}
	return raw_ptrs;
}
