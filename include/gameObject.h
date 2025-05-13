#ifndef ELEMENT_H
#define ELEMENT_H

#include "icon.h"
#include "unit.h"
#include <iostream>
#include <vector>
class GameObject {

  public:
	Position getPosition() const;
	Icon getIcon() const;
	virtual void update(int next_step) = 0;
	virtual ~GameObject() = 0;

  protected:
	GameObject();

  protected:
	Position _pos;
	Icon _icon;
};

#endif
