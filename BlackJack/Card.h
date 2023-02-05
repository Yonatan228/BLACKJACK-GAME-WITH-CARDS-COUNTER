#pragma once
#include <iostream>
#include <string>

using namespace std;

class Card
{
	friend ostream& operator<<(ostream& cout, const Card& card);

private:
	const string _face;
	const string _suit;
	const int _value;

public:

	Card(string face, string suit, int value = NULL);

	Card(const Card& card);

	string getFace() const;

	string getSuit() const;

	int getValue() const;
};

