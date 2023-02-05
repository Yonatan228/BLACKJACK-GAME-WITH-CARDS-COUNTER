#include "Hand.h"

void Hand::count() {
	this->_count = 0;
	this->_isSoftHand = false;
	for (it = this->_cards.begin(); it != this->_cards.end(); it++) {
		this->_count += it->getValue();
		softHandLogic();
	}
	if (_isBlackJack)
		this->_isSoftHand = false;
}

void Hand::softHandLogic() {
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

void Hand::displayCount() {
	if (this->_isBlackJack)
		cout << "-> BLACKJACK";
	else if (this->_count > 21)
		cout << "-> BUST";
	else {
		if (this->_cards.size() == 1) // if hidden card
			cout << "[XXXXXXX]";
		cout << " -> count: " << this->_count;
		if (this->_isSoftHand && !this->_stand)
			cout << "/ " << this->_count - 10;
	}
}

void Hand::displayCards() {
	for (it = this->_cards.begin(); it != this->_cards.end(); it++)
		cout << *it;
}

void Hand::blackJackCheck() {
	this->_isBlackJack = false;
	if (this->_count == 21 && this->_cards.size() == 2) {
		this->_isBlackJack = true;
	}
}

void Hand::splitCheck() {
	this->_splitFlag = false;
	if (this->_cards.size() == 2 && this->_cards.front().getFace() == this->_cards.back().getFace())
		this->_splitFlag = true;
}

void Hand::doubleDownCheck() {
	this->_doubleFlag = false;
	if (this->_cards.size() == 2 && getCount() > 8 && getCount() < 12)
		this->_doubleFlag = true;
}

void Hand::init() {
	this->_cards.clear();
	this->_stand = false;
}

void Hand::displayHand() {
	count();
	blackJackCheck();
	displayCards();
	displayCount();
}

void Hand::addCard(Card card) {
	this->_cards.push_back(card);
}

void Hand::stand() {
	this->_stand = true;
}

int Hand::getCount() {
	count();
	return this->_count;
}

list<Card>& Hand::getCards() {
	return this->_cards;
}

void Hand::setFlags() {
	doubleDownCheck();
	splitCheck();
}

bool Hand::isSoftHand() const {
	return this->_isSoftHand;
}

bool Hand::isBlackJack() const {
	return this->_isBlackJack;
}

bool Hand::getDoubleFlag() const {
	return this->_doubleFlag;
}

bool Hand::getSplitFlag() const {
	return this->_splitFlag;
}