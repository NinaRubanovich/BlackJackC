#include "blackjack.h"

/* An empty deck of cards array is turned into a standard 52 deck of cards. */
void fillDeck(Card * const wDeck, const char * wFace[], const char * wSuit[]) {
	for (size_t i=0; i < CARDS; ++i) {
		wDeck[i].face = wFace[i % FACES];
		wDeck[i].suit = wSuit[i / FACES];
	}
}

/* Using the Fisher-Yates Shuffling Algorithm, a given deck of cards is 
shuffled into randomized order. */
void shuffle(Card * const wDeck) {
	srand(time(NULL));
	for (int i = CARDS-1; i>0; i--) {
		int j = rand() % (i+1);
		Card temp = wDeck[i];
		wDeck[i] = wDeck[j];
		wDeck[j] = temp;
	}
}

/* Given a string value of the card face, the integer value of that card is returned.
If the value is Ace and the card is a player card (playerOrDealer), a 0 is returned.
If the value is Ace and the card is a dealer, the card value will be chosen via the
dealerGetsAce function. */
int getCardValue(const char* cardFace, char* playerOrDealer, int *total) {
	int cardValue = 0;

	if ( strcmp(cardFace, "Ace") == 0 ) {
		if (strcmp(playerOrDealer, "Dealer") == 0) cardValue = dealerGetsAce(total);
		else if (strcmp(playerOrDealer, "Player") == 0 );
		else printf("An unkown error occured in getCardValue function when determining player or dealer\n");
	}
	else if ( strcmp(cardFace, "Deuce" ) == 0 ) cardValue = 2;
	else if ( strcmp(cardFace, "Three" ) == 0 ) cardValue = 3;
	else if ( strcmp(cardFace, "Four" ) == 0 ) cardValue = 4;
	else if ( strcmp(cardFace, "Five" ) == 0 ) cardValue = 5;
	else if ( strcmp(cardFace, "Six" ) == 0 ) cardValue = 6;
	else if ( strcmp(cardFace, "Seven" ) == 0 ) cardValue = 7;
	else if ( strcmp(cardFace, "Eight" ) == 0 ) cardValue = 8;
	else if ( strcmp(cardFace, "Nine" ) == 0 ) cardValue = 9;
	else if ( strcmp(cardFace, "Ten") == 0 || strcmp(cardFace, "Queen") == 0 || strcmp(cardFace, "King") == 0 || strcmp(cardFace, "Jack") == 0) cardValue = 10;
	else printf("An unknown error occured in the when retreiving card value\n");
	return cardValue;
}

/* Called when a dealer's card value is Ace */
int dealerGetsAce(int* dealerTotal) {
	int chosenAceValue = 0;
	if (*dealerTotal <= 10 ) chosenAceValue = 11;
	else chosenAceValue = 1;
	return chosenAceValue;
}

/* Called when a player's card value is Ace. Updates the player's total 
based on the value chosen. */
void userGetsAce(int* playerTotal) {
	int chosenAceValue = 0;
	printf("You got an Ace! Do you chose a 1 or an 11?: ");
	scanf("%d", &chosenAceValue);

	if (chosenAceValue == 1) *playerTotal = updatedTotal(playerTotal, 1);
	else if (chosenAceValue == 11) *playerTotal = updatedTotal(playerTotal, 11);
	else {
			while( chosenAceValue != 11 && chosenAceValue != 1 ) {
				printf("** You must chose either a 1 or an 11 **:");
				scanf("%d", &chosenAceValue);
			}
		}
}

/* Given a card face, returns a true value if the face is an Ace.
otherwise false is returned */
bool isAce(const char* cardFace) {
	if ( strcmp(cardFace, "Ace") == 0) return true;
	else return false;
}

/* Updates the total according to the valueAdded */
int updatedTotal(int *total, int valueAdded) {
	return *total + valueAdded;
}

/* Adds a card value to the userTotal and then "removes" that card from the card deck by
incrementing currentCard */
void usersTurn(int* currentCard, const char* cardFace, int* userTotal, Card * const deck) {
	*userTotal += getCardValue(deck[*currentCard].face, "Player", userTotal);
	if (isAce(deck[*currentCard].face) == true) userGetsAce(userTotal);
	*currentCard += 1;
}

/* Adds a card value to the dealerTotal and then "removes" that card from the card deck by
incrementing currentCard */
void dealersTurn(int* currentCard, const char* cardFace, int* userTotal, Card * const deck) {
	*userTotal += getCardValue(deck[*currentCard].face, "Dealer", userTotal);
	*currentCard += 1;
}

/* Returns true if BlackJack (first two cards add up to 21)*/
bool isBlackJack(int total) {
	if (total == 21) return true;
	else return false;
}

/* Returns true if user wants to play again; otherwise, false is returned */
bool playAgainFunc(char playAgainInput[]) {
	printf("\nWould you like to play again? Enter \"yes\" or \"no\": ");
	scanf("%s", playAgainInput);
	while ((strstr(playAgainInput, "yes") == NULL) && (strstr(playAgainInput, "no") == NULL)) {
		printf("Please enter either \"yes\" or \"no\": ");
		scanf("%s", playAgainInput);
	}
						
	if (strstr(playAgainInput, "yes") != NULL)  return true;
	else return false;
}


