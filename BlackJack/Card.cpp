#include "Card.h"

ostream& operator<<(ostream& cout, const Card& card) {
	cout << "[" << card._face << ", " << card._suit << "] ";
	return cout;
}

Card::Card(string face, string suit, int value) : _face(face), _suit(suit), _value(value){}

Card::Card(const Card& card) : _face(card._face), _suit(card._suit), _value(card._value) {}

string Card::getFace() const {
	return this->_face;
}

string Card::getSuit() const {
	return this->_suit;
}

int Card::getValue() const {
	return this->_value;
}