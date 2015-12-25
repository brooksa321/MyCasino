//Card.h
//Declaration of the Card class
//Programmer: Malcolm Milton
//Date: 4/14/15

#ifndef CARD_H
#define CARD_H

const char spade = char(6); //Unicode UTF-8 (hex) code for a spade
const char club = char(5); //Unicode UTF-8 (hex) code for a club
const char heart = char(3); //Unicode UTF-8 (hex) code for a heart
const char diamond = char(4); //Unicode UTF-8 (hex) code for a diamond
const char design = char(254); //Unicode UTF-8 (hex) code for a star

struct ACard
{
	int num; //The number that will be on the card
	char pic; //The type of card (hearts, spades, diamonds, clubs)
};

class Card
{
	private:
		ACard Cards[52]; //Stack of 52 card structs
		int nextCard; //Int that keeps track of the next card in the deck
		void swap(int, int); //Utility function for shuffleCard(), swaps the ACards at the two paarameter indexes
		void outsideLine(); //Function to print the top or bottom line of a card
    void emptyLine(); //Function to print out the line that has no picture or number on a card
    void leftNumber(int, const char); //Function to print out the line of a non-royal card that has the number on the left side
    void rightNumber(int, const char); //Function to print out the line of a non-royal card that has the number on the right side
    void leftRoyal(int, const char); //Function to print out the line of a royal card that has the letter and picture on the left side
    void rightRoyal(int, const char pic); //Function to print out the line of a royal card that has the letter and picture on the right side
    void onePic(const char); //Function to print out the line of a card that has one picture
    void twoPic(const char); //Function to print out the line of a card that has two pictures
    void backLine(const char); //Function to print out one line of a card that is flipped over
	public:
		ACard flippedCard; //A card for printing out the back of a card for Black Jack
		Card(); //Class constructor. Initializes next card to 0, the deck, and flipped card
		void shuffleCard(); //Function to shuffle the cards in the deck
		ACard getCard(); //Function to return the next card in the deck
		void printCards(ACard[]); //Function that calls other functions to print out a card line by line
};

#endif
