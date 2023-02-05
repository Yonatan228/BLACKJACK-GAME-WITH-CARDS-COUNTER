#pragma once
#include "Hand.h"

class Player {

private:
	Hand _hand;
	Hand _hand2; // for split case
	int _bankroll;

public:

	Player();

	void displayHand(int n = 1);

	void addCard(Card card, int n = 1);

	void splitCards(Card card1, Card card2);

	void addWinnings(int amount);

	Hand& getHand(int n = 1);

	void newHand();

	void setBankroll(int n);
		
	int getBankroll() const;
};