//Poker.h
//Declaration of Poker class
//Programmer: Malcolm Milton
//Date: 4/28/15

#ifndef POKER_H
#define POKER_H
#include "Card.h"

class Poker: public Card //Inherits all public members from Card class
{
	private:
		int seedMoney; //Int for the overall amount of money the user started with
		int initialBalance; //Int for the initial balance when starting one game
		int currentBalance; //Int for the current balance after playing a game
		int bet; //Int for how much money the user wants to bet each game
		ACard hand[6]; //An array of 6 cards for the hand of the user, the last card is used for stoping the printing function
	public:
		Poker(); //Calss constructor
		int playPoker(int); //The function the goes through all the function calls for one whole game of poker
		void changeCards(); //Function for asking the user which cards they want to exchange from their hand
		void sortCards(ACard[], int); //Function for sorting the user's hand by number in ascending order
		void swaper(int, int, ACard[]); //Utility function for sortCard() that swaps the position in the hand of the two parameter indexes
		void winnings(); //Function for figuring out if the user's hand was a winning hand
		void message(int); //Function for telling the user if they had a winning hand
		virtual char afterGame(); //Function that tells the user about their money and asks if they wan to play again
		void cardInfo(ACard); //Function for changeCards() that prints out the number or letter of the card 
		void newHand(); //Function for switching all cards in user's hand for next game
		int errorCheckInts(int, int, int); //Function for checking user input of an integer
		int errorCheckInt(int); //Function for checking user input of an integer
		char errorCheckChar(char); //Function for checking user input of a character
};

#endif
