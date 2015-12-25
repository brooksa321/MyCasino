//Poker.cpp
//Definition of Poker member functions
//Programmer: Malcolm Milton
//Date: 4/28/15

#include <iostream>
#include "Poker.h"
using namespace std;

Poker::Poker() //Class constructor
{
	shuffleCard(); //Calls the function to shuffle the cards in the whole deck
	hand[5].num = -1; //The 6th card's number is set to 0 to tell the printing function to stop printing on one line
}

int Poker::playPoker(int money) //The function the goes through all the function calls for one whole game of poker
{
	char play = 'Y'; //Variable that keeps track of if the user wants to keep playing or quit
	int number; //Variable for saving the various money options for the user

	initialBalance = money; //Sets the initial balance for the first game to seedMoney
	currentBalance = money; //Sets the current balance for the first game to seedMoney

	cout << "WELCOME TO POKER AT MALCOLM'S CASINO!" << endl << endl;

	while(play != 'N' && play != 'n') //Stops looping when the user enters n or N to quit
	{
		cout << "HOW MUCH DO YOU WANT TO BET?" << endl << "$";
		cin >> number; //Saves how much the user wants to bet
		bet = errorCheckInts(0, currentBalance, number); //Makes sure the user entered a number between 0 and their current money
		currentBalance -= bet; //Subtracts the amount of money betted by the user from their balance
		cout << endl << "HERE'S YOUR HAND:" << endl << endl;
		newHand(); //Calls the function to give the user 5 new cards
		printCards(hand); //Calls the function to print the cards of the user's hand
		changeCards(); //Calls the function to ask the user if they want to change any of the cards from their hand
		cout << endl << "HERE'S YOUR NEW HAND:" << endl << endl;
		sortCards(hand, 5); //Calls the function to sort the cards for figuring out what the user won
		printCards(hand); //Calls the function to prin the new hand of the user
		winnings(); //Calls the function to figure out if the user's hand was a winner
		play = afterGame(); //Calls the function to ask if the user wants to play again and sets play to the answer
	}
	cout << endl << "THANK YOU FOR PLAYING POKER AT MALCOLM'S CASINO!" << endl;
	cout << "YOU CAME WITH $" << money << endl << "AND YOU ARE LEAVING WITH $" << currentBalance << endl;
	if(currentBalance < money)
		cout << "(SORRY FOR TAKING YOUR MONEY)" << endl;
	cout << endl;
	return currentBalance;
}

void Poker::changeCards() //Function for asking the user which cards they want to exchange from their hand
{
	int change; //Variable that saves user's answer to keep the card (1) or change the card (0)
	cout << "HOLD (1) OR REDRAW (0)?" << endl;
	for(int x=0; x<5; x++) //Loops through the cards in the user's hand
	{
		cout << hand[x].pic;
		cardInfo(hand[x]); //Calls the function to print the number or letter of the card
		cout << ": ";
		cin >> change; //Saves user's answer to change the card or not
		change = errorCheckInts(0, 1, change); //Calls the function to make sure the user entered a 1 or 0
		if(change == 0) //If the user wants to change the current card
			hand[x] = getCard(); //Calls the function from the Card class to change the current card with the next card in the deck
	}
}

void Poker::sortCards(ACard aHand[], int size) //Function for sorting the user's hand by number in ascending order
{
	for(int x=0; x<size; x++) //Starts at the first index and loops to the last index
		for(int y=x; y<=size-1; y++) //Satrts at the x index and loops to the last index
			if(aHand[y].num < aHand[x].num) //If the card at the y index is smaller than the card at the x index
				swaper(x, y, aHand); //Calls the function to swap the cards at the two indexes
	cout << endl;
}


void Poker::swaper(int x , int y, ACard aHand[]) //Utility function for sortCard() that swaps the position in the hand of the two parameter indexes
{
	ACard temp = aHand[x]; //Creates a card and makes its value the first parameter
	aHand[x] = aHand[y]; //Makes the first parameter index the second parameter index
	aHand[y] = temp; //Makes the second parameter index the previous first parameter index
}

