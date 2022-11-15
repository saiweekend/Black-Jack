#include "BlackJackCalc.h"
#include <iostream>
#include <string>


using namespace std;

int topcard = 0;
float win = 1.00;
int level;

int main()
{
	Rules();
	Difficulty();
	playOneHand();
	return 1;

};