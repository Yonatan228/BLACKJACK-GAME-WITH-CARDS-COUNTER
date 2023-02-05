#pragma once
#include "Shoe.h"
#include "GlobalVariables.h"

void Shoe::createCards() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < N_OF_CARDS / 4; j++) {
			this->_temp.push_back(Card(FACES[j % 13], SUITS[i], FACE_TO_VALUES.at(FACES[j % 13])));
		}
	}
}

void Shoe::shuffleAndStack() {
	list<Card>::iterator it = this->_temp.begin();
	srand((unsigned int)time(NULL));

	//shuffle and push to stack
	for (int i = N_OF_CARDS; i > 0; i--) {
		advance(it, rand() % i);
		this->_shoe.push(*it);
		this->_temp.erase(it);
		it = this->_temp.begin();
	}
}

void Shoe::insertCutCard() {
	int offset = (int)N_OF_CARDS / 4;
	int range = (int)(N_OF_CARDS / 3.33) - offset + 1;
	this->_cutCard = offset + (rand() % range);
}

void Shoe::emptyShoe() {
	while (!this->_shoe.empty())
		this->_shoe.pop();
}

Shoe::Shoe() {
	createShoe();
}

void Shoe::createShoe() {
	this->_isLastHandBeforeReshuffle = false;
	NEW_SHOE = true;
	emptyShoe();
	createCards();
	shuffleAndStack();
	insertCutCard();
	DECKS_REMAINING = N_OF_DECKS;
}

Card Shoe::getCard() {
	if (this->_shoe.size() == this->_cutCard) {
		this->_isLastHandBeforeReshuffle = true;
	}
	Card card = this->_shoe.top();
	this->_shoe.pop();
	DECKS_REMAINING = (int)round(this->_shoe.size() / 52.0);
	return card;
}

bool Shoe::isLastHand() const{
	return this->_isLastHandBeforeReshuffle;
}