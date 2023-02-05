#pragma once
#include "Player.h"
#include "Dealer.h"
#include "Shoe.h"
#include "GlobalVariables.h"
#include <windows.h>

class BlackJack {

private:
	Shoe _shoe;
	Dealer _dealer;
	Player _player;
	int _bet;
	int _originalBet;
	int _winnings;
	int _choice;
	bool _isPlayerTurn;
	bool _isSplitCase;
	int _handTurn;

public:

	BlackJack() {
		init();
	}

	void init() {
		this->_dealer.newHand();
		this->_player.newHand();
		this->_bet = 0;
		this->_originalBet = 0;
		this->_winnings = 0;
		this->_isPlayerTurn = false;
		this->_isSplitCase = false;
		this->_handTurn = 0;
	}

	void play(int deposit) {

		this->_player.setBankroll(deposit);

		while (1) {

			placeYourBet();
			deal();
			display();

			if (this->_player.getHand().isBlackJack()) {
				blackJackCaseLogic();
			}
			else {
				this->_isPlayerTurn = true;
				playerTurn();
			}
			
			init();
			Sleep(3500);
			clearConsole();
		}
	}

	void playerTurn(int n = 1) {

		while (this->_isPlayerTurn) {

			displayChoices();
			cin >> this->_choice;

			switch (this->_choice)
			{
			case 1:
				standCaseLogic(n);
				break;

			case 2:
				hitCaseLogic(n);
				break;

			case 4:
				if (!this->_player.getHand().getDoubleFlag() || this->_isSplitCase || this->_player.getBankroll() < this->_bet)
					cout << "Invalid choice.." << endl;
				else
					doubleCaseLogic();
				break;

			case 5:
				if (!this->_player.getHand().getSplitFlag() || this->_isSplitCase || this->_player.getBankroll() < this->_bet)
					cout << "Invalid choice.." << endl;
				else
					splitCaseLogic();
				break;

			default:
				cout << "Invalid choice.." << endl;
				break;
			}
		}
	}

	void dealerTurn() {

		this->_dealer.addHiddenCard();
		display();

		int limit = this->_dealer.getHand().isSoftHand() ? 18 : 17;

		while (this->_dealer.getHand().getCount() < limit) {
			this->_dealer.addCard(this->_shoe.getCard());
			Sleep(2000);
			display();
			limit = this->_dealer.getHand().isSoftHand() ? 18 : 17;
		}

		if (this->_dealer.getHand().isSoftHand()) {
			this->_dealer.getHand().stand();
			Sleep(1000);
			display();
		}
	}

	void blackJackCaseLogic() {

		this->_dealer.addHiddenCard();
		Sleep(3000);
		display();
		if (this->_isSplitCase)
			return;
		compare();
	}

	void standCaseLogic(int n = 1) {

		this->_isPlayerTurn = false;
		this->_player.getHand(n).stand();
		if(this->_isSplitCase)
			return;
		dealerTurn();
		compare();
	}

	void hitCaseLogic(int n = 1) {

		this->_player.addCard(this->_shoe.getCard(), n);
		display();

		int handCount = this->_player.getHand(n).getCount();

		if (handCount == 21) {

			this->_isPlayerTurn = false;

			if (this->_isSplitCase) {
				this->_player.getHand(n).stand();
				Sleep(2000);
				return;
			}

			Sleep(2000);
			standCaseLogic();
		}

		else if (handCount > 21) {

			this->_isPlayerTurn = false;

			if (this->_isSplitCase) {
				this->_bet -= this->_originalBet;
				Sleep(2000);
			}
			else {
				this->_dealer.addHiddenCard();
				Sleep(1500);
				display();
			}
		}
	}

	void doubleCaseLogic() {

		this->_player.setBankroll(this->_player.getBankroll() - this->_bet);
		this->_bet *= 2;
		this->_player.addCard(this->_shoe.getCard());

		display();
		Sleep(2000);
		standCaseLogic();
	}

	void splitCaseLogic() {

		this->_isSplitCase = true;

		// set bet
		this->_player.setBankroll(this->_player.getBankroll() - this->_bet);
		this->_bet *= 2;

		//split cards
		this->_player.splitCards(this->_shoe.getCard(), this->_shoe.getCard());
		this->_handTurn = 1;
		display();
		
		//first split turn
		if (this->_player.getHand().isBlackJack())
			Sleep(2000);
		else
			playerTurn();
		
		this->_isPlayerTurn = true;
		this->_handTurn = 2;
		display();

		//second split turn
		if (this->_player.getHand(2).isBlackJack())
			Sleep(2000);
		else
			playerTurn(2);

		this->_isPlayerTurn = false;

		// result
		if (this->_bet == 0)  // both busted
			return;

		this->_handTurn = 0;
		if (this->_player.getHand(1).isBlackJack() && this->_player.getHand(2).isBlackJack())
			blackJackCaseLogic();
		else
			dealerTurn();

		compare();
		compare(2);
		Sleep(2000);
	}

