#include "Button.h"

bool Button::isPressed(sf::Event& event, MouseButton button) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button == LEFT) {
		if ((event.mouseButton.x > m_sprite.getPosition().x) &&
			(event.mouseButton.x < m_sprite.getPosition().x + m_w) &&
			(event.mouseButton.y > m_sprite.getPosition().y) &&
			(event.mouseButton.y < m_sprite.getPosition().y + m_h)) {
			Delayer::makeDelay(0.2);
			return true;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && button == RIGHT) {
		if ((event.mouseButton.x > m_sprite.getPosition().x) &&
			(event.mouseButton.x < m_sprite.getPosition().x + m_w) &&
			(event.mouseButton.y > m_sprite.getPosition().y) &&
			(event.mouseButton.y < m_sprite.getPosition().y + m_h)) {
			Delayer::makeDelay(0.2);
			return true;
		}
	}
	return false;
}

void Button::playSound() {		
	m_sound.play();
}