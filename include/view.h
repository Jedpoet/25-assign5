#ifndef VIEW_H
#define VIEW_H
#include "gameObject.h"
#include "unit.h"
#include <string>
#include <utility>
#include <vector>

class View {
  public:
	View();
	void render();
	void updateGameObject(GameObject *);
	void resetLatest();
	void readPlayerPos(Position);

  private:
	int _termWidth;
	int _termHeight;
	std::vector<std::vector<std::string>> latest_map, last_map;
	std::vector<std::vector<Color>> latest_fg_color, last_fg_color;
	std::vector<std::vector<Color>> latest_bg_color, last_bg_color;
	static std::pair<int, int> get_terminal_size();
	Position player_pos;
};

#endif
