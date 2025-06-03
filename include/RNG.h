#ifndef RNG_H
#define RNG_H

#include <random>

class RNG {
  public:
	RNG() : gen(std::random_device{}()) {
	}

	int getInt(int low, int high) {
		std::uniform_int_distribution<> dist(low, high);
		return dist(gen);
	}

  private:
	std::mt19937 gen;
};

#endif
