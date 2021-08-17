#include "Board.h"

void Board::drawOnWindow(sf::RenderWindow& window) {
	for (int i = 0; i < 9; ++i) {
		if (positions[i].symbol == 'x') positions[i].sprite.setTexture(m_crossTexture);
		if (positions[i].symbol == 'o') positions[i].sprite.setTexture(m_circleTexture);
		window.draw(positions[i].plate.getSprite());
		window.draw(positions[i].sprite);
	}
	window.draw(m_sprite);
}

void Board::initializePositions() {
	for (int i = 0; i < 9; ++i) {
		positions[i].plate.setTexture(m_plateTexture);
		positions[i].sprite.setTexture(m_plateTexture);
		positions[i].symbol = '?';
	}
	positions[0].plate.setPosition(0, 0);
	positions[1].plate.setPosition(150, 0);
	positions[2].plate.setPosition(300, 0);
	positions[3].plate.setPosition(0, 150);
	positions[4].plate.setPosition(150, 150);
	positions[5].plate.setPosition(300, 150);
	positions[6].plate.setPosition(0, 300);
	positions[7].plate.setPosition(150, 300);
	positions[8].plate.setPosition(300, 300);

	positions[0].sprite.setPosition(0, 0);
	positions[1].sprite.setPosition(150, 0);
	positions[2].sprite.setPosition(300, 0);
	positions[3].sprite.setPosition(0, 150);
	positions[4].sprite.setPosition(150, 150);
	positions[5].sprite.setPosition(300, 150);
	positions[6].sprite.setPosition(0, 300);
	positions[7].sprite.setPosition(150, 300);
	positions[8].sprite.setPosition(300, 300);
	
}

void Board::makeMoveOneP(sf::Event& event) {
	//player move
	bool hasPlayerMoved = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkCurrentGameState() == GameStates::CONTINUES) {
		for (int i = 0; i < 9; ++i) {
			if (positions[i].plate.isPressed(event) && positions[i].symbol == '?') {
				positions[i].symbol = 'x';
				positions[i].plate.playSound();
				hasPlayerMoved = true;
			}
		}
	}
	//AI move
	if (hasPlayerMoved && checkCurrentGameState() == GameStates::CONTINUES) {
		bool isStepDone = false;
		while (!isStepDone) {
			int randomChoice = Randomizer::randomizeBetween(0, 8);
			if (positions[randomChoice].symbol == '?') {
				positions[randomChoice].symbol = 'o';
				isStepDone = (positions[randomChoice].symbol == 'o' ? true : false);
				if (positions[randomChoice].symbol == 'o') break;

			}
		}
	}
}
void Board::makeMoveTwoP(sf::Event& event) {
	//player1 move
	static bool hasPlayerOneMoved = false;	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkCurrentGameState(true) == GameStates::CONTINUES && hasPlayerOneMoved == false) {
		for (int i = 0; i < 9; ++i) {
			if (positions[i].plate.isPressed(event) && positions[i].symbol == '?') {
				positions[i].symbol = 'x';
				positions[i].plate.playSound();
				hasPlayerOneMoved = true;
			}
		}
	}
	//player2 move			
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && checkCurrentGameState(true) == GameStates::CONTINUES && hasPlayerOneMoved == true) {
		for (int i = 0; i < 9; ++i) {
			if (positions[i].plate.isPressed(event, Button::RIGHT) && positions[i].symbol == '?') {
				positions[i].symbol = 'o';
				positions[i].plate.playSound();		
				hasPlayerOneMoved = false;
			}
		}
	}
	
}
bool Board::areThereAnyFreePlates() const {
	for (int i = 0; i < 9; ++i) if (positions[i].symbol == '?') return true;
	return false;
}

Board::GameStates Board::checkCurrentGameState(bool twoPlayers) const {
	if ((positions[0].symbol == 'x' && positions[1].symbol == 'x' && positions[2].symbol == 'x') ||
		(positions[3].symbol == 'x' && positions[4].symbol == 'x' && positions[5].symbol == 'x') ||
		(positions[6].symbol == 'x' && positions[7].symbol == 'x' && positions[8].symbol == 'x') ||
		(positions[0].symbol == 'x' && positions[3].symbol == 'x' && positions[6].symbol == 'x') ||
		(positions[1].symbol == 'x' && positions[4].symbol == 'x' && positions[7].symbol == 'x') ||
		(positions[2].symbol == 'x' && positions[5].symbol == 'x' && positions[8].symbol == 'x') ||
		(positions[0].symbol == 'x' && positions[4].symbol == 'x' && positions[8].symbol == 'x') ||
		(positions[2].symbol == 'x' && positions[4].symbol == 'x' && positions[6].symbol == 'x'))
		return (twoPlayers == false ? GameStates::PLAYER_WON : GameStates::PLAYER1_WON);

	else if ((positions[0].symbol == 'o' && positions[1].symbol == 'o' && positions[2].symbol == 'o') ||
		(positions[3].symbol == 'o' && positions[4].symbol == 'o' && positions[5].symbol == 'o') ||
		(positions[6].symbol == 'o' && positions[7].symbol == 'o' && positions[8].symbol == 'o') ||
		(positions[0].symbol == 'o' && positions[3].symbol == 'o' && positions[6].symbol == 'o') ||
		(positions[1].symbol == 'o' && positions[4].symbol == 'o' && positions[7].symbol == 'o') ||
		(positions[2].symbol == 'o' && positions[5].symbol == 'o' && positions[8].symbol == 'o') ||
		(positions[0].symbol == 'o' && positions[4].symbol == 'o' && positions[8].symbol == 'o') ||
		(positions[2].symbol == 'o' && positions[4].symbol == 'o' && positions[6].symbol == 'o')) 
		return (twoPlayers == false ? GameStates::AI_WON : GameStates::PLAYER2_WON);
	else if (areThereAnyFreePlates()) return GameStates::CONTINUES;
	else return GameStates::DRAFT;

}