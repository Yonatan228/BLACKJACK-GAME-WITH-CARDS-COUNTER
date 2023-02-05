#pragma once
#include <list>
#include "Card.h"

class Hand {

private:
	list<Card> _cards;
	list<Card>::iterator it;
	int _count;
	bool _isSoftHand;
	bool _isBlackJack;
	bool _splitFlag;
	bool _doubleFlag;
	bool _stand = false;

	void count() {
		this->_count = 0;
		this->_isSoftHand = false;
		for (it = this->_cards.begin(); it != this->_cards.end(); it++) {
			this->_count += it->getValue();
			softHandLogic();
		}
		if (_isBlackJack)
			this->_isSoftHand = false;
	}

	void softHandLogic() {
		if (this->_isSoftHand && this->_count > 21) {
			this->_count -= 10;
			this->_isSoftHand = false;
		}
		if (it->getFace() == "Ace") {
			this->_isSoftHand = true;
			if (this->_count > 21) {
				this->_count -= 10;
				this->_isSoftHand = false;
			}
		}
	}

	void displayCount() {
		if (this->_isBlackJack)
			cout << "-> BLACKJACK";
		else if (this->_count > 21)
			cout << "-> BUST";
		else {
			if (this->_cards.size()==1) // if hidden card
				cout << "[XXXXXXX]";
			cout << " -> count: " << this->_count;
			if (this->_isSoftHand && !this->_stand)
				cout << "/ " << this->_count - 10;
		}
	}

	void displayCards() {
		for (it = this->_cards.begin(); it != this->_cards.end(); it++)
			cout << *it;
	}

	void blackJackCheck() {
		this->_isBlackJack = false;
		if (this->_count == 21 && this->_cards.size() == 2) {
			this->_isBlackJack = true;
		}
	}

	void splitCheck() {
		this->_splitFlag = false;
		if (this->_cards.size() == 2 && this->_cards.front().getFace() == this->_cards.back().getFace())
			this->_splitFlag = true;
	}
		
	void doubleDownCheck() {
		this->_doubleFlag = false;
		if (this->_cards.size() == 2 && getCount() > 8 && getCount() < 12)
			this->_doubleFlag = true;
	}

public:

	void init() {
		this->_cards.clear();
		this->_stand = false;
	}

	void displayHand() {
		count();
		blackJackCheck();
		displayCards();
		displayCount();
	}

	void addCard(Card card) {
			this->_cards.push_back(card);
	}

	void stand() {
		this->_stand = true;
	}

	int getCount() {
		count();
		return this->_count;
	}

	list<Card>& getCards() {
		return this->_cards;
	}

	void setFlags() {
		doubleDownCheck();
		splitCheck();
	}

	bool isSoftHand() {
		return this->_isSoftHand;
	}

	bool isBlackJack() {
		return this->_isBlackJack;
	}

	bool getDoubleFlag() {
		return this->_doubleFlag;
	}
		
	bool getSplitFlag() {
		return this->_splitFlag;
	}
};
