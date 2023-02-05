#pragma once
#include "Card.h"
#include <time.h>
#include <list>
#include <stack>

class Shoe {

private:
	stack<Card> _shoe;
	list<Card> _temp;
	int _cutCard;
	bool _isLastHandBeforeReshuffle;

	void createCards();

	void shuffleAndStack();

	void insertCutCard();

	void emptyShoe();

public:

	Shoe();

	void createShoe();

	Card getCard();

	bool isLastHand() const;
};
