#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define CARDS 52
#define FACES 13

typedef struct Card Card;

struct Card {
	const char* face;
	const char* suit;
};

void fillDeck(Card * const wDeck, const char * wFace[], const char * wSuit[]);
void shuffle(Card * const wDeck);
int getCardValue(const char* cardFace, char* playerOrDealer, int *total);
int dealerGetsAce(int* dealerTotal);
void userGetsAce(int* playerTotal);
bool isAce(const char* cardFace);
int updatedTotal(int *total, int valueAdded);
void usersTurn(int *currentCard, const char* cardFace, int* userTotal, Card * const deck);
void dealersTurn(int* currentCard, const char* cardFace, int* userTotal, Card * const deck);
bool isBlackJack(int total);
bool playAgainFunc(char playAgainInput[]);
