#ifndef ELEMENT_H
#define ELEMENT_H

#include "RNG.h"
#include "icon.h"
#include "unit.h"

class GameObject {

  public:
	Position getPosition() const;
	Icon getIcon() const;
	virtual void update() = 0;
	virtual ~GameObject() = 0;

  protected:
	GameObject();

	Position _pos;
	Icon _icon;
	RNG rng = RNG();
};

#endif
