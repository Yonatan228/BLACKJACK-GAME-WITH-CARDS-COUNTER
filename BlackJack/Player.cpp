#include "Player.h"
#include "GlobalVariables.h"

Player::Player() {
	this->_bankroll = 0;
}

void Player::displayHand(int n) {
	if (n == 1)
		this->_hand.displayHand();
	else
		this->_hand2.displayHand();
}

void Player::addCard(Card card, int n) {
	CARD_COUNTER.addToCount(card);
	if (n == 1)
		this->_hand.addCard(card);
	else
		this->_hand2.addCard(card);
}

void Player::splitCards(Card card1, Card card2) {
	this->_hand2.addCard(this->_hand.getCards().back());
	this->_hand.getCards().pop_back();
	addCard(card1);
	addCard(card2, 2);
}

void Player::addWinnings(int amount) {
	this->_bankroll += amount;
}

Hand& Player::getHand(int n) {
	if (n == 1)
		return this->_hand;
	else
		return this->_hand2;
}

void Player::newHand() {
	this->_hand.init();
	this->_hand2.init();
}

void Player::setBankroll(int n) {
	this->_bankroll = n;
}

int Player::getBankroll() const {
	return this->_bankroll;
}