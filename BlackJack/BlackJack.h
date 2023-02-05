#pragma once
#include "Player.h"
#include "Dealer.h"
#include "Shoe.h"
#include <windows.h>

class BlackJack {

private:
	Shoe _shoe;
	Dealer _dealer;
	Player _player;
	int _bet;
	int _originalBet;
	int _winnings;
	int _choice;
	bool _isPlayerTurn;
	bool _isSplitCase;
	int _handTurn;

public:

	BlackJack();

	void init();

	void play(int deposit);

	void playerTurn(int n = 1);

	void dealerTurn();

	void blackJackCaseLogic();

	void standCaseLogic(int n = 1);

	void hitCaseLogic(int n = 1);

	void doubleCaseLogic();

	void splitCaseLogic();

	void compare(int n = 1);

	void display();

	void deal();

	void placeYourBet();

	void displayChoices();

	void clearConsole();
};
