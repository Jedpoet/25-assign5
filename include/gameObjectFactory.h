// TODO
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller.

#include "gameObject.h"
#include <vector>

class Player : public GameObject {
  public:
	Player();
	void update(int next_step);
};

class Block : public GameObject {
  public:
	Block();
	void update(int next_step);
};

class GameObjectFactory : public Player, public Block {
  public:
	GameObjectFactory(){};
	void creat_object(int type);
	std::vector<GameObject *> get_objs();

  private:
	void add_object(GameObject *obj);
	std::vector<GameObject *> objs;
};
