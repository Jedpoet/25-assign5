
#include "RPSGameObject.h"
#include "gameObject.h"
#include "unit.h"
#include <memory>
#include <vector>

class GameObjectFactory {
  public:
	GameObjectFactory() = default;
	void create_object();
	std::vector<GameObject *> get_objs();

  private:
	void add_object(std::unique_ptr<GameObject> obj);
	std::vector<std::unique_ptr<GameObject>> objs;
};
