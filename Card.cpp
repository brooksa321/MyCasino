//Card.cpp
//Definition of Card class members
//Programmer: Malcolm Milton
//Date: 4/14/15

#include "Card.h"
#include <stdlib.h> //srand, rand
#include <time.h>
#include <iostream>
#include <cstdio> //for colors
#include <cstring> //for comparing cstrings
#include <windows.h>   // WinApi header

using namespace std;

Card::Card() //Class constructor
{
	nextCard = 0;

	for(int x = 0; x < 52; x++) //Starts at the index of the first card and stops at the last card
	{
		Cards[x].num = (x%13)+1; //Sets the number of the current card to a number 1-13

		if(x < 13) //If the card is in the first set of 13 cards
			Cards[x].pic = (char)spade;//Sets the picture of the card to a spade
		else if(x >= 13 && x < 26) //If the card is in the second set of 13 cards
			Cards[x].pic = (char)club;//Sets the picture of the card to a club
		else if(x >= 26 && x < 39) //If the card is in the third set of 13 cards
			Cards[x].pic = (char)heart; //Sets the picture of the card to a heart
		else if(x >= 39) //If the card is in the last set of 13 cards
			Cards[x].pic = (char)diamond; //Sets the picture of the card to a diamond
	}
	
	flippedCard.num = 14; //Initializes the number of a flipped card to 14
	flippedCard.pic = design; //Initializes the pic of a flipped card to a star
}

void Card::swap(int x, int y) //Function for shuffling. Switches the cards in the array of the two parameter indexes
{
	ACard temp = Cards[x]; //Creates a card and makes its value the first parameter
	Cards[x] = Cards[y]; //Makes the first parameter index the second parameter index
	Cards[y] = temp; //Makes the second parameter index the previous first parameter index
}

void Card::shuffleCard() //Function to shuffle the cards in the deck
{
	int rnum; //Variable to be used for saving a random number between 0 and 51
	srand(time(NULL)); //Sets the seed for random numbers

	for(int x=0; x<52; x++) //Loops through all of the cards in the array
	{
		rnum = rand()%51; //Sets the variable to a random number between 0 and 51
		swap(x, rnum); //Calls the function to switch the two cards in the array of the current index and the random index
	}
	nextCard = 0; //Makes the next card the first card in the array
}

ACard Card::getCard() //Function to return the next card in the array
{
	if(nextCard == 46)
		shuffleCard();
	return Cards[nextCard++]; //Returns the next card in the deck and incriments nextCard after
}

void Card::printCards(ACard hand[]) //Function to print out the cards on the same line. Parameters: start is the starting index in the array, numCards is the number of cards to print out
{
	int index = 0;
	ACard tempCard = hand[index]; //Makes a new ACard structure and sets it equal to the first card to print out

	HANDLE  hConsole;/////////////////////////////
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);///////////////////////////////////////////////

	for(int line=1; line<=9; line++) //Starts at the first line of the cards to print out and loops to the last line
	{
		cout << "  ";
		while(tempCard.num != -1) //Starts at the first card to print out and loops to the last card to print out
		{
			if (tempCard.pic == (char)spade || tempCard.pic == (char)club) //If the picture is a spade or a club
				SetConsoleTextAttribute(hConsole, 240);//////////////////////////printf("%c[%dm", 0x1B, 30); //Sets the foreground color to black
			else //If the picture is a heart or diamond
				SetConsoleTextAttribute(hConsole, 252);//////////////////////////////////printf("%c[%dm", 0x1B, 31); //Sets the foreground color to red
			/////////////////////////printf("%c[%dm", 0x1B, 47); //Sets the background of the line to white

			if(tempCard.num == 14) //If the current card is a flipped card
			{
				SetConsoleTextAttribute(hConsole, 207);
/*
				printf("%c[%dm", 0x1B, 37); //Sets the foreground color back to white
				printf("%c[%dm", 0x1B, 41); //Sets the background of the line to red
*/
				backLine(tempCard.pic); //Calls the function to print out a line of a flipped card
			}
			else if(line == 1) //If the current line to print out is the second line
			{
				if(tempCard.num < 11) //All cards that are not royal cards have the same format for this line
					leftNumber(tempCard.num, tempCard.pic); //Calls the function to print out the line that specifies the number of the card
				else //If the card is a royal card (Jack, Queen, King)
					leftRoyal(tempCard.num, tempCard.pic); //Calls the function to print out the line that specifies both the value and picture of the current card
			}
			else if(line == 2 || line == 8) //All cards have the same respective format for lines 3 and 9
			{
				if(tempCard.num < 11 && tempCard.num > 3) //Cards from 4 to 10 have the same lines 3 and 9
					twoPic(tempCard.pic); //Calls the function to print out a line with 2 pictures
				else if(tempCard.num == 3) //The 3 card has the same format for lines 3 and 9
					onePic(tempCard.pic); //Calls the function to print out a line with 1 picture
				else //The rest of the cards have an empty line for lines 3 and 9
					emptyLine(); //Calls the function to print out a line with no pictures or numbers
			}
			else if(line == 3 && (tempCard.num == 2 || (tempCard.num > 6 && tempCard.num < 11))) //Line 4 has 1 picture for cards 2 and 7-10, empty for all other cards
				onePic(tempCard.pic); //Calls the function to print out a line with 1 picture
			else if((line == 4 || line == 6) && (tempCard.num == 9 || tempCard.num == 10)) //Lines 5 and 7 have 1 picture for cards 9 and 10, empty for all others
				twoPic(tempCard.pic); //Calls the function to print out a line with 2 pictures
			else if(line == 5) //If the current line to print out is the sixth
			{
				if(tempCard.num > 5 && tempCard.num < 9) //Cards 6-8 have the same format for line 6
					twoPic(tempCard.pic); //Calls the function to print out a line with 2 pictures
				else if(tempCard.num < 6 && tempCard.num%2 == 1) //Odd numbered cards that are less than 6 (A, 3, and 5) have the same format for line 6
					onePic(tempCard.pic); //Calls the function to print out a line with 1 picture
				else //All other cards have an empty line for line 6
					emptyLine();
			}
			else if(line == 7 && (tempCard.num == 2 || tempCard.num == 8 || tempCard.num == 10)) //Cards 2, 8, and 10 have one picture for line 8, all others have an empty line
				onePic(tempCard.pic); //Calls the function to print out a line with 1 picture
			else if(line == 9) //If the current line to print out is the tenth
			{
				if(tempCard.num < 11) //All cards that are not royal cards have the same format for this line
					rightNumber(tempCard.num, tempCard.pic); //Calls the function to print out the line that specifies the number of the card
				else //If the card is a royal card (Jack, Queen, King)
					rightRoyal(tempCard.num, tempCard.pic); //Calls the function to print out the line that specifies both the value and picture of the current card
			}
			else //If the current card and line did not fit into an if statement above, then the correct line to print out is an empty line
				emptyLine(); //Calls the function to print out an empty line
			tempCard = hand[++index]; //Sets temp card to the next card in the parameter array
			SetConsoleTextAttribute(hConsole, 15);
/*
			printf("%c[%dm", 0x1B, 37); //Sets the foreground color back to white
			printf("%c[%dm", 0x1B, 40); //Sets the background color back to black
*/
			cout << "   ";
		}
		cout << endl;
		index = 0; //Sets the index to 0 so the next card is the first card
		tempCard = hand[index]; //Sets tempCard to the first card in the hand for the next line of printing
	}
	cout << endl;
}

