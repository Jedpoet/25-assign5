#ifndef RPS_H
#define RPS_H

#include "RNG.h"
#include "collider.h"
#include "gameObject.h"

enum RPSType { ROCK, PAPER, SCISSORS };
enum Direction {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	TOP_LIFT,
	TOP_RIGHT,
	DOWN_LIFT,
	DOWN_RIGHT
};

class RPSGameObject : public GameObject, public ICollider {

  public:
	RPSGameObject() : GameObject(){};
	void update() override;
	void onCollision(ICollider *other) override;
	bool intersect(ICollider *other) override;

	RPSType getType() const;
	void setType(RPSType type);
	void setDirection(Direction);

  private:
	RPSType _type;
	Direction _dir;
	RNG rng = RNG();
};
#endif
