#pragma once
#include "Hand.h"

class Dealer {

private:
	Hand _hand;
	Card* _hiddenCard;

public:

	Dealer();

	void displayHand();

	void addCard(Card card);

	void addHiddenCard();

	void setHiddenCard(Card card);

	Hand& getHand();

	void newHand();
};
