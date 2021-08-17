#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Board.h"
#include "ProgramStatesHandler.h"

int main() {
	srand(static_cast<unsigned int>(time(0)));
	rand();

	sf::RenderWindow window(sf::VideoMode(450, 450), "Tic Tac Toe");
	window.setFramerateLimit(30);

	ProgramStatesHandler programState;

	sf::Music music;
	music.openFromFile("Sounds\\music.wav");
	music.setLoop(true);
	music.play();
	
	Board board(450, 450, "Textures\\board.png", "Textures\\whitePlate.png", "Textures\\cross.png", "Textures\\circle.png");
	board.initializePositions();
	

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		if (board.checkCurrentGameState() != Board::GameStates::CONTINUES && 
			programState.getProgramState() != ProgramStatesHandler::MENU) {
			programState.setProgramState(ProgramStatesHandler::ENDGAME);			
		}
		if (programState.getProgramState() == ProgramStatesHandler::MENU) {
			programState.initializeMenu(board, window, event);
			std::cout << "MENU\n";
		}
		else if (programState.getProgramState() == ProgramStatesHandler::IN_GAME) {
			programState.initializeGame(board, event, window);
			std::cout << "IN_GAME\n";
		}
		else if (programState.getProgramState() == ProgramStatesHandler::ENDGAME) {
			programState.initializeEndScreen(board, event, window);
			std::cout << "ENDGAME\n";
		}
			window.display();		

	}
	return 0;
}