#pragma once

#include <SFML/Graphics.hpp>

class Delayer {
public:
	static void makeDelay(float seconds) {
		sf::Clock clock;
		clock.restart();
		do {
			
		} while (clock.getElapsedTime().asSeconds() < seconds);
	}

};