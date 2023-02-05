#pragma once
#include "Card.h"


class CardCounter {

private:
	int _count;

public:
	void display();

	void addToCount(Card& card);

	int getTrueCount();
};
