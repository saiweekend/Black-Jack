/*
This include all of the essential math that would be needed for caclulating values for Black Jack.
*/

#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <climits>
#include <iomanip>
#include <cstdlib>
using namespace std;

int topCard = 0;
float win = 1.00;
int level;


int getRandomNumber(int low, int high)
{
	static bool firstTime = true;
	int randNum;
	if (firstTime)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		firstTime = false;
	}
	randNum = rand() % (high - low + 1) + low;
	return randNum;
}
int CardValue(int card)
{
	int cardVal;
	switch (card % 100)
	{
	case 1:
		cardVal = 11;
		break;
	case 11:
	case 12:
	case 13:
		cardVal = 10;
		break;
	case 14:
		cardVal = 1;
		break;
	default: 
		cardVal = (card % 100);
	}
	return cardVal;
}
int getTopCard(int deck[])
{
	for (int i = 0; i < 51; i++)
	{
		if (deck[i] != 0)
		{
			topCard = deck[i];
			deck[i] = 0;
			return topCard;
		}
	}
}
int getHandValue(const int hand[])
{
	int addCardValues = 0;
	for (int i = 0; i < 9; i++)
	{
		addCardValues = addCardValues = CardValue(hand[i]);
	}
	return addCardValues;
}
bool playAnotherHand(char& Play)
{
	cout << endl << "\nWould you like to play another hand? (Y\N) ";
	cin >> Play;
	cout << "\n" << endl;
	if (Play == 'y' || Play == 'Y')
	{
		playOneHand();
		return(true);
	}
	else
	{
		return(false);
	}
}
bool userWantsToDraw(char& Draw)
{
	cout << endl << "\nWould you like to hit or stand? (H/S) ";
	cin >> Draw;
	cout << "\n";
	if (Draw == 'h' || Draw == 'H')
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
void initializeDeck(int deck[])
{
	int Rank = 101;
	int i = 0;
	for (i = 0; i <= 13; i++) //Hearts
	{
		deck[i] = Rank++;
	}
	for (i = 13; i <= 26; i++) //Diamonds
	{
		deck[i] = Rank++ + 100 - 14;
	}
	for (i = 26; i <= 39; i++) //Clubs
	{
		deck[i] = Rank++ + 200 - 28;
	}
	for (i = 39; i <= 51; i++) //Spades
	{
		deck[i] = Rank++ + 300 - 42;
	}
}
void dumpDeck(int deck[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i + i << ".)" << deck[i] << endl;
	}
}
void shuffle(int deck[], int size)
{
	for (int i = 0; i < 500; i++)
	{
		int T1 = 0;
		int R1 = getRandomNumber(0, size);
		int R2 = getRandomNumber(0, size);
		T1 = deck[R1];
		deck[R1] = deck[R2];
		deck[R2] = T1;
	}
}
void ShowCard(int card)
{
	if (card == 0)
	{
		cout << "";
	}
	else
	{
		switch (card % 100) 
		{
			case 1:
				cout << "A";
				break;
			case 11:
				cout << "J";
				break;
			case 12:
				cout << "K";
				break;
			case 13:
				cout << "Q";
				break;
			case 14:
				cout << "A";
				break;
			default:
				cout << card % 100;
		}
	}
	if (card == 0)
	{
		cout << "";
	}
	else
	{
		if ((card >= 101) && (card <= 144)) //HEARTS
		{
			cout << static_cast<char>(3);
		}
		else if ((card >= 201) && (card <= 214)) //Diamonds
		{
			cout << static_cast<char>(4);
		}
		else if ((card >= 301) && (card <= 314)) //Clubs
		{
			cout << static_cast<char>(5);
		}
		else if ((card >= 401) && (card <= 414)) //Spades
		{
			cout << static_cast<char>(6);
		}
	}
}
void showCards(const int deck[], int numCards, bool hideFirstCards)
{
	if (hideFirstCards)
	{
		cout << "** ";

	}
	for (int i = 1; i < numCards; i++)
	{
		if (deck[i] != 0)
		{
			ShowCard(deck[i]);
			cout << " ";
		}
		else {
			cout << "";
		}
	}
}
void whoWins(const int pH[], const int dH[])
{
	int playerScore = getHandValue(pH);
	int dealerScore = getHandValue(dH);
	scoreBoard(pH, dH);
	if ((playerScore < 22) && (playerScore > dealerScore) || 
		((dealerScore > 21) && (playerScore < 22))) 
	{
		cout << "\n";
		cout << "You Win!" << endl;
		win++;
	}
	else
	{
		if (playerScore == dealerScore) 
		{
			cout << "\n";
			cout << "Push in the Dealer's favor. 0.1 payout." << endl;
		}
		else{
			cout << "\n";
			cout << "You Lose." << endl;
			win--;
		}
	}
}
void checkBust(const int pH[], const int dH[], char Play)
{
	int playerScore = getHandValue(pH);
	int dealerScore = getHandValue(dH);
	if (playerScore > 21)
	{
		cout << "You bust with " << getHandValue(pH) << " points." << endl;
		cout << "\n" << endl;
		win--;
		cout << "Winnings multiplayer: " << win << endl;
		playAnotherHand(Play);
	}
}
void blackJack(const int pH[], const int dH[], char Play)
{
	int playerScore = getHandValue(pH);
	int dealerScore = getHandValue(dH);
	if ((playerScore == 21) && (dealerScore != 21))
	{
		cout << "\n\n";
		scoreBoard(pH, dH);
		cout << "\n";
		cout << "Blackjack! You win a 3:2 payout." << endl;
		win = win + 1.5;
		cout << "\n";
		cout << "Winnings multiplayer: " << win << endl;
		backDoorKenny(pH);
		playAnotherHand(Play);
	}
	else if ((playerScore == 21) && (dealerScore == 21))
	{
		scoreBoard(pH, dH);
		cout << "\n";
		cout << "Winnings multiplayer: " << win << endl;
		playAnotherHand(Play);
	}
}
void naturalBlackJack(const int pH[], const int dH[], char Play)
{
	int playerScore = getHandValue(pH);
	int dealerScore = getHandValue(dH);
	if ((playerScore == 21) && (dealerScore != 21))
	{
		scoreBoard(pH, dH);
		cout << "\n";
		cout << "Natural Blackjack! You win a 3:2 payout.";
		win = win + 1.5;
		backDoorKenny(pH);
		playAnotherHand(Play);
	}
}
void playOneHand()
{
	char Play = 'N';
	do
	{
		char Draw = 'H';
		int deck[52];
		initializeDeck(deck);
		shuffle(deck, 51);
		int pH[10] = { 0 };
		int dH[10] = { 0 };
		addToHand(pH, getTopCard(deck)); //Deal First Round
		addToHand(dH, getTopCard(deck));
		addToHand(pH, getTopCard(deck));
		addToHand(dH, getTopCard(deck));
		cout << "*********************************************************" << endl;
		cout << "\n" << endl;
		cout << "The Dealer shuffled and dealt you each of your cards." << endl;
		cout << "\n" << endl;
		naturalBlackJack(pH, dH, 'y');
		blackJack(pH, dH, 'Y');
		cout << "Your Hand: " << endl;
		showCards(pH, 10, false);
		cout << "\n\Dealer's Hand: " << endl;
		showCards(dH, 10, true);
		checkSoftOrHard(pH);
		while (userWantsToDraw(Draw))
		{
			addToHand(pH, getTopCard(deck));
			cout << "The Dealer dealt you another card.\n" << endl;
			cout << "Your Hand: " << endl;
			showCards(pH, 10, false);
			checkSoftOrHard(pH);
			checkBust(pH, dH, 'y');
			blackJack(pH, dH, 'Y');
			whoWins(pH, dH);
			cout << endl;
			cout << "Winnings Multiplayer: " << win << endl;

		}
	} 
		while (playAnotherHand(Play));
}
void scoreBoard(const int pH[], const int dH[])
{
	cout << "Player Hand: ";
	showCards(pH, 10, false);
	cout << " (" << getHandValue(pH) << "pts)." << endl;
}
void backDoorKenny(const int hand[])
{
	if ((CardValue(hand[0])%100 == 10) && (CardValue(hand[1])%100 == 11))
	{
		cout << "\n\n";
		cout << "You pulled a Backdoor Kenny!\n" << endl;
		cout << "Win an additional 1:4 payout\n" << endl;
		win = win + 25;
		cout << "Winnings multiplyer: " << endl;
	}

}
void checkSoftOrHard(int pH[])
{
	for (int i = 0; i < 9; i++)
	{
		int checkAce = CardValue(pH[i]);
		int softOrHard;
		if (checkAce == 1 || checkAce == 11)
		{
			cout << "\n";
			cout << "\nWould you like your Ace to count as 1 or 11 points? (1/11): ";
			cin >> softOrHard;
			if (softOrHard == 1)
			{
				if (checkAce == 11)
				{
					pH[i] = pH[i] + 13;
				}
				else if (softOrHard == 11)
				{
					if (checkAce == 1)
					{
						pH[i] = pH[i] - 13;
					}
				}
				else if (softOrHard != 1 || softOrHard != 11)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nPlease enter the number 1 or 11. " << endl;
					checkSoftOrHard(pH);
				}
			}
		}
	}
}
void softOrHardAI(int dH[], int pH[])
{
	for (int i = 0; i < 9; i++)
	{
		if (CardValue(dH[i]) == 1 || CardValue(dH[i]) == 11) 
		{
			if (CardValue(dH[i]) == 11) 
			{
				if (getHandValue(dH) - CardValue(dH[i]) + 1 > getHandValue(pH)) 
				{
					if (getHandValue(dH) - CardValue(dH[i]) + 1 < 22) 
					{
						dH[i] = dH[i] + 13;
					}
				}
				else if (getHandValue(dH) > 21) 
				{
					dH[i] = dH[i] - 13;
				}
			}
			else 
			{
				if (getHandValue(dH) - CardValue(dH[i]) + 11 > getHandValue(pH)) 
				{
					if (getHandValue(dH) - CardValue(dH[i]) + 11 < 22) 
					{
						dH[i] = dH[i] - 13;
					}
				}
			}
		}
	}
}
void Rules()
	{
	cout << "|*********************************************************|" << endl;
	cout << "|*****************WELCOME TO C++ BLACKJACK****************|" << endl;
	cout << "|---------*************************************-----------|" << endl;
	cout << "|+++RULES+++                                              |" << endl;
	cout << "| 1: ACES CAN EITHER BE '1' or '11' POINTS.               |" << endl;
	cout << "| 2: DEALER WINS TIES UNLESS THE PLAYER HAS A BLACKJACK.  |" << endl;
	cout << "|---------*************************************-----------|" << endl;
	cout << "|+++WINNING+++                                            |" << endl;
	cout << "| [Your score beats Dealer's score {100% BET INCREASE}]   |" << endl;
	cout << "| [Dealer's score beats your score {100% BET INCREASE}]   |" << endl;
	cout << "| [-BLACKJACK- {150% BET INCREASE}]                       |" << endl;
	cout << "| [-NATURAL BLACKJACK- {50% BET INCREASE}]                |" << endl;
	cout << "| [-BACKDOOR KENNY- {25% BET INCREASE}                    |" << endl;
	cout << "| [-PUSH- {TIE}]:                                         |" << endl;
	cout << "|    I. [1:1 PAYOUT IF IN YOUR FAVOR]                     |" << endl;
	cout << "|          {100% BET INCREASE}                            |" << endl;
	cout << "|   II. [0:1 PAYOUT IF IN DEALERS FAVOR]                  |" << endl;
	cout << "|          {NO LOSS, NO GAIN}                             |" << endl;
	cout << "|---------*************************************-----------|" << endl;
	cout << "|*********************************************************|" << endl;
	cout << "|---------*******{ LEVEL OF DIFFICULTY }*******-----------|" << endl;
	cout << "|**  BEGINNER - Dealer stands at a soft 17 & has no AI  **|" << endl;
	cout << "|*** EXPERT - Dealer hits at a soft 17 & has not AI    ***|" << endl;
	cout << "|*********************************************************|" << endl;

	}
