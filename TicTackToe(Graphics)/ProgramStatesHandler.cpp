#include "ProgramStatesHandler.h"

void ProgramStatesHandler::initializeMenu(Board& board, sf::RenderWindow& window, sf::Event& event) {
	//Animation
	static float currentFrame = 0;	
	if (currentFrame > 3) currentFrame -= 3;
	menuBgrAnimSprite.setTextureRect(sf::IntRect(int(currentFrame) * 450, 0, 450, 450));
	window.draw(menuBgrAnimSprite);
	currentFrame += 0.05;
	//
	window.draw(onePlayerButton.getSprite());
	window.draw(twoPlayersButton.getSprite());

	if (onePlayerButton.isPressed(event)) {
		onePlayerButton.playSound();		
		restartGame(board);
	}
	if (twoPlayersButton.isPressed(event)) {
		twoPlayersButton.playSound();
		areThereTwoPlayers = true;
		restartGame(board);
	}

	quitButton.setPosition(140, 300);
	window.draw(quitButton.getSprite());

	if (quitButton.isPressed(event)) {
		quitButton.playSound();
		Delayer::makeDelay(0.2);
		window.close();
	}
}
void ProgramStatesHandler::initializeGame(Board& board, sf::Event& event, sf::RenderWindow& window) {
	if (!areThereTwoPlayers)	board.makeMoveOneP(event);
	else board.makeMoveTwoP(event);
	board.drawOnWindow(window);	
}
void ProgramStatesHandler::restartGame(Board& board) {
	board.initializePositions();
	hasEndSoundPlayed = false;
	currentState = States::IN_GAME;
}
void ProgramStatesHandler::initializeEndScreen(Board& board, sf::Event& event, sf::RenderWindow& window) {	
	switch (board.checkCurrentGameState(areThereTwoPlayers)) {
	case Board::GameStates::PLAYER_WON:	
		endText.setString("YOU\n WON");
		if (!hasEndSoundPlayed) endSoundWin.play(); hasEndSoundPlayed = true;  break;
	case Board::GameStates::AI_WON:
		endText.setString("YOU\n LOST");
		if (!hasEndSoundPlayed) endSoundLost.play(); hasEndSoundPlayed = true; break;
	case Board::GameStates::PLAYER1_WON:
		endText.setString("PLAYER\n X WON");
		if (!hasEndSoundPlayed) endSoundWin.play(); hasEndSoundPlayed = true;  break;
	case Board::GameStates::PLAYER2_WON:
		endText.setString("PLAYER\n O WON");
		if (!hasEndSoundPlayed) endSoundWin.play(); hasEndSoundPlayed = true;  break;
	case Board::GameStates::DRAFT:
		endText.setString("DRAFT"); 
		if (!hasEndSoundPlayed) draftSound.play(); hasEndSoundPlayed = true;  break;
	}
	window.draw(endGameBgrSprite);
	window.draw(endText);

	restartButton.setPosition(60, 280);
	window.draw(restartButton.getSprite());
	if (restartButton.isPressed(event)) {
		restartButton.playSound();		
		restartGame(board);
	}

	menuButton.setPosition(240, 300);
	window.draw(menuButton.getSprite());
	if (menuButton.isPressed(event)) {
		menuButton.playSound();
		areThereTwoPlayers = false;
		currentState = States::MENU;
	}

	quitButton.setPosition(60, 350);
	window.draw(quitButton.getSprite());
	if (quitButton.isPressed(event)) {
		quitButton.playSound();		
		Delayer::makeDelay(0.2);
		window.close();
	}
}