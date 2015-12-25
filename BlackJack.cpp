//BlackJack.cpp
//Definition of BalckJack member functions
//Programmer: Malcolm Milton
//Date: 5/5/15

#include <iostream>
#include "BlackJack.h"
using namespace std;

BlackJack::BlackJack() //Class constructor
{
	shuffleCard(); //Calls the Card class function to shuffle the deck of cards
}

int BlackJack::playBlackJack(int seedMoney) //Called from main function to continuously play, returns the user's current balance, parameter: user's money before game
{
	char play = 'Y'; //Looping variable that is n or N when the user wants to stop playing
	initialBalance = seedMoney; //Variable that is the user's money before each game, sets it equal to the starting money
	currentMoney = seedMoney; //Variable that is the user's money after the game, sets it equal to the starting money
	cout << "WELCOME TO BLACK JACK AT MALCOLM'S CASINO!" << endl;
	cout << endl;

	while(play != 'N' && play != 'n') //While the user still wants to play
	{
		cout << "HOW MUCH DO YOU WANT TO BET?" << endl << "$";
		cin >> bet;
		bet = errorCheckInts(0, currentMoney, bet); //Calls the Poker class function to check if the user entered a number less than 0 or more than thier money
		currentMoney -= bet; //Subracts the bet from the user's money
		resetGame(); //Calls the function that resets the game and plays it
		play = afterGame(); //Calls function to ask user if they want to play again and saves answer
	}
	cout << "THANK YOU FOR PLAYING BLACKJACK AT MALCOLM'S CASINO!" << endl;
	cout << "YOU CAME WITH $" << seedMoney << " AND YOU ARE LEAVING WITH $" << currentMoney << endl;
	if(currentMoney < seedMoney) //If the user lost money playing black jack
		cout << "(SORRY WE TOOK YOUR MONEY)" << endl;;
	cout << endl;
	return currentMoney; //Returns the user's money
}

void BlackJack::resetGame() //Function to give the user and dealer their cards, then calls checkCards() to play game
{
	dealer = 0; //Sets dealer's card total to 0
	user = 0; //Sets user's card total to 0
	revealed = false; //Sets variable that says if the dealer has revealed their hidden card yet
	insured = false; //Sets the variable that says if the user buys insurance to false
	uSize = 2; //Sets the amount of cards the user has to 2
	dSize = 1; //Sets the amount of cards the dealer has to 1
	uHand[0] = getCard(); //Gives the user 1 card from Card class deck
	uHand[1] = getCard(); //Gives the user 1 card from Card class deck
	uHand[2].num = -1; //Sets the 3rd card's number in the array to -1 for card printing purposes
	dHand[0] = getCard(); //Gives the dealer 1 card from the Card class deck
	dHand[1] = flippedCard; //Makes the 2nd card a flippedCard to give illusion of a hidden card
	dHand[2].num = -1; //Sets the 3rd card's number in the array to -1 for card printing purposes
	dHand[3] = getCard(); //Makes the 4th card in the array the card that is technically the dealer's 2nd card, but we can't show the user
	
	checkCards(); //Calls the function to prins out the cards and their totals
	insurance(); //Calls the function to see if user has 21, or dealer has an ace
}

void BlackJack::insurance() //Only called if the dealer's first hand is an ace
{
	char x; //Variable to save if user wants to buy insurance or not
	bool won; //Will be true if the user or the dealer wins the game

	if(user == 21) //If the user's cards add up to 21
		won = checkWin(false); //The function will return true for 'won' to be true
	else if(dealer == 11) //If the dealer's first card is an ace
	{
		cout << "UH OH, THE DEALER HAS AN ACE" << endl << "WOULD YOU LIKE TO BUY INSURRANCE? (Y/N)" << endl << "> ";
		cin >> x;
		cout << endl;
		x = errorCheckChar(x); //Calls the function to make sure the user enters a Y, y, N, or n

		if((x=='y' || x=='Y') && ((bet/2) > currentMoney)) //If the user wants insurance but they cannot afford it (insurance costs half of bet)
			cout << "SORRY YOU CANNOT AFFORD INSURANCE" << endl << endl;
		else if(x=='y' || x=='Y') //If the user wants insurance and they can afford it
		{
			currentMoney -= (bet/2); //Insurance costs half of the bet
			insured = true; //Makes 'insured' true to indicate that the user has bought insurance
			cout << "YOU ARE NOW INSURED" << endl << endl;
			if(dHand[3].num >= 10) //If the dealers second card's total is 10 (royal cards are worth 10)
			{
				dHand[1] = dHand[3]; //Switches the flipped card and the dealer's real second card
				dSize++; //Increments the size of the dealer's hand
				checkCards(); //Calls the function to print out the cards and totals
				won = checkWin(false); //Function will tell user the dealer won and return true since the dealer has 21
			}
		}
		else //If the user doesn't want insurance
			won = checkWin(false); //Function will return false for 'won' to be false since user and dealer do not have 21 right away
	}
	else //If the user's total isn't 21 and the dealer's first card is not an ace
		won = checkWin(false); //Function will return false for 'won' to be false

	if(!won) //If the user nor dealer won the game yet
		hitOrStay(); //Calls the function to ask the user if they want another card
}

