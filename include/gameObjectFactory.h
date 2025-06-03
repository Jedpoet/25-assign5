
#include "RPSGameObject.h"
#include <memory>
#include <vector>

class GameObjectFactory {
  public:
	GameObjectFactory() = default;
	void create_object();
	std::vector<RPSGameObject *> get_objs();

  private:
	void add_object(std::unique_ptr<RPSGameObject> obj);
	std::vector<std::unique_ptr<RPSGameObject>> objs;
};
