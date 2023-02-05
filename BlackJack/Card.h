#pragma once
#include <iostream>
#include <string>

using namespace std;

class Card
{
	friend ostream& operator<<(ostream& cout, const Card& card) {
		cout << "[" << card._face << ", " << card._suit << "] ";
		return cout;
	}

private:
	const string _face;
	const string _suit;
	const int _value;

public:

	Card(string face, string suit, int value = NULL) : _face(face), _suit(suit), _value(value) {}

	Card(const Card& card) : _face(card._face), _suit(card._suit), _value(card._value) {}

	string getFace() const {
		return this->_face;
	}

	string getSuit() const {
		return this->_suit;
	}

	int getValue() const {
		return this->_value;
	}
};