void Difficulty()
{
	cout << "\n";
	cout << "Level of Difficulty: Beginner [1] | Expert [2].";
	cin >> level;
	cout << "\n";
	if (level != 1)
	{
		if (level != 2)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter Level of Difficulty [1] or [2]" << endl;
			Difficulty();
		}
	
	}
}
void addToHand(int hand[], int cardToAdd)
{
	for (int i = 0; i < 9; i++)
	{
		if (hand[i] == 0)
		{
			hand[i] = cardToAdd;
			break;
		}
	}
}
void hitUntilStand(int dH[], int deck[], int pH[])
{
	for (int i = 0; i < 9; i++)
	{
		if (level == 1)
		{
			addToHand(dH, getTopCard(deck));
		}
		else if (level == 2)
		{
			addToHand(dH, getTopCard(deck));
			softOrHardAI(dH, pH);
		}
		else
		{
			if (i == 0)
			{
				cout << "The Dealer stands." << endl;
				break;
			}
			else if (i == 1)
			{
				cout << "The Dealer hit a card and stands." << endl;
				break;
			}
			else
			{
				cout << "The Dealer hit " << i << " card & stands." << endl;
				break;
			}
			if (level == 2);
			else if (level == 2)
			{
				softOrHardAI(dH, pH);
			}
		}
	}
}

	