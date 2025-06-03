#ifndef RPS_H
#define RPS_H

#include "RNG.h"
#include "collider.h"
#include "gameObject.h"

enum RPSType { ROCK, PAPER, SCISSORS, NONE };
enum Direction {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	TOP_LIFT,
	TOP_RIGHT,
	DOWN_LIFT,
	DOWN_RIGHT,
	STOP
};

class RPSGameObject : public GameObject, public ICollider {

  public:
	RPSGameObject() : GameObject(){};
	void update() override;
	int onCollision(ICollider *other) override;
	bool intersect(ICollider *other) override;

	RPSType getType() const;
	void setType(RPSType type);
	void setDirection(Direction);
	bool isPlayer() const;
	void playerSwitch();

  private:
	RPSType _type;
	Direction _dir;
	RNG rng = RNG();
	bool is_player = false;
};
#endif
