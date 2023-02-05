#pragma once
#include "Hand.h"
#include "GlobalVariables.h"

class Dealer {

private:
	Hand _hand;
	Card* _hiddenCard = NULL;

public:

	void displayHand() {
		this->_hand.displayHand();
	}

	void addCard(Card card) {
		CARD_COUNTER.addToCount(card);
		this->_hand.addCard(card);
	}

	void addHiddenCard() {
		CARD_COUNTER.addToCount(*this->_hiddenCard);
		this->_hand.addCard(*this->_hiddenCard);
	}

	void setHiddenCard(Card card) {
		this->_hiddenCard = new Card(card);
	}

	Hand& getHand() {
		return this->_hand;
	}

	void newHand() {
		this->_hand.init();
		this->_hiddenCard = NULL;
	}
};
