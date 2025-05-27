#include "gameObjectFactory.h"
#include "RPSGameObject.h"
#include "gameObject.h"
#include "iconFactory.h"
#include <memory>
#include <stdlib.h>
#include <vector>

void GameObjectFactory::add_object(std::unique_ptr<GameObject> obj) {
	objs.push_back(std::move(obj));
}

void GameObjectFactory::create_object() {
	add_object(std::unique_ptr<GameObject>(new RPSGameObject()));
}

std::vector<GameObject *> GameObjectFactory::get_objs() {
	std::vector<GameObject *> raw_ptrs;
	for ( const auto &uptr : objs ) {
		raw_ptrs.push_back(uptr.get());
	}
	return raw_ptrs;
}
