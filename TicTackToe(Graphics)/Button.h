#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Delayer.h"

class Button {
public:
	enum MouseButton {
		LEFT,
		RIGHT
	};
	Button() : Button(150, 150, "Textures\\whitePlate.png", "Sounds\\plateSound.wav")
	{

	}
	Button(int w, int h, std::string filePath = "Def", std::string soundFilePath = "Def",
		float x = 0, float y = 0) : m_w(w), m_h(h), m_filePath(filePath), m_x(x), m_y(y)
	{
		m_texture.loadFromFile(m_filePath);
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(x, y);

		m_sBuffer.loadFromFile(soundFilePath);
		m_sound.setBuffer(m_sBuffer);
	}	
	
	sf::Sprite& getSprite() { return m_sprite; }	

	void setTexture(sf::Texture& texture) {	m_sprite.setTexture(texture); }
	void setPosition(float x, float y) { 
		m_x = x;
		m_y = y; 
		m_sprite.setPosition(sf::Vector2f(m_x, m_y));
	}

	void playSound();
	bool isPressed(sf::Event& event, MouseButton button = MouseButton::LEFT);
private:
	int m_w, m_h;
	float m_x, m_y;
	std::string m_filePath;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	

	sf::SoundBuffer m_sBuffer;
	sf::Sound m_sound;

	sf::Clock clock;
};

