#pragma once
#include <cstdlib>

class Randomizer {
public:
	static int randomizeBetween(int min, int max) {			
		static const double fraction = 1.0 / static_cast<double>(RAND_MAX + 1.0);
		return static_cast<int>(rand() * fraction * (static_cast<double>(max) - static_cast<double>(min) + 1) + static_cast<double>(min));
	}
};

