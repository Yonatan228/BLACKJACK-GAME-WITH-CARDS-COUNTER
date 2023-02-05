#pragma once
#include "Hand.h"
#include "GlobalVariables.h"

class Player {

private:
	Hand _hand;
	Hand _hand2;
	int _bankroll;

public:

	void displayHand(int n = 1) {
		if (n == 1)
			this->_hand.displayHand();
		else
			this->_hand2.displayHand();
	}

	void addCard(Card card, int n = 1) {
		CARD_COUNTER.addToCount(card);
		if (n == 1)
			this->_hand.addCard(card);
		else
			this->_hand2.addCard(card);
	}

	void splitCards(Card card1, Card card2) {
		this->_hand2.addCard(this->_hand.getCards().back());
		this->_hand.getCards().pop_back();
		addCard(card1);
		addCard(card2, 2);
	}

	void addWinnings(int amount) {
		this->_bankroll += amount;
	}

	Hand& getHand(int n = 1) {
		if (n == 1)
			return this->_hand;
		else
			return this->_hand2;
	}

	void newHand() {
		this->_hand.init();
		this->_hand2.init();
	}

	void setBankroll(int n) {
		this->_bankroll = n;
	}
		
	int getBankroll() {
		return this->_bankroll;
	}
};