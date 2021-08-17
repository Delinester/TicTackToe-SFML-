#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Randomizer.h"
#include "Button.h"

class Board {
public:	
	enum class GameStates {
		PLAYER_WON,
		AI_WON,
		DRAFT,
		PLAYER1_WON,
		PLAYER2_WON,
	    CONTINUES
	};
	struct OnePosition {
		sf::Sprite sprite;
		char symbol;
		Button plate;	
		OnePosition(){}
	};
	Board(int w, int h, std::string boardFilePath, std::string plateFilepath, std::string crossFilePath, std::string circleFilePath)
		: m_w(w), m_h(h), m_filePath(boardFilePath), m_plateFilepath(plateFilepath), m_crossFilePath(crossFilePath), 
		m_circleFilepath(circleFilePath)
	{
		m_texture.loadFromFile(m_filePath);
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_w, m_h));

		m_plateTexture.loadFromFile(m_plateFilepath);		

		m_crossTexture.loadFromFile(m_crossFilePath);		

		m_circleTexture.loadFromFile(m_circleFilepath);		
	}

	void drawOnWindow(sf::RenderWindow& window);

	void initializePositions();

	void makeMoveOneP(sf::Event& event);
	void makeMoveTwoP(sf::Event& event);
	bool areThereAnyFreePlates() const;

	GameStates checkCurrentGameState(bool twoPlayers = false) const;
	
private:
	OnePosition positions[9];	

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int m_w, m_h;
	std::string m_filePath;

	std::string m_crossFilePath;
	sf::Texture m_crossTexture;	

	std::string m_plateFilepath;
	sf::Texture m_plateTexture;	

	std::string m_circleFilepath;
	sf::Texture m_circleTexture;	
};


