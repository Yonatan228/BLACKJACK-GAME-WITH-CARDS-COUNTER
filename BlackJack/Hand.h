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

	void count();

	void softHandLogic();

	void displayCount();

	void displayCards();

	void blackJackCheck();

	void splitCheck();
		
	void doubleDownCheck();

public:

	void init();

	void displayHand();

	void addCard(Card card);

	void stand();

	int getCount();

	list<Card>& getCards();

	void setFlags();

	bool isSoftHand() const;

	bool isBlackJack() const;

	bool getDoubleFlag() const;
		
	bool getSplitFlag() const;
};
