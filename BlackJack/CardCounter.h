#pragma once
#include "Card.h"
#include "GlobalVariables.h"

class CardCounter {

private:
	int _count;

public:

	void display() {
		cout << "---------------------------------------" << endl;
		if (NEW_SHOE) {
			cout << "            ***NEW SHOE***" << endl;
			NEW_SHOE = false;
			this->_count = 0;
		}
		string plusSign = this->_count > 0 ? "+" : "";
		cout << "            COUNT: " << plusSign << this->_count << endl;
		cout << "            DECKS REMAINING: ~" << DECKS_REMAINING << endl;
		plusSign = getTrueCount() > 0 ? "+" : "";
		cout << "            TRUE COUNT: " << plusSign << getTrueCount() << endl;
		cout << "---------------------------------------";
	}

	void addToCount(Card& card) {
		int value = card.getValue();
		if (value <= 6)
			this->_count += 1;
		else if(value >= 10)
			this->_count -= 1;
	}

	int getTrueCount() {
		if (DECKS_REMAINING <= 1)
			return this->_count;
		return round((float)(this->_count / DECKS_REMAINING));
	}
};