void BlackJack::checkCards() //Adds up the total of the user and dealer's hands, then calls the checkWin function to see if any one won
{
	sortCards(uHand, uSize); //Sorts the dealer's cards for figuring out if an ace should be 1 or 11	
	cout << "HERE'S YOUR HAND:" << endl;
	printCards(uHand); //Calls the Card class function to print out the user's hand
        cout << "HERE'S THE DEALER'S HAND:" << endl;
	printCards(dHand); //Calls the Card class function to print out the dealer's hand
	
	uTotal(); //Function will add up the cards of the user's hand
	dTotal(); //Function will add up the cards of the dealer's hand
	cout << "USER: " << user << " DEALER: " << dealer << endl << endl;
}

void BlackJack::uTotal()
{
	user = 0; //Makes the total of the user's hand 0 to calculate the total again
	sortCards(uHand, uSize); //Sorts the dealer's cards for figuring out if an ace should be 1 or 11
	for(int x=uSize-1; x>=0; x--) //Starts at the user's last card and decrements to the first card
        {
                if(uHand[x].num == 1) //If the current card is an ace
                {
                        if(x > 0 && user > 9) //If the current card is not the first card in the array and the current card total is over 9
                                user += 1; //Makes the ace amount to 1 and adds it to the user's card total
                        else if(x > 0 && user <= 9) //If the current card is not the first card in the array and the current card total is under 10
                                user += 11; //Makes the ace amount to 11 and adds it to the user's card total
                        else if(user >= 11) //If the current card is the first card in the array and the current card total is over 10
                                user += 1; //Makes the ace amount to 1 and adds it to the user's card total
                        else //If the current card is the first card in the array and the current card total is under 11
                                user += 11; //Makes the ace amount to 11 and adds it to the user's card total
                }
                else if(uHand[x].num >= 10) //If the current card is a 10 or a royal card
                        user += 10; //Adds 10 to the user's card total (royal cards count as 10)
                else //If the current card is neither an ace, 10, or royal card
                        user += uHand[x].num; //Adds the card's number to the user's card total
        }
}

void BlackJack::dTotal()
{
	dealer = 0; //Makes the total of the dealer's hand 0 to calculate the total again
	sortCards(dHand, dSize); //Sorts the user's cards for figuring out if an ace should be 1 or 11
	for(int x=dSize-1; x>=0; x--) //Starts at the user's last card and decrements to the first card
        {
                if(dHand[x].num == 1) //If the current card is an ace
                {
                        if(x > 0 && dealer > 9) //If the current card is not the first card in the array and the current card total is over 9
                                dealer += 1; //Makes the ace amount to 1 and adds it to the user's card total
                        else if(x > 0 && dealer <= 9) //If the current card is not the first card in the array and the current card total is under 10
                                dealer += 11; //Makes the ace amount to 11 and adds it to the user's card total
                        else if(dealer >= 11) //If the current card is the first card in the array and the current card total is over 10
                                dealer += 1; //Makes the ace amount to 1 and adds it to the user's card total
                        else //If the current card is the first card in the array and the current card total is under 11
                                dealer += 11; //Makes the ace amount to 11 and adds it to the user's card total
                }
                else if(dHand[x].num >= 10) //If the current card is a 10 or a royal card
                        dealer += 10; //Adds 10 to the user's card total (royal cards count as 10)
                else //If the current card is neither an ace, 10, or royal card
                        dealer += dHand[x].num; //Adds the card's number to the user's card total
        }
}

