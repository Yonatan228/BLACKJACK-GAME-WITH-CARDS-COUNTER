#include "Dealer.h"
#include "GlobalVariables.h"

Dealer::Dealer() {
	this->_hiddenCard = NULL;
}

void Dealer::displayHand() {
	this->_hand.displayHand();
}

void Dealer::addCard(Card card) {
	CARD_COUNTER.addToCount(card);
	this->_hand.addCard(card);
}

void Dealer::addHiddenCard() {
	CARD_COUNTER.addToCount(*this->_hiddenCard);
	this->_hand.addCard(*this->_hiddenCard);
}

void Dealer::setHiddenCard(Card card) {
	this->_hiddenCard = new Card(card);
}

Hand& Dealer::getHand() {
	return this->_hand;
}

void Dealer::newHand() {
	this->_hand.init();
	this->_hiddenCard = NULL;
}