void Poker::winnings() //Function for figuring out if the user's hand was a winning hand
{
	const int amount[9] = {10000, 1000, 20, 10, 8, 6, 4, 2, 1}; //Initializes an array for the winning amount of each winning hand
	bool win[9]; //An of bool where each index is a bool for a winning hand
	for(int x=0; x<9; x++) //Goes through the whole bool win array
		win[x] = false; //Sets each index to false

	
	for(int x=0; x<4; x++) //Starts at the first card and loops to the second to last card
	{
		//If the current card and next card numbers are the same and either Ace or royal
		if(hand[x].num == hand[x+1].num && (hand[x].num >10 || hand[x].num == 1))
			win[8] = true; //Index for a pair of jack or better is set to true
	}
	
	//If there are two pairs of cards that are the same number
	if((hand[0].num == hand[1].num && (hand[2].num == hand[3].num || hand[3].num == hand[4].num)) || (hand[1].num == hand[2].num && hand[3].num == hand[4].num))
		win[7] = true; //Index for a two pair winning hand is set to true

	for(int x=0; x<3; x++) //Starts at the first card and goes to the third card
	{
		if(hand[x].num == hand[x+1].num && hand[x].num == hand[x+2].num) //If three cards in a row have the same number
			win[6] = true; //Index for a triple is set to true
	}

	//For each card the difference of the card left and right is one
	if(hand[0].num+1 == hand[1].num && hand[0].num+2 == hand[2].num && hand[0].num+3 == hand[3].num && hand[0].num+4 == hand[4].num)
		win[5] = true; //Index for a straight hand is set to true

	//A straight hand where an Ace is the biggest value
	if(hand[0].num == 0 && hand[1].num == 10 && hand[2].num == 11 && hand[3].num == 12 && hand[4].num == 13)
		win[5] = true; //Index for a straight is set to true
	
	//Each card in the hand has the same picture value
	if(hand[0].pic == hand[1].pic && hand[0].pic == hand[2].pic && hand[0].pic == hand[3].pic && hand[0].pic == hand[4].pic)
		win[4] = true; //Index for a flush is set to true
	
	//A hand where there is one pair and one triple, the pair is not part of the triple
	if(win[6] && ((hand[0].num == hand[1].num && hand[1].num != hand[2].num) || (hand[4].num == hand[3].num && hand[3].num != hand[2].num)))
		win[3] = true; //Index for a full house hand is set to true

	for(int x=0; x<2; x++) //Loops from the first card to the second card
		if(hand[x].num == hand[x+1].num && hand[x].num == hand[x+2].num && hand[x].num == hand[x+3].num) //If there are four cards in a row with the same number
			win[2] = true; //Index for a four card hand is set to true

	if(win[5] && win[4]) //If the array indexes of a straight and a flush are true
		if(hand[0].num == 0 && hand[1].num == 10) //If the first card is an Ace and the second card is a 10, it is a royal straight flush
			win[0] = true; //Index for royal straight flush is set to true
		else //If it is not a royal straight flush
			win[1] = true; //Index for a straight flush is set to true

	bool won = false; //Variable for looping
	int index = 0; //Variable for looping through win array
	while(!won && index != 9) //Stops when the user has a winning hand or reached the last index and won nothing
	{
		if(win[index]) //If the current index in the array is true
		{
			currentBalance += bet; //Adds the bet amount of money back to the user's current money
			won = true; //Sets to true to stop looping
			message(index); //Calls the function to let the user know what winning hand they had
			if(index != 8) //If the user got a pair (index 8) then they only get their money back
			{
				bet *= amount[index]; //Multiplies the bet amount by the matching index of the winning hand
				cout << "YOU WIN $" << bet << "!" << endl << endl;
				currentBalance += bet; //Adds the winning amount of money to the user's current money
			}
		}
		index++; //Increases the looping variable
		if(index == 9 && win[8] == false) //If the user did not win anything
			cout << "OUCH, YOU LOSE. BETTER LUCK NEXT TIME" << endl << endl;
	}
}

