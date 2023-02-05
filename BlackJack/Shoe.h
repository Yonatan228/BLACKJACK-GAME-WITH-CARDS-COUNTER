#pragma once
#include "Card.h"
#include <time.h>
#include <list>
#include <stack>
#include "GlobalVariables.h"

class Shoe {

private:
	stack<Card> _shoe;
	list<Card> _temp;
	int _cutCard;
	bool _isLastHandBeforeReshuffle;

	void createCards() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < N_OF_CARDS / 4; j++) {
				this->_temp.push_back(Card(FACES[j % 13], SUITS[i], FACE_TO_VALUES.at(FACES[j % 13])));
			}
		}
	}

	void shuffleAndStack() {
		list<Card>::iterator it = this->_temp.begin();
		srand(time(0));

		//shuffle and push to stack
		for (int i = N_OF_CARDS; i > 0; i--) {
			advance(it, rand() % i);
			this->_shoe.push(*it);
			this->_temp.erase(it);
			it = this->_temp.begin();
		}
	}

	void insertCutCard() {
		int offset = N_OF_CARDS / 4;
		int range = (N_OF_CARDS / 3.33) - offset + 1;
		this->_cutCard = offset + (rand() % range);
	}

	void emptyShoe() {
		while (!this->_shoe.empty())
			this->_shoe.pop();
	}

public:

	Shoe() {
		createShoe();
	}

	void createShoe() {
		this->_isLastHandBeforeReshuffle = false;
		NEW_SHOE = true;
		emptyShoe();
		createCards();
		shuffleAndStack();
		insertCutCard();
		DECKS_REMAINING = N_OF_DECKS;
	}

	Card getCard() {
		if (this->_shoe.size() == this->_cutCard) {
			this->_isLastHandBeforeReshuffle = true;
		}
		Card card = this->_shoe.top();
		this->_shoe.pop();
		DECKS_REMAINING = round(this->_shoe.size() / 52.0);
		return card;
	}

	bool isLastHand() {
		return this->_isLastHandBeforeReshuffle;
	}
};
