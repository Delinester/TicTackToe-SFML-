#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Button.h"
#include "Board.h"
class ProgramStatesHandler {
public:
	enum States {
		MENU,
		IN_GAME,
		ENDGAME
	};
	ProgramStatesHandler() 
		: onePlayerButton(166, 66, "Textures\\onePlayerButton.png", "Sounds\\startButton.wav", 140, 130),
		twoPlayersButton(166,66, "Textures\\twoPlayersButton.png", "Sounds\\startButton.wav", 140, 200),
		quitButton(170, 70, "Textures\\quitButton.png", "Sounds\\quitSound.wav", 140, 300),
		restartButton(166, 66, "Textures\\restartButton.png", "Sounds\\restartButton.wav", 60, 300),
		menuButton(166,66, "Textures\\menuButton.png", "Sounds\\menuButton.wav", 240, 300)
	{	
		endGameBgrTexture.loadFromFile("Textures\\endGameBgr.png");
		endGameBgrSprite.setTexture(endGameBgrTexture);
		
		endSoundBuffWin.loadFromFile("Sounds\\playerWon.wav");
		endSoundWin.setBuffer(endSoundBuffWin);

		endSoundBuffLost.loadFromFile("Sounds\\playerLost.wav");
		endSoundLost.setBuffer(endSoundBuffLost);

		draftSoundBuff.loadFromFile("Sounds\\draft.wav");
		draftSound.setBuffer(draftSoundBuff);
		
		//
		menuBgrAnimTexture.loadFromFile("Textures\\menuBgrAnim.png");
		menuBgrAnimSprite.setTexture(menuBgrAnimTexture);
		menuBgrAnimSprite.setTextureRect(sf::IntRect(0, 0, 450, 450));
		menuBgrAnimSprite.setPosition(sf::Vector2f(0, 0));
		//
		endFont.loadFromFile("Fonts\\ka1.ttf");
		endText.setFont(endFont);
		endText.setCharacterSize(50);
		endText.setFillColor(sf::Color::White);		
		endText.setPosition(sf::Vector2f(10, 150));
	}
	void initializeMenu(Board& board, sf::RenderWindow& window, sf::Event& event);	

	void initializeGame(Board& board, sf::Event& event, sf::RenderWindow& window);

	void initializeEndScreen(Board& board, sf::Event& event, sf::RenderWindow& window);

	void restartGame(Board& board);

	bool areTwoPlayers() const { return areThereTwoPlayers; }
	void setProgramState(States state) { currentState = state; }
	States getProgramState() const { return currentState; }
private:
	States currentState = MENU;

	Button onePlayerButton;
	Button twoPlayersButton;
	Button quitButton;	
	Button restartButton;
	Button menuButton;

	sf::SoundBuffer endSoundBuffWin;
	sf::Sound endSoundWin;

	sf::SoundBuffer endSoundBuffLost;
	sf::Sound endSoundLost;	

	sf::SoundBuffer draftSoundBuff;
	sf::Sound draftSound;

	sf::Text endText;
	sf::Font endFont;	

	sf::Texture endGameBgrTexture;
	sf::Sprite endGameBgrSprite;
	
	sf::Texture menuBgrAnimTexture;
	sf::Sprite menuBgrAnimSprite;		

	bool hasEndSoundPlayed = false;
	bool areThereTwoPlayers = false;
};