void Poker::message(int index) //Function for telling the user if they had a winning hand
{
	//All numbers for the index are parallel to the indexes of the bool win[] array in the winnings() function
	if(index == 0)
		cout << "YOU GOT A ROYAL STRAIGHT FLUSH! CONGRATULATIONS!!!!!!!!" << endl;
	else if(index == 1)
		cout << "YOU GOT A STRAIGHT FLUSH!" << endl;
	else if(index == 2)
		cout << "YOU GOT FOUR OF A KIND!" << endl;
	else if(index == 3)
		cout << "YOU GOT A FULL HOUSE!" << endl;
	else if(index == 4)
		cout << "YOU GOT A FLUSH!" << endl;
	else if(index == 5)
		cout << "YOU GOT A STRAIGHT!" << endl;
	else if(index == 6)
		cout << "YOU GOT A TRIPLE!" << endl;
	else if(index == 7)
		cout << "YOU GOT A TWO PAIR!" << endl;
	else if(index == 8)
		cout << "YOU GOT A PAIR OF JACK OR BETTER! YOU GET YOUR MONEY BACK!" << endl;
}

char Poker::afterGame() //Function that tells the user about their money and asks if they wan to play again
{
	char answer; //Variable for saving if the user wants to play again or not
	cout << "YOUR INITIAL BALANCE WAS $" << initialBalance << endl;
	cout << "YOUR CURRENT BALANCE IS $" << currentBalance << endl;
	cout << "DO YOU WANT TO PLAY AGAIN? (Y/N)" << endl << "> ";
	cin >> answer; //Saves user's answer
        answer = errorCheckChar(answer); //Makes sure the user answered with either y or n
	return answer; //Returns the user's answer
}

void Poker::cardInfo(ACard tempCard) //Function for changeCards() that prints out the number or letter of the card
{
	if(tempCard.num > 1 && tempCard.num < 11) //If the number of the card is 2-10
		cout << tempCard.num;
	else if(tempCard.num == 1) //If the number of the card is 1 then it's an ace
		cout << "A";
	else if(tempCard.num == 11) //If the number of the card is 11 then it's a Jack
		cout << "J";
	else if(tempCard.num == 12) //If the number of the card is 12 then it's an Queen
		cout << "Q";
	else if(tempCard.num == 13) //If the number of the card is 13 then it's an King
		cout << "K";
}

void Poker::newHand() //Function for switching all cards in user's hand for next game
{
	for(int x=0; x<5; x++) //Loops 5 times to give the user 5 ACards in the hand array
		hand[x] = getCard(); //Calls the function to get the next ACard in the deck and set the current hand index to it
}

int Poker::errorCheckInts(int min, int max, int choice) //Function for checking if the user's input (choice) is between max and min, returns the correct number
{
	while(choice < min || choice > max) //If the user's input was less than the min or more than the max
	{
		cout << "PLEASE CHOOSE A VALID CHOICE: ";
		cin >> choice; //Saves user's answer
	}
	return choice; //Returns user's correct answer
}

int Poker::errorCheckInt(int choice) //Function for checking user input of an integer
{
	while(choice <= 0) //If the user's input was less than or equal to 0
	{
	        cout << "PLEASE CHOOSE A VALID CHOICE: ";
	        cin >> choice; //Saves user's answer
	}
	return choice; //Returns user's correct answer
}

char Poker::errorCheckChar(char choice) //Function for checking user input of a character
{
	while(choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n') //If the user's input was not y, Y, n, or N
	{
		cout << "PLEASE CHOOSE A VALID CHOICE (Y/N): ";
		cin >> choice; //Saves user's answer
	}
	return choice; //Returns user's correct answer
}