	void compare(int n = 1) {

		int dealerCount = this->_dealer.getHand().getCount();
		int playerCount = this->_player.getHand(n).getCount();

		if (this->_isSplitCase) {

			cout << " SPLIT " << n << ":";
			if (playerCount > 21) {
				cout << "  BUST" << endl;
				return;
			}
			if(this->_bet != this->_originalBet)
				this->_bet -= this->_originalBet;
		}

		if (this->_player.getHand(n).isBlackJack()) {

			if (this->_dealer.getHand().isBlackJack()) {
				this->_player.addWinnings(this->_bet);
				cout << "  PUSH...";
				cout << endl << endl;
			}
			else {
				this->_winnings += this->_bet * 1.5;
				this->_player.addWinnings(this->_winnings + this->_bet);
			}

		}
		else if (this->_dealer.getHand().isBlackJack())
			cout << "  DEALER WINS " << endl;
		else if (dealerCount > 21 || dealerCount < playerCount) {
			this->_winnings += this->_bet;
			this->_player.addWinnings(this->_winnings + this->_bet);
		}
		else if (dealerCount == playerCount) {
			this->_player.addWinnings(this->_bet);
			cout << "  PUSH...";
			cout << endl << endl;
		}
		else {
			cout << "  DEALER WINS " << endl;
		}

		if (this->_winnings > 0)
			cout << "  YOU WIN $" << this->_winnings << endl;

		this->_winnings = 0;
	}

	void display() {
		clearConsole();
		
		CARD_COUNTER.display();
		cout << endl;

		//bankroll
		cout << "          *BANKROLL: $" << this->_player.getBankroll() << "*";
		cout << endl << endl;

		//dealer hand
		cout << "DEALER CARDS:";
		cout << endl << endl << " ";
		this->_dealer.displayHand();
		cout << endl << endl;

		//rules
		cout << "          *DEALER MUST HIT SOFT 17*" << endl;
		cout << "          *BLACKJACK PAYS 3 TO 2*" << endl;
		cout << endl << endl << endl;

		//bet
		cout << "           YOUR BET: $" << this->_bet;
		cout << endl << endl;
		
		//player hand
		cout << "YOUR CARDS:";
		cout << endl << endl << " ";
		if (this->_handTurn == 1) 
			cout << "---> ";
		this->_player.displayHand();
		cout << endl << endl;

		if (this->_isSplitCase) {
			cout << " ";
			if (this->_handTurn == 2)
				cout << "---> ";
			this->_player.displayHand(2);
			cout << endl << endl;
		}
		cout << "---------------------------------------" << endl;
	}

	void deal() {
		this->_player.addCard(this->_shoe.getCard());
		this->_dealer.setHiddenCard(this->_shoe.getCard());
		this->_player.addCard(this->_shoe.getCard());
		this->_dealer.addCard(this->_shoe.getCard());
	}

	void placeYourBet() {

		if (this->_player.getBankroll() < 10) {
			cout << " Sorry, you don't have any remaining chip to play :(" << endl;
			Sleep(3000);
			exit(0);
		}

		if (this->_shoe.isLastHand()) {
			this->_shoe.createShoe();
		}

		CARD_COUNTER.display();
		cout << endl;
		cout << "          *BANKROLL: $" << this->_player.getBankroll() << "*";
		cout << endl << endl;
		cout << " PLACE YOUR BET: ";

		while (1) {

			cin >> this->_bet;
			if (this->_bet % 10 != 0 || this->_bet <= 0) {
				cout << " Please enter a bet which is a multiple of 10:" << endl;
				continue;
			}
			if (this->_bet > this->_player.getBankroll()) {
				cout << " Sorry, your bankroll is insufficient for this bet.." << endl;
				cout << " PLACE YOUR BET: ";
				continue;
			}
			this->_player.setBankroll(this->_player.getBankroll() - this->_bet);
			break;
		}

		this->_originalBet = this->_bet;
		clearConsole();
	}

	void displayChoices() {
		
		cout << " STAND? -> press 1" << endl;
		cout << " HIT? -> press 2" << endl;
		
		if (!this->_isSplitCase && this->_player.getBankroll() >= this->_bet) {

			this->_player.getHand().setFlags();

			if (this->_player.getHand().getDoubleFlag())
				cout << " DOUBLE DOWN? -> press 4" << endl;

			if (this->_player.getHand().getSplitFlag())
				cout << " SPLIT? -> press 5" << endl;
		}
	}

	void clearConsole() {
		system("cls");
	}
};
