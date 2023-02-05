#pragma once
#include <string>
#include <map>

using namespace std;

const int N_OF_DECKS = 7;
const int N_OF_CARDS = N_OF_DECKS * 52; 

bool NEW_SHOE; // for card counting
int DECKS_REMAINING; // for card counting

const string FACES[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

const string SUITS[] = { "Spade", "Club", "Diamond", "Heart" };

const map<string, int> FACE_TO_VALUES = { {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
	{"10", 10}, {"Jack", 10}, {"Queen", 10}, {"King", 10}, {"Ace", 11} };

#include "CardCounter.h"
CardCounter CARD_COUNTER;