void Card::emptyLine() //Function to print out the line that has no picture or number on a card
{
	cout << "         ";
}

void Card::leftNumber(int x, const char pic) //Function to print out the upper line on a number/ace card that specifies the number or A
{
	if(x == 10) //If the number on the card is a 10
		cout << x << "       ";
	else if(x != 1) //If the number on the card is not a 10 and is not an ace
		cout << x << "        ";
	else //If the number for the card is not 2-10, then it is an ace
		cout << "A        ";
}

void Card::rightNumber(int x, const char pic) //Function to print out the bottom line on a number/ace card that specifies the number or A
{

	if(x == 10) //If the number on the card is a 10
		cout << "       " << x;
	else if(x != 1) //If the number on the card is not a 10 and is not an ace
		cout << "        " << x;
	else //If the number for the card is not 2-10, then it is an ace
		cout << "        A";
}

void Card::leftRoyal(int x, const char pic) //Function to print out the upper line on a royal card that specifies the picture and J/Q/K
{
	char letter; //Variable to be used to save J, Q, or K, depending on the number of the card
	if(x == 11) //If the number on the card is 11, then it is a Jack
		letter = 'J'; //Sets letter to print out a J
	else if(x == 12) //If the number on the card is a 12, then it is a Quuen
		letter = 'Q'; //Sets letter to print out a Q
	else //If the card is not a Jack or Queen, then it is a King
		letter = 'K'; //Sets letter to print out a K
       	cout << letter << pic << "       ";
}

void Card::rightRoyal(int x, const char pic) //Function to print out the lower line on a royal card that specifies the picture and J/Q/K
{
	char letter; //Variable to be used to save J, Q, or K, depending on the number of the card
	if(x == 11) //If the number on the card is 11, then it is a Jack
		letter = 'J'; //Sets letter to print out a J
	else if(x == 12) //If the number on the card is a 12, then it is a Quuen
		letter = 'Q'; //Sets letter to print out a Q
	else //If the card is not a Jack or Queen, then it is a King
		letter = 'K'; //Sets letter to print out a K
        cout << "       " << pic << letter;
}

void Card::onePic(const char pic) //Function to print out the line on a card that has one picture
{
	cout << "    " << pic << right << "    ";
}

void Card::twoPic(const char pic) //Function to print out the line on a card that has two pictures
{
	cout << "  " << pic << "   " << pic << "  ";
}

void Card::backLine(const char pic) //Function to print out one line of a flipped card
{
        cout << " " << pic << " " << pic << " " << pic << " " << pic << " ";
}