bool BlackJack::checkWin(bool end) //Function to check if anyone has won the game, Parameter is true if the user has decided to not add more cards and firces the game to make a decision
{
	bool won = true; //Will indicate if the user or dealer has won the game

	if(dealer > 21 && user > 21) //If the dealer and user are both over 21, the user loses
		cout << "YOU AND THE DEALER ARE BOTH OVER 21, YOU LOSE" << endl << endl;
	else if(dealer > 21 && user <= 20) //If the dealer is over 21 but the user is not, the user wins
	{
		cout << "THE DEALER IS OVER 21, YOU WIN!" << endl << endl;
		currentMoney += (bet*2); //Gives the user thier winning money
	}
	else if(user > 21 && dealer <= 21) //If the user is over 21 and the dealer is under or equal to 21, the user loses
		cout << "YOU ARE OVER 21, YOU LOSE" << endl << endl;
	else if(user==21 && dealer==21) //If the user and dealer both have 21, the user ties
	{
		cout << "YOU AND THE DEALER BOTH HAVE 21! YOU GET YOUR MONEY BACK!" << endl << endl;
		currentMoney += bet; //Gives the user their money back
	}
	else if(user==21 && dealer < 21) //If the user gets 21 and the dealer does not, the user wins
	{
		cout << "YOU HAVE 21! YOU WIN!" << endl << endl;
		currentMoney += (bet*2.5); //Gives the user their winning money
	}
	else if(user < 21 && dealer == 21) //If the user is under 21 and the dealer has 21, the user loses
	{
		if(insured) //If the dealer's first card was an ace and the user bought insurance
		{
			cout << "THE DEALER GOT 21 BUT YOU ARE INSURED SO YOU GET ALL YOU MONEY BACK!" << endl << endl;
			currentMoney += bet; //Gives the user their money back
		}
		else //If the user did not buy insurance or didn't have the option to buy insurance
			cout << "THE DEALER GOT 21, YOU LOSE" << endl << endl;
	}
	else if(end == true) //If the user and dealer are both under 21 and the user does not want any more cards, this function will be called with "end" being true
	{
		if(user == dealer) //If the user's and dealer's cards are both equal, the user ties
		{
			cout << "YOU TIED WITH THE DEALER, YOU GET YOUR MONEY BACK" << endl << endl;
			currentMoney += bet; //Gives the user thier money back
		}
		else if(user < dealer) //If the user's total is less than the dealer's total, the user loses
			cout << "YOU GOT LESS THAN THE DEALER, YOU LOSE" << endl << endl;
		else //If the user's total is more than the dealer's total, the user wins
		{
			cout << "YOU GOT MORE THAN THE DEALER! YOU WIN!" << endl << endl;
			currentMoney += (bet*2); //Gives the user thier winning money
		}
	}
	else //If nobody wins
		won = false; //Indicates that nobody has won the game
	return won;
}

void BlackJack::dHit() //Function that gives the dealer cards until they are over 16
{
	while(dealer < 17) //While the dealer's total is less than 17
	{
		dHand[dSize] = getCard(); //Gives the dealer a new card from the deck
		dHand[dSize+1].num = -1; //Makes the next card's number in the array -1 for printing purposes
		dSize++; //Increases the number of cards the user has
		dTotal(); //Calls the function to add up the dealer's cards
	}
}

void BlackJack::hitOrStay() //Function for asking the user if they want another card
{
	char hit; //Will save the user's answer
	bool won = false; //Will indicate if anyone has won the game

	cout << "DO YOU WANT ANOTHER CARD? (Y/N)" << endl << "> ";
	cin >> hit;
	hit = errorCheckChar(hit); //Makes sure the user answered with a Y, N, y, or n

	while(hit != 'N' && hit != 'n') //While the user wants another card
	{
		uHand[uSize] = getCard(); //Gives the user another card from the deck
		uHand[uSize+1].num = -1; //Makes the next card's number in the array for printing purposes
		uSize++; //Increments the number of cards the user has
		checkCards(); //Calls the checkCards() function to print out the cards and see if anyone won
		won = checkWin(false); //Checks to see if anyone won the game and saves the answer
		
		if(!won) //If nobody won the game yet
		{
			cout << "DO YOU WANT ANOTHER CARD? (Y/N)" << endl << "> ";
			cin >> hit;
			hit = errorCheckChar(hit); //Makes sure the user answered with a Y, N, y, or n
		}
		else //If someone has won the game already
			hit = 'N'; //Sets to 'N' to stop from looping
	}

	if(!won) //If nobody won the game
	{
		dHand[1] = dHand[3]; //Switches the flipped card and the dealer's real second card
		dSize++; //Increments the size of the dealer's hand
		dTotal(); //Calls the function to add up the total of the dealer's hand
		dHit(); //Calls the function to give the dealer cards until they are over 16
		checkCards(); //Calls the function to print out the cards and the totals
		checkWin(true); //Calls the function to force the game to end and see who won
	}
}

char BlackJack::afterGame()
{
	char answer; //Variable for saving if the user wants to play again or not
        cout << "YOUR INITIAL BALANCE WAS $" << initialBalance << endl;
        cout << "YOUR CURRENT BALANCE IS $" << currentMoney << endl;
	initialBalance = currentMoney; //Makes the initial balance for the next game the current balance now
        cout << "DO YOU WANT TO PLAY AGAIN? (Y/N)" << endl << "> ";
        cin >> answer; //Saves user's answer
        answer = errorCheckChar(answer); //Makes sure the user answered with either y or n
	cout << endl;
        return answer; //Returns the user's answer
}
