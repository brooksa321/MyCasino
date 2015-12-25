//BlackJack.h
//Declaration of the BlackJack class
//Programmer: Malcolm Milton
//Date: 5/5/15

#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Poker.h"

class BlackJack : public Poker //Inherits all public members from Poker class
{
	private:
		int initialBalance; //Int for the initial balance when starting one game
		int currentMoney; //Int for the current balance after playing a game
		int bet; //Int for how much money the user wants to bet each game
		int uSize; //Amount of cards the user has
		int dSize; //Amount of cards the dealer has
		int user; //Total of user's cards
		int dealer; //Total of dealer's cards
		bool revealed; //True if the dealer's second card is revealed
		bool insured; //True if the user buys insurance
		ACard dHand[10]; //An array of 10 cards for the hand of the user, all spots may not need to be used
		ACard uHand[10]; //An array of 10 cards for the hand of the dealer, all spots may not need to be used
	public:
		BlackJack(); //Class constructor
		int playBlackJack(int); //The function the goes through all the function calls for one whole game of black jack
		void resetGame(); //Function to give the user and dealer their cards
		void checkCards(); //Function that only prints the cards and their totals
		void uTotal(); //Function that finds out the total of the user's cards
		void dTotal(); //Function that finds out the total of the dealer's cards
		bool checkWin(bool); //Function that checks if the user has won, the parameter is true if the user doesn't want another card
		void dHit(); //Function that gives the dealer cards until they are over 16
		char afterGame(); //Function that tells the user about their money and 
		void hitOrStay(); //Function to ask the user if they want another card or not
		void insurance(); //Function that's called when the dealer's first card is an ace, asks user if they want insurrance
};

#endif
